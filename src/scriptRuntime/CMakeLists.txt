find_package(robin_hood)
find_package(LLVM)

add_library(BraneScriptRuntime STATIC
        typeDef.cpp
        scriptRuntime.cpp
        irScript.cpp
        nativeTypes.cpp
        valueIndex.cpp
        functionHandle.cpp
        structDefinition.cpp
        script.cpp
        nativeLibrary.cpp nativeTypes/BSString.cpp nativeTypes/BSString.h)
target_link_libraries(BraneScriptRuntime PUBLIC LLVM::LLVMOrcJIT LLVM::LLVMAsmPrinter LLVM::LLVMX86AsmParser)
target_include_directories(BraneScriptRuntime PUBLIC ${robin_hood_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})