find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../src)

set(FINDEX_TEST_SOURCE_FILES
        program_test.cpp
)

add_executable(findex_test
        main.cpp
        ${FINDEX_TEST_SOURCE_FILES}
)

target_link_libraries(findex_test findex ${GTEST_BOTH_LIBRARIES})
