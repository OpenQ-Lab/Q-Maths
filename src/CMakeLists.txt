add_library(Q-Maths)

target_sources(Q-Maths
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include
        FILES
        ${CMAKE_SOURCE_DIR}/include/complex/complexNb.hpp
)

target_include_directories(Q-Maths PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(Q-Maths PRIVATE /W4)
else()
    target_compile_options(Q-Maths PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(complex)