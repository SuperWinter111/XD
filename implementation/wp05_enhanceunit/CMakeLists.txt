cmake_minimum_required(VERSION 3.20)

add_library(wp05_enhanceunit
  src/capability_reporter.cpp
  src/command_translator.cpp
  src/enhanceunit_application_service.cpp
  src/execution_feedback_bridge.cpp
  src/perception_bridge.cpp
  src/platform_command_service.cpp
  src/simulation_bridge.cpp
)

target_include_directories(wp05_enhanceunit
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp05_enhanceunit PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp05_enhanceunit_command_chain_test tests/command_chain_test.cpp)
  add_executable(wp05_enhanceunit_feedback_test tests/feedback_test.cpp)
  add_executable(wp05_enhanceunit_registration_test tests/registration_test.cpp)
  add_executable(wp05_enhanceunit_simulation_test tests/simulation_test.cpp)

  target_link_libraries(wp05_enhanceunit_command_chain_test PRIVATE wp05_enhanceunit)
  target_link_libraries(wp05_enhanceunit_feedback_test PRIVATE wp05_enhanceunit)
  target_link_libraries(wp05_enhanceunit_registration_test PRIVATE wp05_enhanceunit)
  target_link_libraries(wp05_enhanceunit_simulation_test PRIVATE wp05_enhanceunit)

  target_include_directories(wp05_enhanceunit_command_chain_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp05_enhanceunit_feedback_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp05_enhanceunit_registration_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp05_enhanceunit_simulation_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  add_test(NAME wp05_enhanceunit_command_chain_test COMMAND wp05_enhanceunit_command_chain_test)
  add_test(NAME wp05_enhanceunit_feedback_test COMMAND wp05_enhanceunit_feedback_test)
  add_test(NAME wp05_enhanceunit_registration_test COMMAND wp05_enhanceunit_registration_test)
  add_test(NAME wp05_enhanceunit_simulation_test COMMAND wp05_enhanceunit_simulation_test)
endif()