add_library("${PROJECT_NAME}" "")

target_include_directories(virtel_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR/include}
)

set(CMAKE_CXX_STANDARD 17)

add_executable(virtel
    main.cpp
    debug.cpp
    runner.cpp
    scanner.cpp
    token.cpp
)

target_link_libraries(virtel PRIVATE virtel_lib)
