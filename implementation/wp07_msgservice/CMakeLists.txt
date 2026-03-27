cmake_minimum_required(VERSION 3.20)

find_package(SQLite3 QUIET)

set(_bms_sqlite_runtime_release)
set(_bms_sqlite_runtime_debug)

if(NOT SQLite3_FOUND AND NOT TARGET SQLite::SQLite3)
  set(_bms_sqlite_vcpkg_roots)

  if(DEFINED ENV{VCPKG_ROOT} AND NOT "$ENV{VCPKG_ROOT}" STREQUAL "")
    list(APPEND _bms_sqlite_vcpkg_roots "$ENV{VCPKG_ROOT}/installed/x64-windows")
  endif()

  list(APPEND _bms_sqlite_vcpkg_roots "C:/vcpkg/installed/x64-windows")
  list(REMOVE_DUPLICATES _bms_sqlite_vcpkg_roots)

  foreach(_bms_sqlite_root IN LISTS _bms_sqlite_vcpkg_roots)
    if(EXISTS "${_bms_sqlite_root}/include/sqlite3.h" AND EXISTS "${_bms_sqlite_root}/lib/sqlite3.lib")
      set(_bms_sqlite_runtime_release "${_bms_sqlite_root}/bin/sqlite3.dll")
      set(_bms_sqlite_runtime_debug "${_bms_sqlite_root}/debug/bin/sqlite3.dll")

      add_library(SQLite::SQLite3 UNKNOWN IMPORTED)
      set_target_properties(SQLite::SQLite3 PROPERTIES
        IMPORTED_CONFIGURATIONS "Debug;Release;RelWithDebInfo;MinSizeRel"
        IMPORTED_LOCATION "${_bms_sqlite_root}/lib/sqlite3.lib"
        IMPORTED_LOCATION_DEBUG "${_bms_sqlite_root}/debug/lib/sqlite3.lib"
        IMPORTED_LOCATION_RELEASE "${_bms_sqlite_root}/lib/sqlite3.lib"
        IMPORTED_LOCATION_RELWITHDEBINFO "${_bms_sqlite_root}/lib/sqlite3.lib"
        IMPORTED_LOCATION_MINSIZEREL "${_bms_sqlite_root}/lib/sqlite3.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${_bms_sqlite_root}/include"
      )
      set(SQLite3_FOUND TRUE)
      break()
    endif()
  endforeach()
endif()

function(bms_msgservice_attach_sqlite_runtime target_name)
  if(NOT TARGET "${target_name}")
    message(FATAL_ERROR "bms_msgservice_attach_sqlite_runtime target does not exist: ${target_name}")
  endif()

  if(NOT SQLite3_FOUND)
    return()
  endif()

  set(_bms_sqlite_runtime_copy_source)

  if(EXISTS "${_bms_sqlite_runtime_release}" AND EXISTS "${_bms_sqlite_runtime_debug}")
    set(_bms_sqlite_runtime_copy_source
      "$<$<CONFIG:Debug>:${_bms_sqlite_runtime_debug}>$<$<NOT:$<CONFIG:Debug>>:${_bms_sqlite_runtime_release}>"
    )
  elseif(EXISTS "${_bms_sqlite_runtime_debug}")
    set(_bms_sqlite_runtime_copy_source "${_bms_sqlite_runtime_debug}")
  elseif(EXISTS "${_bms_sqlite_runtime_release}")
    set(_bms_sqlite_runtime_copy_source "${_bms_sqlite_runtime_release}")
  endif()

  if(NOT _bms_sqlite_runtime_copy_source)
    return()
  endif()

  add_custom_command(TARGET ${target_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${_bms_sqlite_runtime_copy_source}"
      "$<TARGET_FILE_DIR:${target_name}>"
  )
endfunction()

function(bms_msgservice_install_sqlite_runtime destination)
  if(NOT SQLite3_FOUND)
    return()
  endif()

  if(EXISTS "${_bms_sqlite_runtime_release}")
    install(FILES "${_bms_sqlite_runtime_release}"
      DESTINATION "${destination}"
      CONFIGURATIONS Release RelWithDebInfo MinSizeRel
    )
  endif()

  if(EXISTS "${_bms_sqlite_runtime_debug}")
    install(FILES "${_bms_sqlite_runtime_debug}"
      DESTINATION "${destination}"
      CONFIGURATIONS Debug
    )
  endif()
endfunction()

add_library(wp07_msgservice
  src/file_persistence_format.cpp
  src/topic_registry.cpp
  src/subscription_registry.cpp
  src/subscription_governance_service.cpp
  src/subscription_audit_repository.cpp
  src/envelope_router.cpp
  src/delivery_tracker.cpp
  src/msgservice_application_service.cpp
  src/msgservice_command_handler.cpp
  src/msgservice_command_mapper.cpp
  src/msgservice_repository_factory.cpp
  src/msgservice_response_mapper.cpp
  src/retry_and_dead_letter_service.cpp
  src/retry_schedule_repository.cpp
)

target_include_directories(wp07_msgservice
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wp07_msgservice PUBLIC cxx_std_20)
target_compile_definitions(wp07_msgservice PUBLIC BMS_MSGSERVICE_DEFAULT_PERSISTENCE_SQLITE=1)

if(SQLite3_FOUND)
  target_sources(wp07_msgservice
    PRIVATE
      src/sqlite_subscription_audit_repository.cpp
      src/sqlite_retry_schedule_repository.cpp
  )

  target_link_libraries(wp07_msgservice
    PUBLIC
      SQLite::SQLite3
  )

  target_compile_definitions(wp07_msgservice PUBLIC BMS_MSGSERVICE_HAS_SQLITE=1)
endif()

if(BMS_BUILD_TESTS)
  add_executable(wp07_msgservice_topic_registry_test tests/topic_registry_test.cpp)
  add_executable(wp07_msgservice_subscription_governance_test tests/subscription_governance_test.cpp)
  add_executable(wp07_msgservice_delivery_retry_test tests/delivery_retry_test.cpp)
  add_executable(wp07_msgservice_application_service_test tests/application_service_test.cpp)
  add_executable(wp07_msgservice_file_repository_adapter_test tests/file_repository_adapter_test.cpp)
  add_executable(wp07_msgservice_command_mapper_test tests/command_mapper_test.cpp)
  add_executable(wp07_msgservice_command_handler_test tests/command_handler_test.cpp)
  add_executable(wp07_msgservice_repository_factory_test tests/repository_factory_test.cpp)

  target_link_libraries(wp07_msgservice_topic_registry_test PRIVATE wp07_msgservice)
  target_link_libraries(wp07_msgservice_subscription_governance_test PRIVATE wp07_msgservice)
  target_link_libraries(wp07_msgservice_delivery_retry_test PRIVATE wp07_msgservice)
  target_link_libraries(wp07_msgservice_application_service_test PRIVATE wp07_msgservice)
  target_link_libraries(wp07_msgservice_file_repository_adapter_test PRIVATE wp07_msgservice)
  target_link_libraries(wp07_msgservice_command_mapper_test PRIVATE wp07_msgservice)
  target_link_libraries(wp07_msgservice_command_handler_test PRIVATE wp07_msgservice)
  target_link_libraries(wp07_msgservice_repository_factory_test PRIVATE wp07_msgservice)

  target_include_directories(wp07_msgservice_topic_registry_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp07_msgservice_subscription_governance_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp07_msgservice_delivery_retry_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp07_msgservice_application_service_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp07_msgservice_file_repository_adapter_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp07_msgservice_command_mapper_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp07_msgservice_command_handler_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  target_include_directories(wp07_msgservice_repository_factory_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

  if(SQLite3_FOUND)
    add_executable(wp07_msgservice_sqlite_integration_test tests/sqlite_integration_test.cpp)
    target_link_libraries(wp07_msgservice_sqlite_integration_test PRIVATE wp07_msgservice)
    target_include_directories(wp07_msgservice_sqlite_integration_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  endif()

  if(SQLite3_FOUND)
    set(_bms_msgservice_test_targets
      wp07_msgservice_topic_registry_test
      wp07_msgservice_subscription_governance_test
      wp07_msgservice_delivery_retry_test
      wp07_msgservice_application_service_test
      wp07_msgservice_file_repository_adapter_test
      wp07_msgservice_command_mapper_test
      wp07_msgservice_command_handler_test
      wp07_msgservice_repository_factory_test
      wp07_msgservice_sqlite_integration_test
    )

    foreach(_bms_msgservice_test_target IN LISTS _bms_msgservice_test_targets)
      bms_msgservice_attach_sqlite_runtime(${_bms_msgservice_test_target})
    endforeach()
  endif()

  add_test(NAME wp07_msgservice_topic_registry_test COMMAND wp07_msgservice_topic_registry_test)
  add_test(NAME wp07_msgservice_subscription_governance_test COMMAND wp07_msgservice_subscription_governance_test)
  add_test(NAME wp07_msgservice_delivery_retry_test COMMAND wp07_msgservice_delivery_retry_test)
  add_test(NAME wp07_msgservice_application_service_test COMMAND wp07_msgservice_application_service_test)
  add_test(NAME wp07_msgservice_file_repository_adapter_test COMMAND wp07_msgservice_file_repository_adapter_test)
  add_test(NAME wp07_msgservice_command_mapper_test COMMAND wp07_msgservice_command_mapper_test)
  add_test(NAME wp07_msgservice_command_handler_test COMMAND wp07_msgservice_command_handler_test)
  add_test(NAME wp07_msgservice_repository_factory_test COMMAND wp07_msgservice_repository_factory_test)
  if(SQLite3_FOUND)
    add_test(NAME wp07_msgservice_sqlite_integration_test COMMAND wp07_msgservice_sqlite_integration_test)
  endif()
endif()
