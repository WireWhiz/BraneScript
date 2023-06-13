add_subdirectory(scriptRuntime)
add_subdirectory(compiler)
add_subdirectory(lspServer)
add_subdirectory(cliTool)

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/include)
file(COPY bsIncludes/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/include)

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/modules)
file(COPY bsModules/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/modules)