cmake_minimum_required(VERSION 3.20)

add_library(wp06_commnet
  src/commnet_application_service.cpp
  src/degradation_policy_engine.cpp
  src/link_telemetry_collector.cpp
  src/quality_scoring_service.cpp
  src/security_event_bridge.cpp
  src/topology_view_service.cpp
)

target_include_directories(wp06_commnet
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp06_commnet PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp06_commnet_link_quality_test tests/link_quality_test.cpp)
  add_executable(wp06_commnet_degradation_test tests/degradation_test.cpp)
  add_executable(wp06_commnet_security_test tests/security_test.cpp)
  add_executable(wp06_commnet_topology_test tests/topology_test.cpp)

  target_link_libraries(wp06_commnet_link_quality_test PRIVATE wp06_commnet)
  target_link_libraries(wp06_commnet_degradation_test PRIVATE wp06_commnet)
  target_link_libraries(wp06_commnet_security_test PRIVATE wp06_commnet)
  target_link_libraries(wp06_commnet_topology_test PRIVATE wp06_commnet)

  target_include_directories(wp06_commnet_link_quality_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp06_commnet_degradation_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp06_commnet_security_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp06_commnet_topology_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  add_test(NAME wp06_commnet_link_quality_test COMMAND wp06_commnet_link_quality_test)
  add_test(NAME wp06_commnet_degradation_test COMMAND wp06_commnet_degradation_test)
  add_test(NAME wp06_commnet_security_test COMMAND wp06_commnet_security_test)
  add_test(NAME wp06_commnet_topology_test COMMAND wp06_commnet_topology_test)
endif()