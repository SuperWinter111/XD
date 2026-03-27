cmake_minimum_required(VERSION 3.20)

add_library(wp04_resmgmt
  src/capability_aggregator.cpp
  src/conflict_arbitration_service.cpp
  src/link_impact_evaluator.cpp
  src/reservation_manager.cpp
  src/resource_registry.cpp
  src/resource_scheduling_service.cpp
  src/resmgmt_application_service.cpp
)

target_include_directories(wp04_resmgmt
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp04_resmgmt PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp04_resmgmt_state_snapshot_test tests/state_snapshot_test.cpp)
  add_executable(wp04_resmgmt_allocation_test tests/allocation_test.cpp)
  add_executable(wp04_resmgmt_partial_test tests/partial_test.cpp)
  add_executable(wp04_resmgmt_reservation_test tests/reservation_test.cpp)

  target_link_libraries(wp04_resmgmt_state_snapshot_test PRIVATE wp04_resmgmt)
  target_link_libraries(wp04_resmgmt_allocation_test PRIVATE wp04_resmgmt)
  target_link_libraries(wp04_resmgmt_partial_test PRIVATE wp04_resmgmt)
  target_link_libraries(wp04_resmgmt_reservation_test PRIVATE wp04_resmgmt)

  target_include_directories(wp04_resmgmt_state_snapshot_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp04_resmgmt_allocation_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp04_resmgmt_partial_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp04_resmgmt_reservation_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  add_test(NAME wp04_resmgmt_state_snapshot_test COMMAND wp04_resmgmt_state_snapshot_test)
  add_test(NAME wp04_resmgmt_allocation_test COMMAND wp04_resmgmt_allocation_test)
  add_test(NAME wp04_resmgmt_partial_test COMMAND wp04_resmgmt_partial_test)
  add_test(NAME wp04_resmgmt_reservation_test COMMAND wp04_resmgmt_reservation_test)
endif()