# Brane Script

Embeddable scripting language in development with and intended for use in [Brane Engine](https://github.com/WireWhiz/BraneEngine).

## Why not use a different language?

Brane script is being developed with the goal of creating a high performance embeddable 
statically typed scripting system for ECS based game engines. BS functions are AOT optimized
to a cross-platform IR and jit compiled to allow native speeds. With a focus on runtime 
loading and linking for highly modular use cases.

## Building
We use the conan package manager version 1.x, we will update to conan 2.x once all our dependencies supported by the new version, for now install it with:
```
pip install --upgrade conan==1.59
conan profile update settings.compiler.libcxx=libstdc++11 default
```
If you wish to edit the grammar file, you will also need [Antlr](https://www.antlr.org/download.html).

Cmake automatically calls conan to instal the dependencies so all you need to run is:
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
