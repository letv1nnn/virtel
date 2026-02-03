add_executable(virtel_tests
    main.cpp
    scanner_test.cpp
)

target_include_directories(virtel_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(virtel_tests
    virtel_lib    
    gtest
    gtest_main
)

add_test(NAME virtel_tests COMMAND virtel_tests)
