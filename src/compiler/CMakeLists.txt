find_package(robin_hood)
find_package(jsoncpp)


add_library(BraneScriptCompiler STATIC
        analyzer.cpp
        documentContext.cpp

        functionCallTree.cpp
        constexprEvaluator.cpp
        ast/ast.cpp
        ast/ast.h
        ast/statements.h
        ast/expressions.h
        ast/module.h
        ast/source.h
        ../documentBackend/documentSource.h
        ../documentBackend/documentReader.cpp
        ../documentBackend/documentReader.h)
target_link_libraries(BraneScriptCompiler PUBLIC BraneScriptRuntime antlr4 JsonCpp::JsonCpp)
target_include_directories(BraneScriptCompiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${robin_hood_INCLUDE_DIRS} ../scriptRuntime)

target_compile_definitions(BraneScriptCompiler PUBLIC LLVM_LINK_COMPONENTS WebAssembly)