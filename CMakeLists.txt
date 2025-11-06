cmake_minimum_required(VERSION 4.0)
project(QBreakpad2
    VERSION 1.0.0
    DESCRIPTION "An open-source multi-platform crash reporting system"
    LANGUAGES C CXX
)
if(WIN32)
    enable_language(RC)
endif()
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release")
endif()
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
foreach(__lang C CXX)
    if(NOT "x${CMAKE_${__lang}_FLAGS}" STREQUAL "x")
        if(MSVC)
            string(REGEX REPLACE " [/-]W[01234] " " " CMAKE_${__lang}_FLAGS ${CMAKE_${__lang}_FLAGS})
        else()
            string(REGEX REPLACE " -W(all)?(extra)? " " " CMAKE_${__lang}_FLAGS ${CMAKE_${__lang}_FLAGS})
            string(REGEX REPLACE " -[W]?pedantic " " " CMAKE_${__lang}_FLAGS ${CMAKE_${__lang}_FLAGS})
        endif()
    endif()
    string(APPEND CMAKE_${__lang}_FLAGS " -w ")
endforeach()
set(__top_level ON)
if("x${CMAKE_PROJECT_SOURCE_DIR}" STREQUAL "x${PROJECT_SOURCE_DIR}")
    message("QBreakpad2: Building as a top-level project.")
else()
    set(__top_level OFF)
    message("QBreakpad2: Building as a subproject.")
endif()
find_package(Qt6 REQUIRED COMPONENTS Core)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
option(QBREAKPAD2_BUILD_SHARED "Build shared library edition of QBreakpad2." ON)
option(QBREAKPAD2_BUILD_STATIC "Build static library edition of QBreakpad2." ON)
option(QBREAKPAD2_INSTALL "Enable installation for QBreakpad2." OFF)
if(NOT QBREAKPAD2_BUILD_SHARED AND NOT QBREAKPAD2_BUILD_STATIC)
    message(SEND_ERROR "You MUST build either the shared library or the static library or both of them!")
endif()
set(__targets)
if(QBREAKPAD2_BUILD_SHARED)
    add_library(${PROJECT_NAME}_shared SHARED)
    add_library(${PROJECT_NAME}::${PROJECT_NAME}_shared ALIAS ${PROJECT_NAME}_shared)
    set(__dllname ${PROJECT_NAME})
    if(NOT MSVC)
        set(__dllname lib${PROJECT_NAME})
    endif()
    set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${__dllname})
    target_compile_definitions(${PROJECT_NAME}_shared PRIVATE QBREAKPAD2_BUILD_LIBRARY)
    if(WIN32)
        target_sources(${PROJECT_NAME}_shared PRIVATE qbreakpad2.rc)
    endif()
    list(APPEND __targets ${PROJECT_NAME}_shared)
endif()
if(QBREAKPAD2_BUILD_STATIC)
    add_library(${PROJECT_NAME}_static STATIC)
    add_library(${PROJECT_NAME}::${PROJECT_NAME}_static ALIAS ${PROJECT_NAME}_static)
    target_compile_definitions(${PROJECT_NAME}_static PUBLIC QBREAKPAD2_BUILD_STATIC)
    list(APPEND __targets ${PROJECT_NAME}_static)
endif()
if(QBREAKPAD2_BUILD_SHARED AND NOT QBREAKPAD2_BUILD_STATIC)
    add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME}_shared)
endif()
if(QBREAKPAD2_BUILD_STATIC AND NOT QBREAKPAD2_BUILD_SHARED)
    add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME}_static)
endif()
set(__BREAKPAD_DIR qbreakpad2/breakpad/src)
add_library(google-breakpad STATIC)
target_include_directories(google-breakpad PUBLIC ${__BREAKPAD_DIR})
if(WIN32)
    target_sources(google-breakpad PRIVATE
        ${__BREAKPAD_DIR}/client/windows/crash_generation/crash_generation_client.cc
        ${__BREAKPAD_DIR}/client/windows/handler/exception_handler.cc
        ${__BREAKPAD_DIR}/common/windows/guid_string.cc
    )
    if(__top_level)
        target_compile_definitions(google-breakpad PRIVATE
            UNICODE _UNICODE
            NOMINMAX
            _USE_MATH_DEFINES
            WIN32_LEAN_AND_MEAN
        )
    endif()
endif()
if(__top_level AND MSVC)
    target_compile_options(google-breakpad PRIVATE
        /utf-8 /Zc:__cplusplus
        $<$<NOT:$<CONFIG:Debug>>:/Gw /Gy /Zc:inline>
    )
endif()
if(UNIX)
    target_sources(google-breakpad PRIVATE
        ${__BREAKPAD_DIR}/client/minidump_file_writer.cc
        ${__BREAKPAD_DIR}/common/convert_UTF.cc
        ${__BREAKPAD_DIR}/common/md5.cc
        ${__BREAKPAD_DIR}/common/string_conversion.cc
    )
endif()
if(APPLE)
    target_sources(google-breakpad PRIVATE
        ${__BREAKPAD_DIR}/client/mac/crash_generation/crash_generation_client.cc
        ${__BREAKPAD_DIR}/client/mac/handler/breakpad_nlist_64.cc
        ${__BREAKPAD_DIR}/client/mac/handler/dynamic_images.cc
        ${__BREAKPAD_DIR}/client/mac/handler/exception_handler.cc
        ${__BREAKPAD_DIR}/client/mac/handler/minidump_generator.cc
        ${__BREAKPAD_DIR}/common/mac/MachIPC.mm
        ${__BREAKPAD_DIR}/common/mac/bootstrap_compat.cc
        ${__BREAKPAD_DIR}/common/mac/file_id.cc
        ${__BREAKPAD_DIR}/common/mac/macho_id.cc
        ${__BREAKPAD_DIR}/common/mac/macho_utilities.cc
        ${__BREAKPAD_DIR}/common/mac/macho_walker.cc
        ${__BREAKPAD_DIR}/common/mac/string_utilities.cc
    )
endif()
if(LINUX)
    target_sources(google-breakpad PRIVATE
        ${__BREAKPAD_DIR}/client/linux/crash_generation/crash_generation_client.cc
        ${__BREAKPAD_DIR}/client/linux/dump_writer_common/thread_info.cc
        ${__BREAKPAD_DIR}/client/linux/dump_writer_common/ucontext_reader.cc
        ${__BREAKPAD_DIR}/client/linux/handler/exception_handler.cc
        ${__BREAKPAD_DIR}/client/linux/handler/minidump_descriptor.cc
        ${__BREAKPAD_DIR}/client/linux/log/log.cc
        ${__BREAKPAD_DIR}/client/linux/microdump_writer/microdump_writer.cc
        ${__BREAKPAD_DIR}/client/linux/minidump_writer/linux_core_dumper.cc
        ${__BREAKPAD_DIR}/client/linux/minidump_writer/linux_dumper.cc
        ${__BREAKPAD_DIR}/client/linux/minidump_writer/linux_ptrace_dumper.cc
        ${__BREAKPAD_DIR}/client/linux/minidump_writer/minidump_writer.cc
        ${__BREAKPAD_DIR}/common/linux/breakpad_getcontext.S
        ${__BREAKPAD_DIR}/common/linux/elfutils.cc
        ${__BREAKPAD_DIR}/common/linux/file_id.cc
        ${__BREAKPAD_DIR}/common/linux/guid_creator.cc
        ${__BREAKPAD_DIR}/common/linux/linux_libc_support.cc
        ${__BREAKPAD_DIR}/common/linux/memory_mapped_file.cc
        ${__BREAKPAD_DIR}/common/linux/safe_readlink.cc
    )
endif()
include(GNUInstallDirs)
foreach(__target IN LISTS __targets)
    target_sources(${__target} PRIVATE
        qbreakpad2/qbreakpad2_global.h
        qbreakpad2/qbreakpad2handler.h qbreakpad2/qbreakpad2handler.cpp
    )
    target_include_directories(${__target} PUBLIC qbreakpad2)
    if(__top_level)
        if(WIN32)
            target_compile_definitions(${__target} PRIVATE
                UNICODE _UNICODE
                NOMINMAX
                _USE_MATH_DEFINES
                WIN32_LEAN_AND_MEAN
            )
        endif()
        if(MSVC)
            target_compile_options(${__target} PRIVATE
                /utf-8 /Zc:__cplusplus
                $<$<NOT:$<CONFIG:Debug>>:/Gw /Gy /Zc:inline>
            )
            target_link_options(${__target} PRIVATE
                $<$<NOT:$<CONFIG:Debug>>:/OPT:REF /OPT:ICF>
            )
        else()
            target_compile_options(${__target} PRIVATE
                $<$<NOT:$<CONFIG:Debug>>:-ffunction-sections -fdata-sections>
            )
            target_link_options(${__target} PRIVATE
                $<$<NOT:$<CONFIG:Debug>>:-Wl,--gc-sections>
            )
        endif()
    endif()
    set_target_properties(${__target} PROPERTIES
        VERSION ${PROJECT_VERSION}
    )
    set(__dep_visibility PRIVATE)
    get_target_property(__type ${__target} TYPE)
    if("x${__type}" STREQUAL "xSTATIC_LIBRARY")
        set(__dep_visibility PUBLIC)
    else()
        set_target_properties(${__target} PROPERTIES
            SOVERSION ${PROJECT_VERSION_MAJOR}
        )
    endif()
    target_link_libraries(${__target} ${__dep_visibility}
        Qt6::Core
        google-breakpad
    )
    if(QBREAKPAD2_INSTALL)
        install(TARGETS ${__target}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
        install(
            FILES qbreakpad2/qbreakpad2_global.h qbreakpad2/qbreakpad2handler.h
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
    endif()
endforeach()
