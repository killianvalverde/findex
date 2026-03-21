find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../src)

set(FF_TEST_SOURCE_FILES
    program_test.cpp
)

add_executable(ff_test
    main.cpp
    ${FF_TEST_SOURCE_FILES}
)

target_link_libraries(ff_test ff ${GTEST_BOTH_LIBRARIES})
