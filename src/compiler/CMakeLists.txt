find_package(robin_hood)
find_package(jsoncpp)
find_package(LLVM)

add_library(BraneScriptCompiler STATIC
        staticAnalysis/staticAnalyzer.cpp
        staticAnalysis/documentContext.cpp

        staticAnalysis/functionCallTree.cpp
        staticAnalysis/constexprEvaluator.cpp)
target_link_libraries(BraneScriptCompiler PUBLIC BraneScriptRuntime antlr4 JsonCpp::JsonCpp LLVM::LLVMAsmPrinter LLVM::LLVMX86CodeGen)
target_include_directories(BraneScriptCompiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${robin_hood_INCLUDE_DIRS} ../scriptRuntime)

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/include)
file(COPY staticAnalysis/nativeIncludes/BraneScript.bs DESTINATION ${EXECUTABLE_OUTPUT_PATH}/include)