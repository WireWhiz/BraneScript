find_package(antlr4-runtime REQUIRED)

add_library(antlr4 braneBaseVisitor.cpp braneLexer.cpp braneParser.cpp braneVisitor.cpp)
target_link_libraries(antlr4 PUBLIC antlr4-cppruntime::antlr4-cppruntime)
target_include_directories(antlr4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )