add_library(ff STATIC)
add_library(ff::ff ALIAS ff)

target_sources(ff
    PRIVATE
    program.cpp
    PUBLIC
    exception.hpp
    ff.hpp
    program.hpp
    program_args.hpp
)

target_link_libraries(ff PUBLIC speed::speed)

target_include_directories(ff PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(ff PROPERTIES DEBUG_POSTFIX d)
