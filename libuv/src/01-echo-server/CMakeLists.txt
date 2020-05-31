project(libuv-demo)

add_executable(01-echo-server
    main.cpp
    loop.cpp)

target_link_libraries(01-echo-server uv)

