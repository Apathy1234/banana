#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mynteye_depth" for configuration "Release"
set_property(TARGET mynteye_depth APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mynteye_depth PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/tg/3rd_party/MYNT-EYE-D-SDK/_install/lib/libmynteye_depth.so.1.5.0"
  IMPORTED_SONAME_RELEASE "libmynteye_depth.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS mynteye_depth )
list(APPEND _IMPORT_CHECK_FILES_FOR_mynteye_depth "/home/tg/3rd_party/MYNT-EYE-D-SDK/_install/lib/libmynteye_depth.so.1.5.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
