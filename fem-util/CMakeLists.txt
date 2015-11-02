### PROJECT_SOURCE_ROOT CMakeList.txt ###

#===== PROJECT INFO =====
project(fem-util)		    # project name
set(serial "2.x")		    # version
set(soserial "1")		    # shared library version
cmake_minimum_required(VERSION 2.6) # cmake version required
enable_testing()		    # enable testing


message(STATUS "################## CMakeLists ######################")


#===== REQUIRED PACKAGES =====
find_package(Boost 1.41)
message(STATUS "Looking for Boost found - ${Boost_FOUND}")
if(NOT Boost_FOUND)
  message(ERROR "--> Boost is not found!")
  return()
endif()

#=====  SET CONFIG =====
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "build type is not specified, set to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()
# set(CMAKE_VERBOSE_MAKEFILE TRUE)
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(is_debug TRUE)
endif()

#===== MAKE OPTIONS =====
include(CMakeDependentOption)
cmake_dependent_option(fem_disable_pthreads "POSIX Thread" ON "is_debug" OFF)
cmake_dependent_option(fem_unit_test  "Compile Unit Test" ON "is_debug" OFF)
set(gtest_disable_pthreads ${fem_disable_pthreads})

#===== DIRECTORY INFO =====
# Output Root Directory
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
# Install Root Directory
set(CMAKE_INSTALL_PREFIX /home/usr/HF_WBM/shibata/tool)


#===== FLAGS INFO =====
# set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")


#===== INCLUDE and LIBRARY =====
# gcc -I(include_dir)
include_directories(${PROJECT_SOURCE_DIR}/src/data)
include_directories(${PROJECT_SOURCE_DIR}/src/iodata)
include_directories(${PROJECT_SOURCE_DIR}/src/tool)
include_directories(${PROJECT_SOURCE_DIR}/src/func)
include_directories(${PROJECT_SOURCE_DIR}/gtest-1.7.0/include)
# # gcc -L(lib_dir)
# link_directories(${PROJECT_BINARY_DIR}/lib)



#===== TARGETS and OPTIONS =====
# file(GLOB src iodata.cpp calcdata.cpp)
# add_library(staticlib  STATIC ${src})
# add_library(sharedlib  SHARED ${src})
# add_executable(testexe ${src})
# target_link_libraries(testexe
#   staticlib		# 内部静的ライブラリ
#   sharedlib		# 内部動的ライブラリ
#　 m			# 外部ライブラリ
#   ※ 外部ライブラリの指定には，接頭辞と拡張子は省略表記・全表記どれでもよい．
#   openblas/openblas.so/libopenblas.so
#   ※ 外部ライブラリの拡張子を書いておくと，cmakeが静的／動的を区別して処理する
#   openblas/openblas.soのとき  => -lopenblas
#   openblas.a のとき           => -Wl,-Bstatic -lopenblas -Wl,-Bdynamic
#  )

# set_target_properties(testlibso PROPERTIES
#   COMPILE_FLAGS ""
#   OUTPUT_NAME testlibso
#   VERSION ${serial}
#   SOVERSION ${soserial})


#===== POST BUILD =====
# # run_test command (after build)
# add_custom_command(
#     TARGET fea2vtk
#     POST_BUILD
#     # COMMAND echo "finish to build"
#     COMMAND ./bin/fea2vtk
#     WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})


#===== CUSTOM TARGETS =====
# tag
add_custom_target(tag
  COMMAND gtags
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
# clean
set(cmake-files "CMakeFiles CMakeCache.txt *.cmake install_manifest.txt")
add_custom_target(clean-all
  COMMAND rm -rf ${cmake-files}
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  COMMENT "clean all")
# uninstall
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


#===== INSTALL DESTINATION in Install Root Directory =====
# INSTALL(TARGETS fea2vtk DESTINATION bin)
# file(GLOB include iodata.hpp calcdata.hpp)
# INSTALL(FILES ${include} DESTINATION include)
INSTALL(FILES ${PROJECT_SOURCE_DIR}/src/shellscript/run.sh DESTINATION bin
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE  GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

#===== SUBDIRECTORY INFO =====
add_subdirectory(gtest-1.7.0)
add_subdirectory(src/data)
add_subdirectory(src/tool)
add_subdirectory(src/iodata)
add_subdirectory(src/func)
add_subdirectory(src/app/translate)
add_subdirectory(src/app/nodfor)
add_subdirectory(src/app/bdf2vtk)
add_subdirectory(src/app/fea2vtk)

add_subdirectory(test/tool)
add_subdirectory(test/data)
add_subdirectory(test/iodata)
add_subdirectory(test/func)

add_subdirectory(test/app_test/fea2vtk)
add_subdirectory(test/app_test/translate)

#===== MESSAGE INFO =====
message("
-------------------------------------------------------
fem-util Version ${serial}
         SoVersion ${soserial}

Current compiler options:
 c language
    CC:                        	    ${CMAKE_C_COMPILER}
 c++ language
    CXX:			    ${CMAKE_CXX_COMPILER}
    CMAKE_CXX_FLAGS:		    ${CMAKE_CXX_FLAGS} 
    CMAKE_CXX_FLAGS_DEBUG:	    ${CMAKE_CXX_FLAGS_DEBUG} 
    CMAKE_CXX_FLAGS_RELEASE:	    ${CMAKE_CXX_FLAGS_RELEASE}
    CMAKE_CXX_ARCHIVE_CREATE:        ${CMAKE_CXX_ARCHIVE_CREATE}
    CMAKE_CXX_ARCHIVE_APPEND:        ${CMAKE_CXX_ARCHIVE_APPEND}
    CMAKE_CXX_ARCHIVE_FINISH:        ${CMAKE_CXX_ARCHIVE_FINISH}
 linker
    CMAKE_EXE_LINKER_FLAGS:         ${CMAKE_EXE_LINKER_FLAGS}
    CMAKE_STATIC_LINKER_FLAGS:      ${CMAKE_STATIC_LINKER_FLAGS}
    CMAKE_SHARED_LINKER_FLAGS:      ${CMAKE_SHARED_LINKER_FLAGS}
 archiver
    CMAKE_AR:                       ${CMAKE_AR}
 ranlib
    CMAKE_RANLIB:                   ${CMAKE_RANLIB}
 others
    GTEST_CMAKE_OPTION:		    ${GTEST_OPT}

Features configure:
    CMAKE_VERSION:		    ${CMAKE_VERSION}
    CMAKE_BUILD_TYPE:		    ${CMAKE_BUILD_TYPE}
    Using Boost version:	    ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}
    disable POSIX Thread:	    ${fem_disable_pthreads}
    build unit test:		    ${fem_unit_test}

GoogleTest configure:
    disable POSIX Thread:	    ${gtest_disable_pthreads}
    build test: 		    ${gtest_build_tests}
    bould samples:		    ${gtest_build_samples}

Build path configure:
    PROJECT_SOURCE_DIR:		    ${PROJECT_SOURCE_DIR}
    PROJECT_BINARY_DIR:		    ${PROJECT_BINARY_DIR}

-------------------------------------------------------
")
