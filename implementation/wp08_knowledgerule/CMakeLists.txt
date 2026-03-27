cmake_minimum_required(VERSION 3.20)

add_library(wp08_knowledgerule
  src/knowledgerule_application_service.cpp
  src/query_gateway.cpp
  src/reason_trace_service.cpp
  src/recommendation_assembler.cpp
  src/request_context_builder.cpp
  src/rule_execution_engine.cpp
)

target_include_directories(wp08_knowledgerule
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp08_knowledgerule PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp08_knowledgerule_recommendation_test tests/recommendation_test.cpp)
  add_executable(wp08_knowledgerule_reason_trace_test tests/reason_trace_test.cpp)
  add_executable(wp08_knowledgerule_conflict_test tests/conflict_test.cpp)
  add_executable(wp08_knowledgerule_boundary_test tests/boundary_test.cpp)

  target_link_libraries(wp08_knowledgerule_recommendation_test PRIVATE wp08_knowledgerule)
  target_link_libraries(wp08_knowledgerule_reason_trace_test PRIVATE wp08_knowledgerule)
  target_link_libraries(wp08_knowledgerule_conflict_test PRIVATE wp08_knowledgerule)
  target_link_libraries(wp08_knowledgerule_boundary_test PRIVATE wp08_knowledgerule)

  target_include_directories(wp08_knowledgerule_recommendation_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp08_knowledgerule_reason_trace_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp08_knowledgerule_conflict_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp08_knowledgerule_boundary_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  add_test(NAME wp08_knowledgerule_recommendation_test COMMAND wp08_knowledgerule_recommendation_test)
  add_test(NAME wp08_knowledgerule_reason_trace_test COMMAND wp08_knowledgerule_reason_trace_test)
  add_test(NAME wp08_knowledgerule_conflict_test COMMAND wp08_knowledgerule_conflict_test)
  add_test(NAME wp08_knowledgerule_boundary_test COMMAND wp08_knowledgerule_boundary_test)
endif()