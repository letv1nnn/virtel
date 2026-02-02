set(CMAKE_CXX_STANDARD 17)

add_executable(virtel
    main.cpp
    runner.cpp
    scanner.cpp
    token.cpp
)

target_include_directories(virtel
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
