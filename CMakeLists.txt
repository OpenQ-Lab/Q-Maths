cmake_minimum_required(VERSION 3.28)

project(Q-Maths
        VERSION 1.0.0
        DESCRIPTION "Library for quantum mathematical operations"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

# Installation: lets other projects use the library with find_package(QMaths)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(QMATHS_CMAKE_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/QMaths)

install(TARGETS Q-Maths
        EXPORT QMathsTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT QMathsTargets
        FILE QMathsTargets.cmake
        NAMESPACE QMaths::
        DESTINATION ${QMATHS_CMAKE_INSTALL_DIR}
)

configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/QMathsConfig.cmake.in
        ${PROJECT_BINARY_DIR}/QMathsConfig.cmake
        INSTALL_DESTINATION ${QMATHS_CMAKE_INSTALL_DIR}
)

write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/QMathsConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        ${PROJECT_BINARY_DIR}/QMathsConfig.cmake
        ${PROJECT_BINARY_DIR}/QMathsConfigVersion.cmake
        DESTINATION ${QMATHS_CMAKE_INSTALL_DIR}
)
