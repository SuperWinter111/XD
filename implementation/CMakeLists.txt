cmake_minimum_required(VERSION 3.20)

project(BmsImplementation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BMS_BUILD_TESTS "Build package smoke tests" ON)

if(BMS_BUILD_TESTS)
	enable_testing()
endif()

add_subdirectory(wp01_battlectrl)
add_subdirectory(wp02_taskmgmt)
add_subdirectory(wp03_sitmgmt)
add_subdirectory(wp04_resmgmt)
add_subdirectory(wp05_enhanceunit)
add_subdirectory(wp06_commnet)
add_subdirectory(wp07_msgservice)
add_subdirectory(wp08_knowledgerule)
add_subdirectory(wp09_authaudit)
add_subdirectory(wp10_monitorlog)
