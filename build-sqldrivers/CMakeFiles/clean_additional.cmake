# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "oci\\CMakeFiles\\QOCIDriverPlugin_autogen.dir\\AutogenUsed.txt"
  "oci\\CMakeFiles\\QOCIDriverPlugin_autogen.dir\\ParseCache.txt"
  "oci\\QOCIDriverPlugin_autogen"
  "odbc\\CMakeFiles\\QODBCDriverPlugin_autogen.dir\\AutogenUsed.txt"
  "odbc\\CMakeFiles\\QODBCDriverPlugin_autogen.dir\\ParseCache.txt"
  "odbc\\QODBCDriverPlugin_autogen"
  "sqlite\\CMakeFiles\\QSQLiteDriverPlugin_autogen.dir\\AutogenUsed.txt"
  "sqlite\\CMakeFiles\\QSQLiteDriverPlugin_autogen.dir\\ParseCache.txt"
  "sqlite\\QSQLiteDriverPlugin_autogen"
  )
endif()
