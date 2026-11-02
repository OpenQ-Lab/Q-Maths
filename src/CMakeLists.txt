add_library(Q-Maths)
add_library(QMaths::QMaths ALIAS Q-Maths)

set_target_properties(Q-Maths PROPERTIES EXPORT_NAME QMaths)

target_compile_features(Q-Maths PUBLIC cxx_std_23)

target_sources(Q-Maths
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES
        ${PROJECT_SOURCE_DIR}/include/complex/complexNb.hpp
)

# Only impose our warnings when Q-Maths is built on its own, not when embedded in another project
if(PROJECT_IS_TOP_LEVEL)
    if(MSVC)
        target_compile_options(Q-Maths PRIVATE /W4)
    else()
        target_compile_options(Q-Maths PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

add_subdirectory(complex)
