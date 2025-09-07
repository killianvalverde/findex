find_package(speed REQUIRED)

set(debug_suffix "$<IF:$<CONFIG:Debug>,d,>")

set(FF_SOURCE_FILES
        exception.hpp
        program.cpp
        program.hpp
        program_args.hpp
        ff.hpp
)

add_library(ff STATIC ${FF_SOURCE_FILES})
target_link_libraries(ff speed::speed)
set_target_properties(ff PROPERTIES OUTPUT_NAME ff${debug_suffix})
