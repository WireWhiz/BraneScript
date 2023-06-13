# Tool to be used for generating client side loadable modules, such as the native includes

add_executable(bsCLI main.cpp)
target_include_directories(bsCLI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)
target_link_libraries(bsCLI PRIVATE BraneScriptCompiler BraneScriptRuntime)