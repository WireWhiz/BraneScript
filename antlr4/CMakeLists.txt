add_library(antlr4 braneBaseVisitor.cpp braneLexer.cpp braneParser.cpp braneVisitor.cpp)
target_include_directories(antlr4 PUBLIC include/antlr4 include)
if(UNIX)
    target_link_libraries(antlr4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libantlr4-runtime.a)
elseif(WIN32)
    target_link_libraries(antlr4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr4-runtime-static$<IF:$<CONFIG:Debug>,-db,>.lib)

endif()
target_compile_definitions(antlr4 PUBLIC ANTLR4CPP_STATIC)