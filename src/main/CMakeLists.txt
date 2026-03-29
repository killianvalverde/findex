add_executable(main)

target_sources(main PRIVATE
    main.cpp
)

target_link_libraries(main PRIVATE ff::ff)

set_target_properties(main PROPERTIES DEBUG_POSTFIX d OUTPUT_NAME ff)

install(TARGETS main RUNTIME DESTINATION bin)
