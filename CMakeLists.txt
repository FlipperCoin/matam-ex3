cmake_minimum_required(VERSION 3.0.0)
project(partA VERSION 0.1.0)

include(CTest)
enable_testing()

set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror -o")
set(MTM_FLAGS_RELEASE "$-DNDEBUG {MTM_FLAGS_DEBUG}")
set(CMAKE_C++_FLAGS ${MTM_FLAGS_DEBUG} )

SET(SOURCES_PART_A partA/date_wrap partA/exceptions)
SET(SOURCES_PART_B partB/base_event partB/closed_event partB/custom_event partB/event_container partB/festival partB/one_time_event partB/open_event partB/recurring_event partB/vector.h)
SET(SOURCES_PART_C partC/schedule)

add_library(date partA/date.c partA/date.h)

link_directories(partA)
#add_test(testB testB)

add_executable(testB partB/test_partB.cpp ${SOURCES_PART_A} ${SOURCES_PART_B} )
target_link_libraries(testB date)
target_include_directories(testB PUBLIC partA)
target_include_directories(testB PUBLIC partB)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
