find_package(robin_hood)
find_package(jsoncpp)


add_library(BraneScriptCompiler STATIC
        functionCallTree.cpp
        constexprEvaluator.cpp
        ast/ast.cpp
        ast/scopedId.cpp
        ast/astWalker.cpp
        ast/expressions.cpp
        ast/module.cpp)
target_link_libraries(BraneScriptCompiler PUBLIC BraneScriptRuntime JsonCpp::JsonCpp)
target_include_directories(BraneScriptCompiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${robin_hood_INCLUDE_DIRS} ../scriptRuntime)

target_compile_definitions(BraneScriptCompiler PUBLIC LLVM_LINK_COMPONENTS WebAssembly)