include(FetchContent)

FetchContent_Declare(
    speed
    GIT_REPOSITORY https://github.com/killianvalverde/speed.git
    GIT_TAG develop
)

FetchContent_MakeAvailable(speed)

set(FF_SOURCE_FILES
        exception.hpp
        program.cpp
        program.hpp
        program_args.hpp
        ff.hpp
)

add_library(ff STATIC ${FF_SOURCE_FILES})

set_target_properties(ff PROPERTIES OUTPUT_NAME "ff$<IF:$<CONFIG:Debug>,d,>")

target_link_libraries(ff PUBLIC speed)

target_include_directories(ff PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
