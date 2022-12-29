# Brane Script

Embeddable scripting language in development with and intended for use in Brane Engine.

## Justifications for not just using LuaJit or some other scripting language
* Allows for a mix of aot (Ahead of time) optimization and jit compilation to optimize things that would have otherwise 
been slowed down by the custom ecs and mirroring system. Such as allowing for component operations to be handled through 
inlined assembly instead of calling switch statements in a component definition.
* The ability to directly use AST objects in node scripting systems. 
* Guaranteed portability of bytecode  
* C style syntax and strong static typing
* Array indexes of 0
* I want to

### Todo
* Unsigned scalar types
* Strings and arrays/vectors
* Operator overloading
* Constexpr folding refactor (need way to run functions at compile time)
* Separate function for printing out opcode debugging
