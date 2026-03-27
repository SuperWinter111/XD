cmake_minimum_required(VERSION 3.20)

add_library(wp10_monitorlog
  src/alert_aggregation_service.cpp
  src/log_index_service.cpp
  src/metric_ingest_service.cpp
  src/monitorlog_application_service.cpp
  src/trace_correlation_service.cpp
)

target_include_directories(wp10_monitorlog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(wp10_monitorlog PUBLIC cxx_std_20)

if(BMS_BUILD_TESTS)
  add_executable(wp10_monitorlog_metric_test tests/metric_test.cpp)
  add_executable(wp10_monitorlog_alert_test tests/alert_test.cpp)
  add_executable(wp10_monitorlog_log_digest_test tests/log_digest_test.cpp)
  add_executable(wp10_monitorlog_trace_test tests/trace_test.cpp)
  target_link_libraries(wp10_monitorlog_metric_test PRIVATE wp10_monitorlog)
  target_link_libraries(wp10_monitorlog_alert_test PRIVATE wp10_monitorlog)
  target_link_libraries(wp10_monitorlog_log_digest_test PRIVATE wp10_monitorlog)
  target_link_libraries(wp10_monitorlog_trace_test PRIVATE wp10_monitorlog)
  target_include_directories(wp10_monitorlog_metric_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp10_monitorlog_alert_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp10_monitorlog_log_digest_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp10_monitorlog_trace_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  add_test(NAME wp10_monitorlog_metric_test COMMAND wp10_monitorlog_metric_test)
  add_test(NAME wp10_monitorlog_alert_test COMMAND wp10_monitorlog_alert_test)
  add_test(NAME wp10_monitorlog_log_digest_test COMMAND wp10_monitorlog_log_digest_test)
  add_test(NAME wp10_monitorlog_trace_test COMMAND wp10_monitorlog_trace_test)
endif()