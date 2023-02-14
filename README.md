# Brane Script

Embeddable scripting language in development with and intended for use in [Brane Engine](https://github.com/WireWhiz/BraneEngine).

## Why not use a different language?

Brane script is being developed with the goal of creating a high performance embeddable 
statically typed scripting system for ECS based game engines. BS functions are AOT optimized
to a cross-platform byte code and jit compiled to allow native speeds. With a focus on runtime 
loading and linking for highly modular use cases. 

### Todo
* Templating system for arrays/vectors
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
