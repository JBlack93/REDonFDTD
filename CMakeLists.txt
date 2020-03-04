cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("REDonFDTD" VERSION 0.0.1 LANGUAGES CXX)

# Set a default build type if none was specified
set(default_build_type "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

## Global flags for the compiler (all warnings)
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /EHsc")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

## target directories for install
set(INSTALL_INCLUDE_DIR_BASE include)
set(INSTALL_INCLUDE_DIR ${INSTALL_INCLUDE_DIR_BASE}/REDonFDTD)
set(INSTALL_BIN_DIR bin)
set(INSTALL_LIB_DIR lib)
set(INSTALL_CONFIG_DIR lib/cmake/REDonFDTD)

#shortcut for specific includes
set(REDonFDTD_INCLUDE_DIR
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  )

file(GLOB src_files src/*.cpp)
file(GLOB header_files include/REDonFDTD/*.hpp)

set(tst_dir "${CMAKE_CURRENT_SOURCE_DIR}/t")
add_test(
  NAME BasicRegression
  COMMAND ${tst_dir}/regression.sh ${tst_dir} dimExpected.txt ExXZExpected.txt
)

## create main library
add_subdirectory(src)

file(GLOB exec_files src/bin/*.cpp)

foreach(exec ${exec_files})
  get_filename_component(name ${exec} NAME_WE)
  add_executable(${name}_exe ${exec})
  set_target_properties(${name}_exe PROPERTIES OUTPUT_NAME "${name}")

  ## link library
  target_include_directories(${name}_exe PUBLIC ${REDonFDTD_INCLUDE_DIR})
  target_link_libraries(${name}_exe REDonFDTD)
endforeach(exec)

target_link_libraries(REDonFDTDGUI_exe  Qt5::Widgets)

## install headers
file(GLOB REDonFDTD_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/include/REDonFDTD/*.hpp
  ${PROJECT_BINARY_DIR}/include/REDonFDTD/*.hpp
)

add_custom_command(TARGET REDonFDTD_exe POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/include $<TARGET_FILE_DIR:REDonFDTD_exe>/include)

install(FILES ${REDonFDTD_headers} DESTINATION ${INSTALL_INCLUDE_DIR})
install(TARGETS REDonFDTD DESTINATION ${INSTALL_LIB_DIR})
install(TARGETS REDonFDTD_exe DESTINATION ${INSTALL_BIN_DIR})

## tests (prevent testing if current project is a subproject)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  enable_testing()
  include(CTest)
  set(include_tests TRUE)
endif()
