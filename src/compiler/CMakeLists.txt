
add_library(compiler STATIC 
    compiler.cpp
)

target_link_libraries(compiler PUBLIC ir parser)
