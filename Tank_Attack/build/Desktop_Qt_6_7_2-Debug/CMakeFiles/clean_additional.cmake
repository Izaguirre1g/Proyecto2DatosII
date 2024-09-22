# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Tank_Attack_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Tank_Attack_autogen.dir/ParseCache.txt"
  "Tank_Attack_autogen"
  )
endif()
