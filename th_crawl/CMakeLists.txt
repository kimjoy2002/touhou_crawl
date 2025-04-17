cmake_minimum_required(VERSION 3.15)
project(th_crawl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type" FORCE)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "" FORCE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug" CACHE STRING "" FORCE)
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" CACHE STRING "" FORCE)
endif()


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else()
    set(ARCH "Win32")
endif()

add_compile_options(/utf-8 /wd4819 /FS)
if (MSVC)
    add_definitions(-D_HAS_STD_BYTE=0)
endif()





set(DirectXTK "F:/Download/DirectXTK-main/DirectXTK-main/")
include_directories(${DirectXTK}/Inc)
link_directories(${DirectXTK}/Bin/Desktop_2019/x64/Debug)
set(DirectXTK_LIB DirectXTK)



set(STEAMWORKS_SDK "E:/steamworks_sdk/sdk")
include_directories(${STEAMWORKS_SDK}/public)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    link_directories(${STEAMWORKS_SDK}/redistributable_bin/win64)
    set(STEAM_API_LIB steam_api64)
else()
    link_directories(${STEAMWORKS_SDK}/redistributable_bin)
    set(STEAM_API_LIB steam_api)
endif()

file(GLOB_RECURSE SRC_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32 _WINDOWS)
target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:WINDOWS)
target_link_libraries(${PROJECT_NAME} d3d11 ${STEAM_API_LIB} ${DirectXTK_LIB})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug Build")

    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message("Use Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            /Od
            -Wno-comment
            -Wno-new-returns-null
            -Wno-microsoft-enum-forward-reference
            -Wno-microsoft-extra-qualification
            -Wno-deprecated-declarations
            /MDd
        )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message("Use MSVC")
        target_compile_options(${PROJECT_NAME} PRIVATE /MDd)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Ob0 /Od")
        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Debug)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Debug)

else()
    message("Release Build")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wno-comment
        -Wno-new-returns-null
        -Wno-microsoft-enum-forward-reference
        -Wno-microsoft-extra-qualification
        -Wno-deprecated-declarations
        -Od
        -Zi
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -fsanitize=address
        -Zi
    )

    execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Release)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Release)
endif()

set(DLL_FILES
    "${CMAKE_SOURCE_DIR}/dll/msvcp100.dll"
    "${CMAKE_SOURCE_DIR}/dll/msvcr100.dll"
    "${CMAKE_SOURCE_DIR}/dll/D3DX9_43.dll"
    "${CMAKE_SOURCE_DIR}/dll/steam_api64.dll"
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