add_subdirectory(lspServer)
add_subdirectory(antlr4)

add_library(DocumentBackend STATIC
        documentReader.cpp
        parser.cpp
)

target_link_libraries(DocumentBackend PUBLIC BraneScriptCompiler antlr4)