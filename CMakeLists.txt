cmake_minimum_required(VERSION 3.0.0)
project(partA VERSION 0.1.0)

include(CTest)
enable_testing()

SET(CXX_PART_A_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -IpartA")
SET(CXX_PART_B_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -IpartA -IpartB")
SET(CXX_PART_C_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG -IpartA -IpartB -IpartC")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

SET(SOURCES_PART_A partA/date_wrap partA/exceptions)
SET(SOURCES_PART_B partB/base_event partB/closed_event partB/custom_event partB/event_container partB/festival partB/one_time_event partB/open_event partB/recurring_event)
SET(SOURCES_PART_C partC/schedule)

link_directories(partA)
add_executable(progA partA/test_partA ${SOURCES_PART_A})
# add_executable(progB partB/test_partB ${SOURCES_PART_A} ${SOURCES_PART_B})
# add_executable(progC partC/test_partC.cpp ${SOURCES_PART_A} ${SOURCES_PART_B} ${SOURCES_PART_C})
target_link_libraries(progA libdate.a)
# target_link_libraries(progB libdate.a)
# target_link_libraries(progC libdate.a)
target_include_directories(progA PUBLIC partA)
# target_include_directories(progB PUBLIC partA partB)
# target_include_directories(progC PUBLIC partA partB partC)

find_package(GTest CONFIG REQUIRED)
add_executable(testA partA/test_partA_full.cpp ${SOURCES_PART_A})
target_link_libraries(testA libdate.a gtest gtest_main rt pthread)
target_include_directories(testA PUBLIC partA)
add_test(testA testA)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
