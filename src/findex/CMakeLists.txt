find_package(speed REQUIRED)

set(debug_suffix "$<IF:$<CONFIG:Debug>,d,>")

set(FINDEX_SOURCE_FILES
        exception.hpp
        program.cpp
        program.hpp
        program_args.hpp
        findex.hpp
)

add_library(findex STATIC ${FINDEX_SOURCE_FILES})
target_link_libraries(findex speed::speed)
set_target_properties(findex PROPERTIES OUTPUT_NAME findex${debug_suffix})
