# cmake version
cmake_minimum_required(VERSION 2.6)

set(target_name "iodata")
set(clean "clean-${target_name}")

#################
### LIBRARY TAGET
file(GLOB source "*.cpp")
add_library(${target_name} STATIC ${source})
set_target_properties(${target_name} PROPERTIES
  VERSION ${serial}
  SOVERSION ${soserial})
# SET COMPILE OPTION (-l{library} ...)
target_link_libraries(${target_name}
  data
  tool
  )

###################
### INSTALL SETTING
file(GLOB include *.hpp)
# INSTALL DIRECTORY
install(TARGETS ${target_name} ARCHIVE DESTINATION lib)
# INSTALL(TARGETS ${target_name} LIBRARY DESTINATION lib)
install(FILES ${include} DESTINATION include)


###################
### CLEAN CMakeFiles
add_custom_target(${clean}
	COMMAND rm -rf ${cmake-files}
	WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
	COMMENT "clean ${target_name}")
add_dependencies(clean-all ${clean})