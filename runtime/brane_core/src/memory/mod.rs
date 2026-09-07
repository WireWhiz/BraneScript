use region::Allocation;
use std::fmt::Display;
use std::sync::atomic::{AtomicU16, AtomicU32};
use std::{ptr::NonNull, sync::Mutex};

pub const BS_PAGE_SIZE: usize = u16::MAX as usize + 1;

#[repr(C)]
pub struct BufferBinding {
    pub data: Option<NonNull<u8>>,
    pub len: usize,
    // This is a usize for alignment purposes, but should never exceed u16::MAX
    pub generation: usize,
}

// Both these types are api safe, in accordance with the "null pointer optimization"
pub type BufferTable = [BufferBinding; BS_PAGE_SIZE];
pub type FnTable = [Option<NonNull<u8>>; BS_PAGE_SIZE];
/// Currently an alias for global binding index
pub type PageId = u16;
pub type FnId = u16;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
#[repr(C)]
pub struct BSPtr(pub u64);

impl BSPtr {
    pub fn new(generation: u16, binding: u16, offset: u32) -> Self {
        Self(((generation as u64) << 48) | ((binding as u64) << 32) | offset as u64)
    }

    pub fn generation(self) -> u16 {
        (self.0 >> 48) as u16
    }

    pub fn binding(self) -> u16 {
        ((self.0 >> 32) & 0xFFFF) as u16
    }

    pub fn offset(self) -> u32 {
        (self.0 & 0x00000000FFFFFFFF) as u32
    }

    pub fn set_generation(&mut self, generation: u16) {
        *self = Self::new(generation, self.binding(), self.offset());
    }

    pub fn set_binding(&mut self, binding: u16) {
        *self = Self::new(self.generation(), binding, self.offset());
    }

    pub fn set_offset(&mut self, offset: u32) {
        *self = Self::new(self.generation(), self.binding(), offset);
    }
}

impl Display for BSPtr {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "BSPtr {{ gen: {}, binding: {}, offset: {} }} ",
            self.generation(),
            self.binding(),
            self.offset()
        )
    }
}

pub struct Page {
    pub id: PageId,
    pub data: Allocation,
}

pub struct PageVec {
    pub pages: Vec<PageId>,
}

pub struct Store {
    unused_pages: Mutex<Vec<Page>>,
    next_page_binding: AtomicU32,
    fn_table: Box<FnTable>,
    next_fn_id: AtomicU16,
    unused_fn_ids: Mutex<Vec<FnId>>,
}

impl Store {
    pub fn new() -> Self {
        let fn_table = unsafe {
            let mut array = Box::<FnTable>::new_uninit();
            for i in array.assume_init_mut().iter_mut() {
                *i = None;
            }
            array.assume_init()
        };
        Self {
            unused_pages: Default::default(),
            next_page_binding: AtomicU32::new(1),
            next_fn_id: AtomicU16::new(0),
            fn_table,
            unused_fn_ids: Default::default(),
        }
    }

    /// Returns an unused page
    pub fn alloc_page(&self) -> Result<Page, AllocationError> {
        if let Some(page) = self.unused_pages.lock().unwrap().pop() {
            return Ok(page);
        }

        let data = region::alloc(BS_PAGE_SIZE, region::Protection::READ_WRITE)
            .map_err(|_| AllocationError::OsFailedToAllocatePage)?;

        let id = self
            .next_page_binding
            .fetch_add(1, std::sync::atomic::Ordering::Relaxed);
        if id == std::u16::MAX as u32 {
            return Err(AllocationError::OutOfMemory);
        }
        let id = id as u16;
        Ok(Page { id, data })
    }

    /// Adds a page to the unused pool
    pub fn free_page(&self, page: Page) {
        self.unused_pages.lock().unwrap().push(page);
    }

    pub fn fn_table_ptr(&self) -> *const FnTable {
        Box::as_ref(&self.fn_table)
    }

    pub unsafe fn expose_fn(&self, ptr: NonNull<u8>) -> FnId {
        if let Some(unused) = self.unused_fn_ids.lock().unwrap().pop() {
            // Yes, this circumevents rust, but I don't want to deal with it rn
            unsafe {
                *std::mem::transmute::<_, *mut _>(self.fn_table.as_ptr().add(unused as usize)) =
                    Some(ptr)
            };
            unused
        } else {
            let id = self
                .next_fn_id
                .fetch_add(1, std::sync::atomic::Ordering::Relaxed);
            unsafe {
                *std::mem::transmute::<_, *mut _>(self.fn_table.as_ptr().add(id as usize)) =
                    Some(ptr)
            };
            id
        }
    }

    pub unsafe fn remove_fn(&self, id: FnId) {
        assert!(
            self.fn_table[id as usize].is_some(),
            "Tried to remove unexposed function"
        );
        unsafe {
            *std::mem::transmute::<_, *mut Option<NonNull<u8>>>(
                self.fn_table.as_ptr().add(id as usize),
            ) = None;
        }
        self.unused_fn_ids.lock().unwrap().push(id);
    }
}

#[derive(Debug, thiserror::Error)]
pub enum AllocationError {
    #[error("Out of memory")]
    OutOfMemory,
    #[error("OS failed to allocate page")]
    OsFailedToAllocatePage,
}

#[derive(Debug)]
pub enum PtrError {
    NotBound,
    Unaligned,
}
