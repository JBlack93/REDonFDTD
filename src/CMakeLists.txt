file(GLOB srcs *.cpp)

## REDonFDTD source
add_library(REDonFDTD SHARED ${srcs})
set_target_properties(REDonFDTD PROPERTIES OUTPUT_NAME "REDonFDTD")
target_include_directories(REDonFDTD PUBLIC ${REDonFDTD_INCLUDE_DIR})
set(libraries ${CMAKE_DL_LIBS})
target_link_libraries(REDonFDTD PRIVATE ${libraries})

## install & export target
install(TARGETS REDonFDTD
  EXPORT REDonFDTD-export
  DESTINATION ${INSTALL_LIB_DIR}
)
install(EXPORT REDonFDTD-export
  FILE
    REDonFDTDConfig.cmake
  NAMESPACE
    REDonFDTD::
  DESTINATION
    ${INSTALL_CONFIG_DIR}
)
