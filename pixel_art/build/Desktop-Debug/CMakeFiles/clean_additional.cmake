# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/pixel_art_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/pixel_art_autogen.dir/ParseCache.txt"
  "pixel_art_autogen"
  )
endif()
