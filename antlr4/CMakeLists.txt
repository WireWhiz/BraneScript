find_package(antlr4-runtime)
message(${antlr4-cppruntime_INCLUDE_DIRS})

add_library(antlr4 braneBaseVisitor.cpp braneLexer.cpp braneParser.cpp braneVisitor.cpp)
target_include_directories(antlr4 PUBLIC ${antlr4-cppruntime_INCLUDE_DIRS})
target_link_libraries(antlr4 PUBLIC antlr4-cppruntime::antlr4-cppruntime)

target_compile_definitions(antlr4 PUBLIC ANTLR4CPP_STATIC)