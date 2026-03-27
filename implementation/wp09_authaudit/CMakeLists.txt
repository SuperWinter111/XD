cmake_minimum_required(VERSION 3.20)
add_library(wp09_authaudit
  src/access_policy_evaluator.cpp
  src/authaudit_application_service.cpp
  src/operation_audit_recorder.cpp
  src/security_correlation_service.cpp
)
target_include_directories(wp09_authaudit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(wp09_authaudit PUBLIC cxx_std_20)
if(BMS_BUILD_TESTS)
  add_executable(wp09_authaudit_access_test tests/access_test.cpp)
  add_executable(wp09_authaudit_audit_test tests/audit_test.cpp)
  add_executable(wp09_authaudit_security_review_test tests/security_review_test.cpp)
  add_executable(wp09_authaudit_boundary_test tests/boundary_test.cpp)
  target_link_libraries(wp09_authaudit_access_test PRIVATE wp09_authaudit)
  target_link_libraries(wp09_authaudit_audit_test PRIVATE wp09_authaudit)
  target_link_libraries(wp09_authaudit_security_review_test PRIVATE wp09_authaudit)
  target_link_libraries(wp09_authaudit_boundary_test PRIVATE wp09_authaudit)
  target_include_directories(wp09_authaudit_access_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp09_authaudit_audit_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp09_authaudit_security_review_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp09_authaudit_boundary_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  add_test(NAME wp09_authaudit_access_test COMMAND wp09_authaudit_access_test)
  add_test(NAME wp09_authaudit_audit_test COMMAND wp09_authaudit_audit_test)
  add_test(NAME wp09_authaudit_security_review_test COMMAND wp09_authaudit_security_review_test)
  add_test(NAME wp09_authaudit_boundary_test COMMAND wp09_authaudit_boundary_test)
endif()