cmake_minimum_required(VERSION 3.15)

project(th_crawl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type" FORCE)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else()
    set(ARCH "Win32")
endif()

if (MSVC)
    add_definitions(-D_HAS_STD_BYTE=0)
endif()

set(DIRECTX_SDK "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")

add_compile_options(/FS)
include_directories(
    ${DIRECTX_SDK}/Include
)

link_directories(
    ${DIRECTX_SDK}/Lib/${ARCH}
)


file(GLOB_RECURSE SRC_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32 _WINDOWS)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE /MDd)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Ob0 /Od /RTC1")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Debug
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Debug
    )
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE /MD)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Release
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Release
    )
endif()


target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:WINDOWS)

target_link_libraries(${PROJECT_NAME} d3d9 d3dx9)


set(DLL_FILES
    "${CMAKE_SOURCE_DIR}/dll/msvcp100.dll"
    "${CMAKE_SOURCE_DIR}/dll/msvcr100.dll"
    "${CMAKE_SOURCE_DIR}/dll/D3DX9_43.dll"
)
foreach(DLL ${DLL_FILES})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endforeach()


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data/temp"
)