project(findex_test)

include_directories(${PROJECT_SOURCE_DIR}/../../src)

set(GTEST_LIBRARIES gtest gtest_main)

set(FINDEX_TEST_SOURCE_FILES
        program_test.cpp
)

add_executable(findex_test
        main.cpp
        ${FINDEX_TEST_SOURCE_FILES}
)

target_link_libraries(findex_test findex ${GTEST_LIBRARIES})
