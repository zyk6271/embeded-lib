cmake_minimum_required(VERSION 3.22)

# Setup project
project(LwLibPROJECT)

if(NOT PROJECT_IS_TOP_LEVEL)
    add_subdirectory(lwbtn)
else()
    # Set as executable
    add_executable(${PROJECT_NAME})

    # Add key executable block
    target_sources(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/dev/main.c
        ${CMAKE_CURRENT_LIST_DIR}/examples/example_win32.c
        ${CMAKE_CURRENT_LIST_DIR}/examples/test.c
    )

    # Add key include paths
    target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/dev
        ${CMAKE_CURRENT_LIST_DIR}/examples
    )

    # Compilation definition information
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        WIN32
        _DEBUG
        CONSOLE
        LWBTN_DEV
    )

    # Compiler options
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

    # Add subdir with lwbtn and link to project
    add_subdirectory(lwbtn)
    target_link_libraries(${PROJECT_NAME} lwbtn)
endif()
