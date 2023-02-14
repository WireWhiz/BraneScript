find_package(robin_hood)
find_package(jsoncpp)

add_library(BraneScriptCompiler STATIC
        #compiler.cpp
        #operator.cpp
        staticAnalysis/staticAnalyzer.cpp
        staticAnalysis/documentContext.cpp)
target_link_libraries(BraneScriptCompiler PUBLIC antlr4 jsoncpp::jsoncpp)
target_include_directories(BraneScriptCompiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${robin_hood_INCLUDE_DIRS})