find_package(asio)
find_package(jsoncpp)
find_package(robin_hood)

add_executable(BraneScriptLspServer
        main.cpp
        lspServer.cpp
        lspMessage.cpp tokenSerializer.cpp tokenSerializer.h)
target_compile_definitions(BraneScriptLspServer PUBLIC )
target_link_libraries(BraneScriptLspServer PUBLIC asio::asio JsonCpp::JsonCpp BraneScriptCompiler)
target_include_directories(BraneScriptLspServer PUBLIC ${robin_hood_INCLUDE_DIRS})