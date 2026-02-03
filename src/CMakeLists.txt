set(CMAKE_CXX_STANDARD 17)

add_library(virtel_lib
    runner.cpp
    scanner.cpp
    token.cpp
)

add_executable(virtel
    main.cpp
)

target_include_directories(virtel_lib
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(virtel
    virtel_lib
)
