find_package(GTest REQUIRED)

set(FF_TEST_SOURCE_FILES
    program_test.cpp
)

add_executable(ff_test
    main.cpp
    ${FF_TEST_SOURCE_FILES}
)

target_link_libraries(ff_test PRIVATE ff GTest::gtest GTest::gtest_main)
