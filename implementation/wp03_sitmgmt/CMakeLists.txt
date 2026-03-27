cmake_minimum_required(VERSION 3.20)

add_library(wp03_sitmgmt
  src/attribute_fusion_service.cpp
  src/perception_ingest_service.cpp
  src/sitmgmt_application_service.cpp
  src/situation_summary_service.cpp
  src/threat_assessment_service.cpp
  src/track_association_service.cpp
)

target_include_directories(wp03_sitmgmt
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp03_sitmgmt PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp03_sitmgmt_fused_track_test tests/fused_track_test.cpp)
  add_executable(wp03_sitmgmt_threat_test tests/threat_test.cpp)
  add_executable(wp03_sitmgmt_boundary_test tests/boundary_test.cpp)
  add_executable(wp03_sitmgmt_summary_test tests/summary_test.cpp)

  target_link_libraries(wp03_sitmgmt_fused_track_test PRIVATE wp03_sitmgmt)
  target_link_libraries(wp03_sitmgmt_threat_test PRIVATE wp03_sitmgmt)
  target_link_libraries(wp03_sitmgmt_boundary_test PRIVATE wp03_sitmgmt)
  target_link_libraries(wp03_sitmgmt_summary_test PRIVATE wp03_sitmgmt)

  target_include_directories(wp03_sitmgmt_fused_track_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp03_sitmgmt_threat_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp03_sitmgmt_boundary_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp03_sitmgmt_summary_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  add_test(NAME wp03_sitmgmt_fused_track_test COMMAND wp03_sitmgmt_fused_track_test)
  add_test(NAME wp03_sitmgmt_threat_test COMMAND wp03_sitmgmt_threat_test)
  add_test(NAME wp03_sitmgmt_boundary_test COMMAND wp03_sitmgmt_boundary_test)
  add_test(NAME wp03_sitmgmt_summary_test COMMAND wp03_sitmgmt_summary_test)
endif()