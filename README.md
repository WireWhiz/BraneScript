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

## Building
We use the conan package manager, if you don't have it already, [download it here](https://conan.io/downloads.html).<br>
If you wish to edit the grammar file, you will also need [Antlr](https://www.antlr.org/download.html).

Cmake automatically installs the dependencies so all you need to run is:
```  
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=[Debug or Release] -DBUILD_TESTS=[ON/OFF]
cmake --build
```

### CMake options
* BUILD_TESTS<br>
builds tests target
* BS_BUILD_EXECUTABLE<br>
builds compiler example (wip)
