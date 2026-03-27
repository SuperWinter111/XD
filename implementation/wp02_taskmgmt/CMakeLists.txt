cmake_minimum_required(VERSION 3.20)

add_library(wp02_taskmgmt
  src/command_normalizer.cpp
  src/resource_request_coordinator.cpp
  src/task_decomposer.cpp
  src/task_lifecycle_tracker.cpp
  src/task_package_builder.cpp
  src/task_reconstruction_service.cpp
  src/taskmgmt_application_service.cpp
  src/taskmgmt_command_handler.cpp
  src/taskmgmt_command_mapper.cpp
  src/taskmgmt_response_mapper.cpp
)

target_include_directories(wp02_taskmgmt
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp02_taskmgmt PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp02_taskmgmt_main_chain_test tests/main_chain_test.cpp)
  add_executable(wp02_taskmgmt_reconstruction_test tests/reconstruction_test.cpp)
  add_executable(wp02_taskmgmt_command_mapper_test tests/command_mapper_test.cpp)
  add_executable(wp02_taskmgmt_command_handler_test tests/command_handler_test.cpp)
  add_executable(wp02_taskmgmt_lifecycle_test tests/lifecycle_test.cpp)
  add_executable(wp02_taskmgmt_feedback_test tests/feedback_test.cpp)

  target_link_libraries(wp02_taskmgmt_main_chain_test PRIVATE wp02_taskmgmt)
  target_link_libraries(wp02_taskmgmt_reconstruction_test PRIVATE wp02_taskmgmt)
  target_link_libraries(wp02_taskmgmt_command_mapper_test PRIVATE wp02_taskmgmt)
  target_link_libraries(wp02_taskmgmt_command_handler_test PRIVATE wp02_taskmgmt)
  target_link_libraries(wp02_taskmgmt_lifecycle_test PRIVATE wp02_taskmgmt)
  target_link_libraries(wp02_taskmgmt_feedback_test PRIVATE wp02_taskmgmt)

  target_include_directories(wp02_taskmgmt_main_chain_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp02_taskmgmt_reconstruction_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp02_taskmgmt_command_mapper_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp02_taskmgmt_command_handler_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp02_taskmgmt_lifecycle_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp02_taskmgmt_feedback_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  add_test(NAME wp02_taskmgmt_main_chain_test COMMAND wp02_taskmgmt_main_chain_test)
  add_test(NAME wp02_taskmgmt_reconstruction_test COMMAND wp02_taskmgmt_reconstruction_test)
  add_test(NAME wp02_taskmgmt_command_mapper_test COMMAND wp02_taskmgmt_command_mapper_test)
  add_test(NAME wp02_taskmgmt_command_handler_test COMMAND wp02_taskmgmt_command_handler_test)
  add_test(NAME wp02_taskmgmt_lifecycle_test COMMAND wp02_taskmgmt_lifecycle_test)
  add_test(NAME wp02_taskmgmt_feedback_test COMMAND wp02_taskmgmt_feedback_test)
endif()