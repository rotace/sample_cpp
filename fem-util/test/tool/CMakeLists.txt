# cmake version
cmake_minimum_required(VERSION 2.6)

set(target_name "tool")
set(test_name "${target_name}Test")
set(clean "clean-${test_name}")


###################
### CLEAN CMakeFiles
add_custom_target(${clean}
	COMMAND rm -rf ${cmake-files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	COMMENT "clean ${target_name}")
add_dependencies(clean-all ${clean})


###################
### UNIT TEST
if(fem_unit_test)
  message(STATUS "${test_name} will be built")
  file(GLOB source "*.cc")
  add_executable(${test_name} ${source})
  target_link_libraries(${test_name}
    ${target_name}
    gtest
    gtest_main
    )
  if(NOT fem_disable_pthreads)
    message(STATUS "-- with pthread")
    target_link_libraries(${test_name} pthread)
  endif(NOT fem_disable_pthreads)

  # excute
  add_test(
    NAME ${test_name}
    COMMAND $<TARGET_FILE:${test_name}>
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )
  # add_custom_command(
  #   TARGET ${test_name}
  #   POST_BUILD
  #   COMMAND ${test_name}
  #   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  #   )
endif()
