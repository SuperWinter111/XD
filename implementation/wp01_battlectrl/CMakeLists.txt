cmake_minimum_required(VERSION 3.20)

add_library(wp01_battlectrl
  src/battle_plan_generator.cpp
  src/battlectrl_application_service.cpp
  src/constraint_guard.cpp
  src/effect_assessment_service.cpp
  src/plan_adjustment_service.cpp
  src/rule_assist_gateway.cpp
  src/task_intent_adapter.cpp
)

target_include_directories(wp01_battlectrl
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp01_battlectrl PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp01_battlectrl_plan_created_test tests/plan_created_test.cpp)
  add_executable(wp01_battlectrl_plan_updated_test tests/plan_updated_test.cpp)
  add_executable(wp01_battlectrl_effect_report_test tests/effect_report_test.cpp)
  add_executable(wp01_battlectrl_boundary_test tests/boundary_test.cpp)

  target_link_libraries(wp01_battlectrl_plan_created_test PRIVATE wp01_battlectrl)
  target_link_libraries(wp01_battlectrl_plan_updated_test PRIVATE wp01_battlectrl)
  target_link_libraries(wp01_battlectrl_effect_report_test PRIVATE wp01_battlectrl)
  target_link_libraries(wp01_battlectrl_boundary_test PRIVATE wp01_battlectrl)

  target_include_directories(wp01_battlectrl_plan_created_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp01_battlectrl_plan_updated_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp01_battlectrl_effect_report_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp01_battlectrl_boundary_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  add_test(NAME wp01_battlectrl_plan_created_test COMMAND wp01_battlectrl_plan_created_test)
  add_test(NAME wp01_battlectrl_plan_updated_test COMMAND wp01_battlectrl_plan_updated_test)
  add_test(NAME wp01_battlectrl_effect_report_test COMMAND wp01_battlectrl_effect_report_test)
  add_test(NAME wp01_battlectrl_boundary_test COMMAND wp01_battlectrl_boundary_test)
endif()