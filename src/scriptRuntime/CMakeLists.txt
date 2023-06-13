find_package(robin_hood)
find_package(LLVM)

add_library(BraneScriptRuntime STATIC
        typeDef.cpp
        scriptRuntime.cpp
        irScript.cpp
        valueIndex.cpp
        funcRef.cpp
        structDef.cpp
        script.cpp
        nativeLibrary.cpp
        nativeTypes/bsString.cpp
        nativeTypes/bsLambda.cpp
        nativeTypes/bsVector.cpp)
target_link_libraries(BraneScriptRuntime PUBLIC LLVM::LLVMOrcJIT LLVM::LLVMAsmPrinter LLVM::LLVMX86AsmParser)
target_include_directories(BraneScriptRuntime PUBLIC ${robin_hood_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})