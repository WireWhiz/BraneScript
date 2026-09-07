//! Memory access safety test suite.
//!
//! Companion to `tests/ptr_access.bscript`.
//!
//! # The invariant under test
//!
//! Every load or store either traps, or accesses memory strictly inside some
//! currently-registered allocation. Nothing else is promised.
//!
//! In particular this suite does NOT require that an out-of-range access is
//! attributed to the allocation the guest *meant*. Pointer arithmetic is
//! byte-based and unmasked, so an offset large enough to carry out of the low
//! 32 bits names a different binding. If that binding is live and the access is
//! in bounds for it, the access succeeds and the guest gets someone else's
//! memory. That is an accepted silent failure — the cost of not checking — and
//! there are no tests for it here.
//!
//! The one thing carry does not license: the binding field must still be masked
//! to 16 bits before the table lookup. Bits 48–63 are reachable by carry, and an
//! unmasked index reads a base/length pair from beyond the table and then
//! dereferences it. That's an arbitrary host read rather than a silent failure,
//! so `binding_high_bits_are_masked` is a hard requirement.
//!
//! # Why `expect_trap` still works nearly everywhere
//!
//! Most tests register a single allocation into an otherwise-empty table. A
//! carried offset lands on an empty binding, which traps; an uncarried one stays
//! on the original binding out of bounds, which also traps. Both paths trap, so
//! the assertion is still exact. The multi-allocation tests are the exception,
//! and they use deltas chosen to stay inside the offset field.
//!
//! Determinism depends on `reset_allocations()` in `harness()`. Without it a
//! test that bails early leaks its slot, binding indices become a function of
//! test order, and results shift between runs.
//!
//! # Groups
//!
//!   1.  byte semantics    — add moves bytes, not elements
//!   2.  in-bounds         — checks don't reject valid accesses
//!   3.  upper boundary    — last valid, straddling, past the end
//!   4.  lower boundary    — negative offsets
//!   5.  binding lookup    — masking, unregistered slots, forged handles
//!   6.  degenerate allocs — zero-length, shorter than the access
//!   7.  lifecycle         — add, remove, reuse, aliasing, churn
//!   8.  isolation         — non-carrying offsets can't leave the allocation
//!   9.  non-clobber       — a rejected store must not write ANYWHERE
//!  10.  arithmetic policy — forming an OOB pointer is legal, using it isn't
//!
//! Group 9 first. Every other group asks "was the access refused?", which a
//! clamp answers yes to while still writing to the edge of the object. Group 9
//! asks "did memory change?"
//!
//! One seam left open, marked `TODO(trap)`: `expect_trap` accepts any fault, so
//! a clean bounds trap and a genuine segfault are indistinguishable.

#[cfg(test)]
mod mem_tests {
    use brane_core::runtime::LoadedModule;
    use std::sync::Mutex;
    use std::sync::MutexGuard;

    use anyhow::bail;
    use anyhow::Result;
    use brane_backend_cranelift::CraneliftJitBackend;
    use brane_core::memory::BSPtr;
    use brane_core::runtime::Runtime;
    use brane_core::ExecutionCtx;
    use branec::CompileContext;
    use branec_source::SourceManager;

    /// Access size in bytes for the i64 entry points.
    const I64_SIZE: i64 = 8;

    // ========================================================================
    // JIT FUNCTION TABLE
    // ========================================================================

    pub struct MemFunctions {
        pub ctx: *mut ExecutionCtx,
        pub load_i64: extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> i64,
        pub store_i64: extern "C" fn(*mut ExecutionCtx, BSPtr, i64, i64),
        pub load_u8: extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> u8,
        pub store_u8: extern "C" fn(*mut ExecutionCtx, BSPtr, i64, u8),
        pub ptr_bits: extern "C" fn(*mut ExecutionCtx, BSPtr) -> u64,
        pub ptr_add_bits_i64: extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> u64,
        pub ptr_add_bits_u8: extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> u64,
        pub load_from_raw_bits: extern "C" fn(*mut ExecutionCtx, u64) -> i64,
        pub store_to_raw_bits: extern "C" fn(*mut ExecutionCtx, u64, i64),
        pub ptr_add_only: extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> i64,
        pub load_after_walk: extern "C" fn(*mut ExecutionCtx, BSPtr, i64, i64, i64) -> i64,
        pub roundtrip_i64: extern "C" fn(*mut ExecutionCtx, BSPtr, i64, i64) -> i64,
        pub copy_i64: extern "C" fn(*mut ExecutionCtx, BSPtr, i64, BSPtr, i64),
    }

    // ========================================================================
    // HARNESS
    // ========================================================================

    pub struct MemTestHarness {
        functions: MemFunctions,
        exe_ctx: Box<ExecutionCtx>,
        _rt: Runtime<CraneliftJitBackend>,
    }

    unsafe impl Sync for MemTestHarness {}
    unsafe impl Send for MemTestHarness {}

    impl MemTestHarness {
        pub fn new() -> Result<Self> {
            let mut cctx = CompileContext {
                emitter: branec_emitter::ConsoleEmitter::new(),
                sources: SourceManager::new(),
                loaded_modules: Default::default(),
            };
            cctx.load_std();

            let rt = Runtime::<CraneliftJitBackend>::new();
            let mut exe_ctx = Box::new(rt.new_execution_ctx());

            let uri = cctx
                .sources
                .add_custom(include_str!("../../tests/ptr_access.bscript").to_string())?;
            let module_src = cctx.emit_module("ptr_access".into(), &uri)?;
            let mod_id = rt.load_module(uri, module_src)?;

            let functions = {
                let module = rt
                    .get_module(mod_id)
                    .ok_or_else(|| anyhow::anyhow!("module not loaded"))?;

                macro_rules! get_fn {
                    ($name:literal, $type:ty) => {{
                        let index = module
                            .get_fn_by_name($name)
                            .ok_or_else(|| anyhow::anyhow!("function '{}' not found", $name))?;
                        let code = unsafe { *exe_ctx.fn_bindings_ptr().add(index as usize) };
                        unsafe { std::mem::transmute::<_, $type>(code) }
                    }};
                }

                MemFunctions {
                    ctx: &mut *exe_ctx as *mut ExecutionCtx,
                    load_i64: get_fn!(
                        "mem_load_i64",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> i64
                    ),
                    store_i64: get_fn!(
                        "mem_store_i64",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64, i64)
                    ),
                    load_u8: get_fn!(
                        "mem_load_u8",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> u8
                    ),
                    store_u8: get_fn!(
                        "mem_store_u8",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64, u8)
                    ),
                    ptr_bits: get_fn!(
                        "mem_ptr_bits",
                        extern "C" fn(*mut ExecutionCtx, BSPtr) -> u64
                    ),
                    ptr_add_bits_i64: get_fn!(
                        "mem_ptr_add_bits_i64",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> u64
                    ),
                    ptr_add_bits_u8: get_fn!(
                        "mem_ptr_add_bits_u8",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> u64
                    ),
                    load_from_raw_bits: get_fn!(
                        "mem_load_from_raw_bits",
                        extern "C" fn(*mut ExecutionCtx, u64) -> i64
                    ),
                    store_to_raw_bits: get_fn!(
                        "mem_store_to_raw_bits",
                        extern "C" fn(*mut ExecutionCtx, u64, i64)
                    ),
                    ptr_add_only: get_fn!(
                        "mem_ptr_add_only",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64) -> i64
                    ),
                    load_after_walk: get_fn!(
                        "mem_load_after_walk",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64, i64, i64) -> i64
                    ),
                    roundtrip_i64: get_fn!(
                        "mem_roundtrip_i64",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64, i64) -> i64
                    ),
                    copy_i64: get_fn!(
                        "mem_copy_i64",
                        extern "C" fn(*mut ExecutionCtx, BSPtr, i64, BSPtr, i64)
                    ),
                }
            };

            Ok(Self {
                functions,
                exe_ctx,
                _rt: rt,
            })
        }

        pub fn functions(&self) -> &MemFunctions {
            &self.functions
        }

        pub fn ctx_ptr(&mut self) -> *mut ExecutionCtx {
            &mut *self.exe_ctx as *mut ExecutionCtx
        }

        pub fn ctx_mut(&mut self) -> &mut ExecutionCtx {
            &mut self.exe_ctx
        }

        /// Clear every slot. A test that bails early via `?` never reaches its
        /// fixture drops in the failure path we care about least, and more
        /// importantly a previous *run* of a failing test can leave the table
        /// dirty. Without this, binding indices depend on test order and the
        /// order-sensitive tests report nonsense.
        pub fn reset_allocations(&mut self) {
            for buffer in self.exe_ctx.buffers.iter_mut() {
                buffer.data = None;
                buffer.len = 0;
            }
        }
    }

    static HARNESS: std::sync::LazyLock<Mutex<MemTestHarness>> = std::sync::LazyLock::new(|| {
        Mutex::new(MemTestHarness::new().expect("failed to build mem test harness"))
    });

    /// Recovers from poisoning on purpose: one test tripping an assertion
    /// shouldn't turn every other test into a poisoned-mutex error that hides
    /// the real failure.
    fn harness() -> MutexGuard<'static, MemTestHarness> {
        let mut g = HARNESS.lock().unwrap_or_else(|e| e.into_inner());
        g.reset_allocations();
        g
    }

    // ========================================================================
    // TRAP EXPECTATION
    // ========================================================================

    /// TODO(trap): tighten once `TrapCode::user` values are plumbed through.
    /// Right now any fault counts, so "the bounds check fired" and "we got lucky
    /// with an unmapped page" look identical — and only one is a working sandbox.
    fn expect_trap<R>(label: &str, mut f: impl FnMut() -> R) -> Result<()> {
        match unsafe { brane_core::sandbox::try_run(&mut f) } {
            Err(_) => Ok(()),
            Ok(_) => bail!("{label}: expected a trap, but the access was permitted"),
        }
    }

    fn expect_ok<R>(label: &str, mut f: impl FnMut() -> R) -> Result<R> {
        match unsafe { brane_core::sandbox::try_run(&mut f) } {
            Ok(v) => Ok(v),
            Err(e) => bail!("{label}: expected success, but trapped: {e:?}"),
        }
    }

    /// Run something that may or may not trap; only its effect on memory matters.
    fn run_ignoring_trap<R>(mut f: impl FnMut() -> R) {
        let _ = unsafe { brane_core::sandbox::try_run(&mut f) };
    }

    // ========================================================================
    // ALLOCATION FIXTURE
    // ========================================================================

    /// A raw buffer registered with the runtime, flanked by canaries no guest
    /// access should ever touch.
    ///
    ///   backing:  [ CANARY | payload | CANARY ]
    ///                      ^ registered
    ///
    /// `check_canaries` proves a rejected access didn't land just outside;
    /// `check_unchanged` proves it didn't get clamped to just inside.
    ///
    /// Releases on `Drop`, so a test that bails via `?` still frees its slot.
    struct Fixture {
        backing: Vec<u8>,
        ptr: BSPtr,
        ctx: *mut ExecutionCtx,
        payload_off: usize,
        payload_len: usize,
    }

    const CANARY_LEN: usize = 64;
    const CANARY_BYTE: u8 = 0xA5;

    impl Fixture {
        fn new(h: &mut MemTestHarness, payload_len: usize) -> Self {
            let ctx = h.ctx_ptr();
            let mut backing = vec![CANARY_BYTE; CANARY_LEN * 2 + payload_len];
            for i in 0..payload_len {
                backing[CANARY_LEN + i] = 0;
            }
            let data = unsafe { backing.as_mut_ptr().add(CANARY_LEN) };
            let ptr = h.ctx_mut().add_allocation(data, payload_len);
            Self {
                backing,
                ptr,
                ctx,
                payload_off: CANARY_LEN,
                payload_len,
            }
        }

        /// `n` i64 elements, element `i` set to `1000 + i`. Distinct non-zero
        /// values, so a load from the wrong address is visible rather than
        /// plausibly zero.
        fn of_i64s(h: &mut MemTestHarness, n: usize) -> Self {
            let mut f = Fixture::new(h, n * I64_SIZE as usize);
            for i in 0..n {
                let v = (1000 + i as i64).to_ne_bytes();
                let base = f.payload_off + i * I64_SIZE as usize;
                f.backing[base..base + I64_SIZE as usize].copy_from_slice(&v);
            }
            f
        }

        /// Payload filled with a repeating marker, identifiable by content.
        fn marked(h: &mut MemTestHarness, n_elems: usize, marker: i64) -> Self {
            let mut f = Fixture::new(h, n_elems * I64_SIZE as usize);
            for i in 0..n_elems {
                let v = marker.to_ne_bytes();
                let base = f.payload_off + i * I64_SIZE as usize;
                f.backing[base..base + I64_SIZE as usize].copy_from_slice(&v);
            }
            f
        }

        fn ptr(&self) -> BSPtr {
            self.ptr
        }

        fn ptr_at(&self, offset: u32) -> BSPtr {
            let mut offset_ptr = self.ptr;
            offset_ptr.set_offset(offset);
            offset_ptr
        }

        fn len(&self) -> i64 {
            self.payload_len as i64
        }

        fn payload(&self) -> &[u8] {
            &self.backing[self.payload_off..self.payload_off + self.payload_len]
        }

        fn check_canaries(&self, label: &str) -> Result<()> {
            let lead = &self.backing[..self.payload_off];
            let trail = &self.backing[self.payload_off + self.payload_len..];
            if let Some(i) = lead.iter().position(|&b| b != CANARY_BYTE) {
                bail!(
                    "{label}: leading canary corrupted at -{} (value {:#04x}) — a write \
                     landed below the allocation",
                    self.payload_off - i,
                    lead[i]
                );
            }
            if let Some(i) = trail.iter().position(|&b| b != CANARY_BYTE) {
                bail!(
                    "{label}: trailing canary corrupted at +{} (value {:#04x}) — a write \
                     landed above the allocation",
                    self.payload_len + i,
                    trail[i]
                );
            }
            Ok(())
        }

        fn snapshot(&self) -> Vec<u8> {
            self.payload().to_vec()
        }

        fn check_unchanged(&self, before: &[u8], label: &str) -> Result<()> {
            if self.payload() != before {
                let at = before
                    .iter()
                    .zip(self.payload())
                    .position(|(a, b)| a != b)
                    .unwrap_or(0);
                bail!(
                    "{label}: payload modified at byte {at} by an access that should have \
                     been rejected — the check is redirecting the write rather than \
                     refusing it"
                );
            }
            Ok(())
        }
    }

    impl Drop for Fixture {
        fn drop(&mut self) {
            unsafe { (*self.ctx).remove_allocation(self.ptr) };
        }
    }

    // ========================================================================
    // 1. BYTE SEMANTICS
    // ========================================================================
    //
    // `add` moves bytes regardless of the pointee type. These are the tests that
    // pin that decision; if someone reintroduces element scaling, these fail
    // immediately and unambiguously rather than showing up as a wrong value
    // three groups later.

    #[test]
    fn bytes_add_on_i64_pointer_moves_one_byte() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 64);
        let fs = h.functions();
        let base_offset = 0u32;

        for delta in [0i64, 1, 2, 7, 8, 33] {
            let bits = expect_ok(&format!("ptr_add_bits_i64(+{delta})"), || {
                (fs.ptr_add_bits_i64)(fs.ctx, f.ptr(), delta)
            })?;
            let got = BSPtr(bits).offset();
            let want = base_offset + delta as u32;
            if got != want {
                bail!(
                    "add(*mut i64, {delta}) produced offset {got}, expected {want} — add is \
                     scaling by the pointee size instead of moving bytes"
                );
            }
        }

        f.check_canaries("bytes_add_on_i64_pointer_moves_one_byte")?;
        Ok(())
    }

    #[test]
    fn bytes_add_is_identical_for_u8_and_i64_pointers() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 64);
        let fs = h.functions();

        for delta in [1i64, 4, 8, 17] {
            let a = expect_ok("u8 add", || (fs.ptr_add_bits_u8)(fs.ctx, f.ptr(), delta))?;
            let b = expect_ok("i64 add", || (fs.ptr_add_bits_i64)(fs.ctx, f.ptr(), delta))?;
            if a != b {
                bail!(
                    "add(+{delta}) differs by pointee type: u8 gave offset {}, i64 gave {} — \
                     arithmetic must be type-independent",
                    BSPtr(a).offset(),
                    BSPtr(b).offset()
                );
            }
        }

        f.check_canaries("bytes_add_is_identical_for_u8_and_i64_pointers")?;
        Ok(())
    }

    #[test]
    fn bytes_unaligned_i64_load_reads_across_elements() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 4);
        let fs = h.functions();

        // Byte 4 straddles elements 0 and 1. On a little-endian target that's
        // the high half of 1000 (zero) and the low half of 1001, i.e. 1001 << 32.
        let got = expect_ok("unaligned load @4", || (fs.load_i64)(fs.ctx, f.ptr(), 4))?;
        let want = 1001i64 << 32;
        if got != want {
            bail!(
                "unaligned load at byte 4 returned {got:#x}, expected {want:#x} — byte \
                 offsets aren't reaching arbitrary positions"
            );
        }

        f.check_canaries("bytes_unaligned_i64_load_reads_across_elements")?;
        Ok(())
    }

    // ========================================================================
    // 2. IN-BOUNDS
    // ========================================================================

    #[test]
    fn inbounds_first_middle_last() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let fs = h.functions();

        for elem in [0i64, 1, 7, 14, 15] {
            let off = elem * I64_SIZE;
            let got = expect_ok(&format!("load @{off}"), || {
                (fs.load_i64)(fs.ctx, f.ptr(), off)
            })?;
            if got != 1000 + elem {
                bail!(
                    "load @{off}: expected {}, got {got} — the check passed but the \
                     effective address is wrong",
                    1000 + elem
                );
            }
        }

        f.check_canaries("inbounds_first_middle_last")?;
        Ok(())
    }

    #[test]
    fn inbounds_nonzero_starting_offset() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let fs = h.functions();

        // A pointer already offset into the allocation: the check can't assume
        // offset starts at zero.
        let mid = f.ptr_at(64);

        let got = expect_ok("mid load @0", || (fs.load_i64)(fs.ctx, mid, 0))?;
        if got != 1008 {
            bail!("mid load @0: expected 1008, got {got}");
        }
        let got = expect_ok("mid load @56", || (fs.load_i64)(fs.ctx, mid, 56))?;
        if got != 1015 {
            bail!("mid load @56: expected 1015, got {got}");
        }
        expect_trap("mid load @64 (past end)", || (fs.load_i64)(fs.ctx, mid, 64))?;
        expect_trap("mid load @-72 (below base)", || {
            (fs.load_i64)(fs.ctx, mid, -72)
        })?;

        f.check_canaries("inbounds_nonzero_starting_offset")?;
        Ok(())
    }

    #[test]
    fn inbounds_store_then_load_roundtrip() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 8);
        let fs = h.functions();

        for off in [0i64, 24, 56] {
            let sentinel = (0x0BAD_F00D_0000_0000u64 as i64) | off;
            let got = expect_ok(&format!("roundtrip @{off}"), || {
                (fs.roundtrip_i64)(fs.ctx, f.ptr(), off, sentinel)
            })?;
            if got != sentinel {
                bail!("roundtrip @{off}: wrote {sentinel:#x}, read back {got:#x}");
            }
        }

        f.check_canaries("inbounds_store_then_load_roundtrip")?;
        Ok(())
    }

    #[test]
    fn inbounds_every_valid_i64_position() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 64);
        let fs = h.functions();

        // Every byte offset that leaves room for a full 8-byte access, not just
        // the aligned ones.
        for off in 0..=(f.len() - I64_SIZE) {
            expect_ok(&format!("load @{off}"), || {
                (fs.load_i64)(fs.ctx, f.ptr(), off)
            })?;
        }

        f.check_canaries("inbounds_every_valid_i64_position")?;
        Ok(())
    }

    // ========================================================================
    // 3. UPPER BOUNDARY
    // ========================================================================
    //
    // With byte offsets, the straddle cases and the past-the-end cases are the
    // same axis: offsets len-7..len-1 start inside and end outside, offsets >=
    // len start outside. A check written as `icmp ult offset, length` passes the
    // whole straddling window.

    #[test]
    fn upper_i64_straddling_end_traps() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 64);
        let fs = h.functions();
        let len = f.len();

        expect_ok("load @56 (last fully contained)", || {
            (fs.load_i64)(fs.ctx, f.ptr(), len - I64_SIZE)
        })?;

        for off in (len - I64_SIZE + 1)..len {
            expect_trap(
                &format!("load @{off} (straddles end by {})", off - (len - I64_SIZE)),
                || (fs.load_i64)(fs.ctx, f.ptr(), off),
            )?;
        }

        f.check_canaries("upper_i64_straddling_end_traps")?;
        Ok(())
    }

    #[test]
    fn upper_past_end_traps() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let fs = h.functions();
        let len = f.len();

        for off in [len, len + 1, len + 8, len + 4096, 1 << 20] {
            expect_trap(&format!("load @{off}"), || {
                (fs.load_i64)(fs.ctx, f.ptr(), off)
            })?;
        }

        f.check_canaries("upper_past_end_traps")?;
        Ok(())
    }

    #[test]
    fn upper_last_byte_of_unaligned_allocation() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 33); // deliberately not a multiple of 8
        let fs = h.functions();

        expect_ok("u8 load @32 (last byte)", || {
            (fs.load_u8)(fs.ctx, f.ptr(), 32)
        })?;
        expect_trap("u8 load @33 (one past)", || {
            (fs.load_u8)(fs.ctx, f.ptr(), 33)
        })?;
        // Largest i64 access that fits in 33 bytes starts at 25.
        expect_ok("i64 load @25", || (fs.load_i64)(fs.ctx, f.ptr(), 25))?;
        expect_trap("i64 load @26", || (fs.load_i64)(fs.ctx, f.ptr(), 26))?;

        f.check_canaries("upper_last_byte_of_unaligned_allocation")?;
        Ok(())
    }

    // ========================================================================
    // 4. LOWER BOUNDARY
    // ========================================================================
    //
    // `offset` is an unsigned u32, so subtracting below the base borrows out of
    // the field and into the binding. That's permitted — the resulting pointer
    // names a lower binding, which is empty in a clean table, so the access
    // traps. What must never happen is reaching memory below this allocation.

    #[test]
    fn lower_negative_offset_traps() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let fs = h.functions();

        for off in [-1i64, -2, -8, -64, -4096, -(1 << 20)] {
            expect_trap(&format!("load @{off}"), || {
                (fs.load_i64)(fs.ctx, f.ptr(), off)
            })?;
        }

        f.check_canaries("lower_negative_offset_traps")?;
        Ok(())
    }

    #[test]
    fn lower_partial_underflow_from_mid_pointer_traps() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let fs = h.functions();

        // From a mid pointer, small negative deltas stay inside the offset field
        // — no borrow into the binding — so this tests the bounds check itself
        // rather than the empty-slot path.
        let mid = f.ptr_at(16);
        expect_ok("mid load @-16 (back to base)", || {
            (fs.load_i64)(fs.ctx, mid, -16)
        })?;
        for off in [-17i64, -20, -24] {
            expect_trap(&format!("mid load @{off} (below base)"), || {
                (fs.load_i64)(fs.ctx, mid, off)
            })?;
        }

        f.check_canaries("lower_partial_underflow_from_mid_pointer_traps")?;
        Ok(())
    }

    #[test]
    fn lower_explicit_high_offset_traps() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 64);
        let fs = h.functions();

        // Constructed directly rather than derived, so this stays meaningful
        // regardless of how arithmetic wraps.
        for off in [u32::MAX, u32::MAX - 7, 0x8000_0000, 0xFFFF_0000] {
            let p = f.ptr_at(off);
            expect_trap(&format!("load through offset {off:#010x}"), || {
                (fs.load_i64)(fs.ctx, p, 0)
            })?;
        }

        f.check_canaries("lower_explicit_high_offset_traps")?;
        Ok(())
    }

    // ========================================================================
    // 5. BINDING LOOKUP
    // ========================================================================
    //
    // Carry into the binding field is permitted, so the guest can name any
    // binding it likes. That's fine as long as the lookup itself is safe:
    // the index must be masked to the table, and an unregistered slot must trap
    // rather than dereferencing whatever stale bytes are in it.

    /// Bits 48–63 are reachable by carry. If the JIT shifts right by 32 without
    /// masking to 16 bits, the index runs up to 2^32 and the table lookup reads
    /// a base/length pair from far past the array — then dereferences it. That's
    /// an arbitrary host read, not a silent failure, so this is a hard
    /// requirement rather than a "trap or ignore" case.

    #[test]
    fn binding_unregistered_slot_traps() -> Result<()> {
        let mut h = harness();

        // Register then release to learn an in-range but empty binding.
        let vacated = {
            let f = Fixture::new(&mut h, 32);
            f.ptr
        };

        let fs = h.functions();
        expect_trap("load through vacated slot", || {
            (fs.load_from_raw_bits)(fs.ctx, vacated.0)
        })?;
        expect_trap("store through vacated slot", || {
            (fs.store_to_raw_bits)(fs.ctx, vacated.0, -1)
        })?;
        Ok(())
    }

    #[test]
    fn binding_forged_handles_trap_on_empty_table() -> Result<()> {
        let mut h = harness();
        h.reset_allocations();
        let fs = h.functions();

        // Nothing is registered, so every binding is empty and every forged
        // handle must trap — whatever bits the guest picked.
        for raw in [
            u64::MAX,
            u64::MAX - 1,
            0xFFFF_0000_0000_0000,
            0xFFFFu64 << 32,
            0xDEAD_BEEF_DEAD_BEEF,
            0x0001_0000_0000_0000,
        ] {
            expect_trap(&format!("guest-forged load {raw:#018x}"), || {
                (fs.load_from_raw_bits)(fs.ctx, raw)
            })?;
            expect_trap(&format!("guest-forged store {raw:#018x}"), || {
                (fs.store_to_raw_bits)(fs.ctx, raw, -1)
            })?;
        }
        Ok(())
    }

    #[test]
    fn binding_forged_offset_on_live_handle_traps() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 4);
        let before = f.snapshot();
        let fs = h.functions();

        // Real binding, forged offset — the handle is legitimate and only the
        // offset is wrong, so the bounds check is the only thing standing here.
        for off in [32u32, 64, 4096, 0x8000_0000, u32::MAX] {
            let mut bits = f.ptr;
            bits.set_offset(off);
            expect_trap(&format!("forged offset {off:#x}"), || {
                (fs.load_from_raw_bits)(fs.ctx, bits.0)
            })?;
            run_ignoring_trap(|| (fs.store_to_raw_bits)(fs.ctx, bits.0, -1));
            f.check_unchanged(&before, &format!("forged offset {off:#x}"))?;
            f.check_canaries(&format!("forged offset {off:#x}"))?;
        }
        Ok(())
    }

    // ========================================================================
    // 6. DEGENERATE ALLOCATIONS
    // ========================================================================

    #[test]
    fn degenerate_zero_length_rejects_everything() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 0);
        let fs = h.functions();

        expect_trap("u8 load @0 of empty", || (fs.load_u8)(fs.ctx, f.ptr(), 0))?;
        expect_trap("i64 load @0 of empty", || (fs.load_i64)(fs.ctx, f.ptr(), 0))?;
        expect_trap("u8 store @0 of empty", || {
            (fs.store_u8)(fs.ctx, f.ptr(), 0, 1)
        })?;

        f.check_canaries("degenerate_zero_length_rejects_everything")?;
        Ok(())
    }

    /// The `limit = length - access_size` underflow.
    ///
    /// When the allocation is shorter than the access, `length - size` wraps to
    /// a huge unsigned value and every offset passes the compare. Easy to ship,
    /// because natural test cases all use allocations comfortably larger than
    /// one element. Needs an explicit `length < access_size` guard.
    #[test]
    fn degenerate_allocation_smaller_than_access_size() -> Result<()> {
        let mut h = harness();

        for len in 1..(I64_SIZE as usize) {
            let f = Fixture::new(&mut h, len);
            let fs = h.functions();

            expect_trap(
                &format!("i64 load from {len}-byte allocation (limit underflow)"),
                || (fs.load_i64)(fs.ctx, f.ptr(), 0),
            )?;
            expect_trap(
                &format!("i64 store to {len}-byte allocation (limit underflow)"),
                || (fs.store_i64)(fs.ctx, f.ptr(), 0, -1),
            )?;
            f.check_canaries(&format!("{len}-byte allocation"))?;
        }
        Ok(())
    }

    #[test]
    fn degenerate_u8_access_still_works_on_tiny_allocation() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 1);
        let fs = h.functions();

        // The fix for the case above must not be "reject small allocations".
        expect_ok("u8 load @0 of 1-byte alloc", || {
            (fs.load_u8)(fs.ctx, f.ptr(), 0)
        })?;
        expect_trap("u8 load @1 of 1-byte alloc", || {
            (fs.load_u8)(fs.ctx, f.ptr(), 1)
        })?;

        f.check_canaries("degenerate_u8_access_still_works_on_tiny_allocation")?;
        Ok(())
    }

    // ========================================================================
    // 7. LIFECYCLE
    // ========================================================================

    #[test]
    fn lifecycle_many_allocations_are_independent() -> Result<()> {
        let mut h = harness();

        let mut fixtures = Vec::new();
        for i in 0..32 {
            fixtures.push(Fixture::marked(&mut h, 4, 0x100 + i as i64));
        }

        let mut seen = std::collections::HashSet::new();
        for f in &fixtures {
            if !seen.insert(f.ptr) {
                bail!("add_allocation handed out binding {} twice", f.ptr);
            }
        }

        let fs = h.functions();
        for (i, f) in fixtures.iter().enumerate() {
            let want = 0x100 + i as i64;
            let got = expect_ok(&format!("alloc {i} load @0"), || {
                (fs.load_i64)(fs.ctx, f.ptr(), 0)
            })?;
            if got != want {
                bail!(
                    "alloc {i} (binding {}): expected {want:#x}, got {got:#x}",
                    f.ptr
                );
            }
            expect_trap(&format!("alloc {i} load @32 (past end)"), || {
                (fs.load_i64)(fs.ctx, f.ptr(), 32)
            })?;
        }

        for f in &fixtures {
            f.check_canaries("lifecycle many")?;
        }
        Ok(())
    }

    #[test]
    fn lifecycle_removing_one_leaves_others_usable() -> Result<()> {
        let mut h = harness();

        let a = Fixture::marked(&mut h, 4, 0xAAAA);
        let b = Fixture::marked(&mut h, 4, 0xBBBB);
        let c = Fixture::marked(&mut h, 4, 0xCCCC);

        let b_ptr = b.ptr();
        drop(b);

        let fs = h.functions();
        expect_trap("load from removed b", || (fs.load_i64)(fs.ctx, b_ptr, 0))?;

        let got_a = expect_ok("load a after removing b", || {
            (fs.load_i64)(fs.ctx, a.ptr(), 0)
        })?;
        let got_c = expect_ok("load c after removing b", || {
            (fs.load_i64)(fs.ctx, c.ptr(), 0)
        })?;
        if got_a != 0xAAAA || got_c != 0xCCCC {
            bail!("removing b disturbed its neighbours: a={got_a:#x}, c={got_c:#x}");
        }

        a.check_canaries("lifecycle a")?;
        c.check_canaries("lifecycle c")?;
        Ok(())
    }

    #[test]
    fn lifecycle_double_remove_is_harmless() -> Result<()> {
        let mut h = harness();

        let binding = {
            let f = Fixture::new(&mut h, 32);
            f.ptr
        };
        h.ctx_mut().remove_allocation(binding); // second removal

        let g = Fixture::marked(&mut h, 2, 0x5150);
        let fs = h.functions();
        let got = expect_ok("load after double remove", || {
            (fs.load_i64)(fs.ctx, g.ptr(), 0)
        })?;
        if got != 0x5150 {
            bail!("allocation table damaged by double remove (read {got:#x})");
        }

        g.check_canaries("double remove")?;
        Ok(())
    }

    #[test]
    fn lifecycle_use_after_revoke_traps() -> Result<()> {
        let mut h = harness();

        let ptr = {
            let f = Fixture::of_i64s(&mut h, 8);
            let p = f.ptr();
            let fs = h.functions();
            expect_ok("load before revoke", || (fs.load_i64)(fs.ctx, p, 0))?;
            p
        };

        let fs = h.functions();
        expect_trap("load after revoke", || (fs.load_i64)(fs.ctx, ptr, 0))?;
        expect_trap("store after revoke", || (fs.store_i64)(fs.ctx, ptr, 0, -1))?;
        Ok(())
    }

    /// Slot reuse. `add_allocation` returns the first free slot, so release and
    /// re-register hands the same index back — and a stale `BSPtr` then names
    /// the new allocation.
    ///
    /// This FAILS without a generation counter in the handle. That's the point:
    /// it's the demonstration that a bare 16-bit index can't distinguish
    /// generations. Unlike the carry cases, this one isn't a silent
    /// wrong-allocation read the guest caused itself — the host revoked the
    /// handle and the guest kept using it. Leave it red until generations land.
    #[test]
    fn lifecycle_slot_reuse_does_not_resurrect_stale_handle() -> Result<()> {
        let mut h = harness();

        let (stale, first_binding) = {
            let first = Fixture::marked(&mut h, 8, 0x1111);
            (first.ptr(), first.ptr)
        };

        let second = Fixture::marked(&mut h, 8, 0x2222);
        if second.ptr != first_binding {
            eprintln!("note: slot not reused, reuse test inconclusive");
            return Ok(());
        }

        let fs = h.functions();
        match unsafe { brane_core::sandbox::try_run(&mut || (fs.load_i64)(fs.ctx, stale, 0)) } {
            Err(_) => Ok(()),
            Ok(v) if v == 0x2222 => bail!(
                "stale handle to a freed allocation now reads the allocation that reused \
                 its slot (got {v:#x}) — the binding index alone doesn't distinguish \
                 generations"
            ),
            Ok(v) => bail!("stale handle succeeded, returning {v:#x}"),
        }
    }

    #[test]
    fn lifecycle_two_handles_to_same_buffer_are_independent() -> Result<()> {
        let mut h = harness();

        // Register the same memory twice at different lengths. Both handles are
        // legitimate; each carries its own bounds, and revoking one must not
        // affect the other.
        let mut backing = vec![0u8; 64];
        let data = backing.as_mut_ptr();

        let full = h.ctx_mut().add_allocation(data, 64);
        let half = h.ctx_mut().add_allocation(data, 32);
        if full == half {
            bail!("registering the same buffer twice returned the same binding");
        }

        {
            let fs = h.functions();
            let p_full = full;
            let p_half = half;

            expect_ok("full handle load @56", || (fs.load_i64)(fs.ctx, p_full, 56))?;
            expect_ok("half handle load @24", || (fs.load_i64)(fs.ctx, p_half, 24))?;
            // The narrow registration must not inherit the wide one's bounds.
            expect_trap("half handle load @32", || (fs.load_i64)(fs.ctx, p_half, 32))?;
            expect_trap("half handle load @56", || (fs.load_i64)(fs.ctx, p_half, 56))?;
        }

        h.ctx_mut().remove_allocation(half);

        let fs = h.functions();
        expect_trap("revoked half handle", || (fs.load_i64)(fs.ctx, half, 0))?;
        expect_ok("full handle survives half's revocation", || {
            (fs.load_i64)(fs.ctx, full, 56)
        })?;

        h.ctx_mut().remove_allocation(full);
        Ok(())
    }

    #[test]
    fn lifecycle_churn_does_not_leak_slots() -> Result<()> {
        let mut h = harness();

        // If remove_allocation ever failed to free a slot, this would exhaust
        // the table and add_allocation would panic.
        for round in 0..500 {
            let f = Fixture::marked(&mut h, 4, 0x7000 + round as i64);
            let fs = h.functions();
            println!("Round {} ptr {}", round, f.ptr);

            let got = expect_ok("churn load", || (fs.load_i64)(fs.ctx, f.ptr(), 0))?;
            if got != 0x7000 + round as i64 {
                bail!(
                    "churn round {round}: expected {:#x}, got {got:#x}",
                    0x7000 + round
                );
            }
            expect_trap("churn oob", || (fs.load_i64)(fs.ctx, f.ptr(), 32))?;
            f.check_canaries(&format!("churn round {round}"))?;
        }
        Ok(())
    }

    // ========================================================================
    // 8. ISOLATION
    // ========================================================================
    //
    // Carry into the binding field is permitted, so "a pointer derived from a
    // can never name b" is no longer true and there's no test for it. What is
    // still required: an offset that stays inside the 32-bit field can only ever
    // reach the allocation its binding names.
    //
    // Every delta below is chosen to keep the offset in field — positive deltas
    // well under 2^32 from a base offset of 0, and negative deltas smaller than
    // the starting offset — so nothing here relies on carry behaviour.

    #[test]
    fn isolation_in_field_offsets_cannot_leave_the_allocation() -> Result<()> {
        let mut h = harness();

        let a = Fixture::marked(&mut h, 8, 0x1111_1111_1111_1111);
        let b = Fixture::marked(&mut h, 8, 0x2222_2222_2222_2222);
        let fs = h.functions();

        // From a mid pointer so negative deltas don't borrow into the binding.
        let a_mid = a.ptr_at(32);
        for delta in [-64i64, -33, 32, 64, 4096, 1 << 20] {
            match unsafe {
                brane_core::sandbox::try_run(&mut || (fs.load_i64)(fs.ctx, a_mid, delta))
            } {
                Err(_) => {}
                Ok(v) if v == 0x2222_2222_2222_2222 => {
                    bail!(
                        "a+{delta} read b's marker without leaving the offset field — \
                         allocations are not isolated"
                    )
                }
                Ok(v) => bail!("a+{delta} should have trapped but returned {v:#x}"),
            }
        }

        a.check_canaries("isolation a")?;
        b.check_canaries("isolation b")?;
        Ok(())
    }

    #[test]
    fn isolation_two_pointer_copy_checks_both_sides() -> Result<()> {
        let mut h = harness();

        let src = Fixture::of_i64s(&mut h, 8);
        let dst = Fixture::of_i64s(&mut h, 8);
        let fs = h.functions();

        expect_ok("copy in range", || {
            (fs.copy_i64)(fs.ctx, dst.ptr(), 0, src.ptr(), 24)
        })?;
        let after_valid = dst.snapshot();

        // Bad source, good destination: must trap and must not write.
        expect_trap("copy from out-of-range source", || {
            (fs.copy_i64)(fs.ctx, dst.ptr(), 8, src.ptr(), 512)
        })?;
        dst.check_unchanged(&after_valid, "bad source")?;

        // Good source, bad destination.
        expect_trap("copy to out-of-range destination", || {
            (fs.copy_i64)(fs.ctx, dst.ptr(), 512, src.ptr(), 8)
        })?;
        dst.check_unchanged(&after_valid, "bad destination")?;

        src.check_canaries("copy src")?;
        dst.check_canaries("copy dst")?;
        Ok(())
    }

    #[test]
    fn isolation_multi_step_walk_ending_in_range_is_checked_at_the_load() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let fs = h.functions();

        // p + a + b - c, with intermediates far out of range but a final result
        // back inside. Policy: intermediates unchecked, final load checked.
        let got = expect_ok("walk with wild intermediates", || {
            (fs.load_after_walk)(fs.ctx, f.ptr(), 1 << 20, 32, 1 << 20)
        })?;
        if got != 1004 {
            bail!("walk: expected element 4 (1004), got {got}");
        }

        expect_trap("walk ending out of range", || {
            (fs.load_after_walk)(fs.ctx, f.ptr(), 1 << 20, 4096, 1 << 20)
        })?;

        f.check_canaries("isolation_multi_step_walk")?;
        Ok(())
    }

    // ========================================================================
    // 9. NON-CLOBBER
    // ========================================================================
    //
    // Run first. Every other group asks "was the access refused?", which a clamp
    // answers yes to while still writing to the edge of the object. This group
    // asks "did memory change?"

    #[test]
    fn nonclobber_rejected_stores_leave_payload_untouched() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let before = f.snapshot();
        let fs = h.functions();
        let len = f.len();

        let evil = 0xDEAD_BEEF_DEAD_BEEFu64 as i64;
        let offsets = [
            len,     // first byte past the end
            len - 1, // straddles
            len - 7, // straddles by one
            len + 8,
            -1, // below the base
            -8,
            1 << 20,
            -(1 << 20),
        ];

        for off in offsets {
            run_ignoring_trap(|| (fs.store_i64)(fs.ctx, f.ptr(), off, evil));
            f.check_unchanged(&before, &format!("store @{off}"))?;
            f.check_canaries(&format!("store @{off}"))?;
        }
        Ok(())
    }

    #[test]
    fn nonclobber_straddling_stores_write_nothing() -> Result<()> {
        let mut h = harness();
        let f = Fixture::new(&mut h, 64);
        let before = f.snapshot();
        let fs = h.functions();
        let len = f.len();

        // The sharpest version: the start address is in bounds, so a clamp has
        // nothing to clamp and the write may go through in full, spilling past
        // the end into the canary.
        for off in (len - I64_SIZE + 1)..len {
            run_ignoring_trap(|| (fs.store_i64)(fs.ctx, f.ptr(), off, -1));
            f.check_unchanged(&before, &format!("straddling store @{off}"))?;
            f.check_canaries(&format!("straddling store @{off}"))?;
        }
        Ok(())
    }

    #[test]
    fn nonclobber_last_element_survives_out_of_range_stores() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 4);
        let fs = h.functions();

        // A clamp to `length - access_size` lands exactly on the last element,
        // where the canaries can't see it. Read it back explicitly.
        for off in [32i64, 40, 800, 1 << 20] {
            run_ignoring_trap(|| (fs.store_i64)(fs.ctx, f.ptr(), off, 0x4141_4141));
            let last = expect_ok("read last element", || (fs.load_i64)(fs.ctx, f.ptr(), 24))?;
            if last != 1003 {
                bail!(
                    "store @{off} was rejected but the last element changed from 1003 to \
                     {last} — the out-of-range write was clamped into the allocation"
                );
            }
        }

        f.check_canaries("nonclobber_last_element")?;
        Ok(())
    }

    #[test]
    fn nonclobber_first_element_survives_underflow_stores() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 4);
        let fs = h.functions();

        // Mirror case: a clamp to offset 0 lands on the first element.
        for off in [-1i64, -8, -800, -(1 << 20)] {
            run_ignoring_trap(|| (fs.store_i64)(fs.ctx, f.ptr(), off, 0x4242_4242));
            let first = expect_ok("read first element", || (fs.load_i64)(fs.ctx, f.ptr(), 0))?;
            if first != 1000 {
                bail!(
                    "store @{off} was rejected but the first element changed from 1000 to \
                     {first} — the underflowing write was clamped to the base"
                );
            }
        }

        f.check_canaries("nonclobber_first_element")?;
        Ok(())
    }

    // ========================================================================
    // 10. ARITHMETIC POLICY
    // ========================================================================
    //
    // Forming an out-of-range pointer is legal; only the dereference is checked.
    // Pinned here so it can't drift silently.

    #[test]
    fn arithmetic_forming_out_of_range_pointer_is_permitted() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 8);
        let fs = h.functions();

        for off in [64i64, 72, 1 << 16, -1, -(1 << 16), 1 << 33] {
            expect_ok(&format!("form p+{off} without deref"), || {
                (fs.ptr_add_only)(fs.ctx, f.ptr(), off)
            })?;
        }

        f.check_canaries("arithmetic_forming_out_of_range_pointer_is_permitted")?;
        Ok(())
    }

    #[test]
    fn arithmetic_one_past_end_may_be_formed_but_not_loaded() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 8);
        let fs = h.functions();
        let len = f.len();

        expect_ok("form one-past-the-end pointer", || {
            (fs.ptr_add_only)(fs.ctx, f.ptr(), len)
        })?;
        expect_trap("load through one-past-the-end pointer", || {
            (fs.load_i64)(fs.ctx, f.ptr(), len)
        })?;

        f.check_canaries("arithmetic_one_past_end")?;
        Ok(())
    }

    // ========================================================================
    // STRESS
    // ========================================================================

    #[test]
    fn stress_alternating_valid_and_invalid() -> Result<()> {
        let mut h = harness();
        let f = Fixture::of_i64s(&mut h, 16);
        let before = f.snapshot();
        let fs = h.functions();

        // Interleaved, so a check that caches metadata across accesses can't get
        // away with validating only the first in a run.
        for i in 0..500i64 {
            let elem = i % 16;
            let off = elem * I64_SIZE;
            let got = expect_ok("stress valid load", || (fs.load_i64)(fs.ctx, f.ptr(), off))?;
            if got != 1000 + elem {
                bail!("stress: load @{off} returned {got} on iteration {i}");
            }
            let bad = 128 + (i % 64) * I64_SIZE;
            run_ignoring_trap(|| (fs.store_i64)(fs.ctx, f.ptr(), bad, -1));
        }

        f.check_unchanged(&before, "stress")?;
        f.check_canaries("stress")?;
        Ok(())
    }
}
