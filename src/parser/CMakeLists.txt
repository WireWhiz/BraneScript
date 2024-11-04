

find_package(unofficial-tree-sitter CONFIG REQUIRED)

add_library(parser STATIC 
documentParser.cpp
documentContext.cpp
)
target_link_libraries(parser PUBLIC unofficial::tree-sitter::tree-sitter TreeSitterBraneScript types)
