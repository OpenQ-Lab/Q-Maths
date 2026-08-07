add_library(Q-Maths)

# sub section (cmake)
add_subdirectory(complex)

target_include_directories(Q-Maths PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(Q-Maths PRIVATE /W4)
else()
    target_compile_options(Q-Maths PRIVATE -Wall -Wextra -Wpedantic)
endif()
