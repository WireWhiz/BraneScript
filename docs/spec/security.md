 # Security 
 BraneScript is intended to be downloaded from untrusted sources, thus proper sandboxing is key.

 # Taking Inspiration from WASM

When researching potential scripting solutions for BraneEngine, WASM was thoroughly investigated as an option. While I got the base functionality working, all of my main requirements for the engine are only served by proposals with varying support and implementations, additionally WASM is impossible to debug with a tool like LLDB. 

However there are lessons to be learned from the security measures taken by the WASM spec and popular runtimes. The main and most important one is not allowing direct pointer operations, and instead making all memory operations relative to an unknown offset. This makes it nearly impossible to reliably access the memory of the host environment or other stores of virtualized memory. Additionally many runtimes will set guard pages around these blocks of memory to catch out-of-bounds access.

I particularly like the idea of splitting up memory into blocks and controlling access to those blocks, as that system could double as a thread safe memory access scheme, while also providing security

# Security Measures

The build pipeline will output a RISC (Reduced Instruction Set) bytecode, this allows us to constrict possible operations to only those that we want to allow, for example direct memory access by address is impossible because when that bytecode is compiled the safety is added on the client's side. 

Memory access will granted by region, where regions of memory are passed around to functions as arguments or are fetched as handles.

Guard registers will be investigated as well.