add_executable(ff_test)

target_sources(ff_test PRIVATE
    main.cpp
    program_test.cpp
)

target_link_libraries(ff_test PRIVATE ff::ff GTest::gtest_main)

set_target_properties(ff_test PROPERTIES DEBUG_POSTFIX d)

include(GoogleTest)

gtest_discover_tests(ff_test DISCOVERY_TIMEOUT 30)
