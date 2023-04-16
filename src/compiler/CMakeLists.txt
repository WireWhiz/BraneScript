find_package(robin_hood)
find_package(jsoncpp)

add_library(BraneScriptCompiler STATIC
        compiler.cpp
        staticAnalysis/staticAnalyzer.cpp
        staticAnalysis/documentContext.cpp

        aotNodes/aotFlowNodes.cpp
        aotNodes/aotNode.cpp
        aotNodes/aotValueNodes.cpp
        aotNodes/aotModifierNodes.cpp
        aotNodes/aotLogicNodes.cpp

        aotInlineFunctions/aotInlineFunction.cpp
        aotInlineFunctions/aotNativeOperators.cpp
        staticAnalysis/functionCallTree.cpp)
target_link_libraries(BraneScriptCompiler PUBLIC BraneScriptRuntime antlr4 JsonCpp::JsonCpp)
target_include_directories(BraneScriptCompiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${robin_hood_INCLUDE_DIRS} ../scriptRuntime)

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/include)
file(COPY staticAnalysis/nativeIncludes/BraneScript.bs DESTINATION ${EXECUTABLE_OUTPUT_PATH}/include)