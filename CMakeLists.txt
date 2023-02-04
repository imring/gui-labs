cmake_minimum_required(VERSION 3.16)

project(gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(QT_VERSION 6)

# https://stackoverflow.com/a/7788165
MACRO(subdirlist result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

set(LABS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/)
subdirlist(SUBDIRS ${LABS_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
    if(EXISTS "${LABS_SOURCE_DIR}/${subdir}/CMakeLists.txt")
        add_subdirectory(${LABS_SOURCE_DIR}/${subdir})
    else()
        file(GLOB SOURCES "${LABS_SOURCE_DIR}/${subdir}/*.cpp")
        add_executable(${subdir} ${SOURCES})
    endif()
endforeach()