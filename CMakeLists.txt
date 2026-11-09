cmake_minimum_required(VERSION 3.23)

# Must be set BEFORE project() -- ignored on non-Apple hosts.
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum macOS version")

# Only line you rename per project. The target below follows automatically.
project(2048-Game-)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
        main.cpp
)

# ---------------------------------------------------------------------------
# Warnings and source encoding
# ---------------------------------------------------------------------------
if(MSVC)
    # /utf-8 stops MSVC guessing the source encoding from a BOM.
    # Without it, a literal like "12,50 EUR" is mangled at COMPILE time.
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8 /W4)
else()
    # GCC and Clang already assume UTF-8 source.
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---------------------------------------------------------------------------
# Windows: fully standalone .exe
# ---------------------------------------------------------------------------
# -static covers libgcc, libstdc++ AND libwinpthread. Without it the binary
# runs fine under Wine (which finds the DLLs on your Linux system) and then
# fails on real Windows with a missing-DLL dialog.
if(MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE -static)
endif()

# Print the .exe's DLL imports after every Windows build, so a non-static
# binary can never leave the machine unnoticed. Only Windows system DLLs
# (KERNEL32.dll, msvcrt.dll, ...) should appear.
if(MINGW AND CMAKE_HOST_UNIX)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "-- Imported DLLs:"
            COMMAND sh -c "x86_64-w64-mingw32-objdump -p '$<TARGET_FILE:${PROJECT_NAME}>' | grep 'DLL Name' || true"
            VERBATIM
    )
endif()
