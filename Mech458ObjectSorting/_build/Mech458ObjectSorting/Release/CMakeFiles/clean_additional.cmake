# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/khephrengould/Documents/Projects/School/Mech 458/MECH458_ObjectSorting/Mech458ObjectSorting/out/Mech458ObjectSorting/Release.eep"
  "/home/khephrengould/Documents/Projects/School/Mech 458/MECH458_ObjectSorting/Mech458ObjectSorting/out/Mech458ObjectSorting/Release.hex"
  "/home/khephrengould/Documents/Projects/School/Mech 458/MECH458_ObjectSorting/Mech458ObjectSorting/out/Mech458ObjectSorting/Release.lss"
  "/home/khephrengould/Documents/Projects/School/Mech 458/MECH458_ObjectSorting/Mech458ObjectSorting/out/Mech458ObjectSorting/Release.srec"
  "/home/khephrengould/Documents/Projects/School/Mech 458/MECH458_ObjectSorting/Mech458ObjectSorting/out/Mech458ObjectSorting/Release.usersignatures"
  )
endif()
