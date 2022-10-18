cmake_minimum_required(VERSION 3.23)
project(mini_stacktrace VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INSTALL_PREFIX "D:/libs/mini-stacktrace")

include(GNUInstallDirs)

add_library(mini_stacktrace INTERFACE)

target_include_directories(
        mini_stacktrace
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(
            mini_stacktrace
            INTERFACE
            dbghelp
    )
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_compile_options(
            mini_stacktrace
            INTERFACE
            -rdynamic
    )
endif()

install(TARGETS mini_stacktrace
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file("${PROJECT_NAME}-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        INSTALL_DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mini-stacktrace DESTINATION include)

add_executable(main main.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")
endif()

target_link_libraries(main mini_stacktrace)
