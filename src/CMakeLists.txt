include(FetchContent)

find_package(speed CONFIG QUIET)

if(NOT TARGET speed::speed)
    FetchContent_Declare(
        speed
        GIT_REPOSITORY https://github.com/killianvalverde/speed.git
        GIT_TAG develop
    )

    FetchContent_MakeAvailable(speed)
endif()

add_subdirectory(ff)
add_subdirectory(main)
