set(MAIN_SOURCE_FILES
    main.cpp
)

add_executable(main ${MAIN_SOURCE_FILES})

set_target_properties(main PROPERTIES OUTPUT_NAME "ff$<IF:$<CONFIG:Debug>,d,>")

target_link_libraries(main PRIVATE ff)

install(TARGETS main DESTINATION bin)
