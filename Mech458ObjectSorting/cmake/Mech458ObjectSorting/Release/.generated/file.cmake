# The following variables contains the files used by the different stages of the build process.
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_assemble)
set_source_files_properties(${Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../adc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../breadboard_io.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../dcmotor.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../lcd.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../mtimer.c")
set_source_files_properties(${Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_compile_cpp)
set_source_files_properties(${Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_link)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_objcopy_ihex)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_objcopy_eep)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_objcopy_lss)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_objcopy_srec)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_objcopy_sig)
set(Mech458ObjectSorting_Release_Release_avr_gcc_FILE_TYPE_objcopy_memusage)
set(Mech458ObjectSorting_Release_image_name "Release.elf")
set(Mech458ObjectSorting_Release_image_base_name "Release")

# The output directory of the final image.
set(Mech458ObjectSorting_Release_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/Mech458ObjectSorting")

# The full path to the final image.
set(Mech458ObjectSorting_Release_full_path_to_image ${Mech458ObjectSorting_Release_output_dir}/${Mech458ObjectSorting_Release_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .lss
    .eep
    .srec
    .usersignatures)
list(TRANSFORM output_extensions PREPEND "${Mech458ObjectSorting_Release_output_dir}/${Mech458ObjectSorting_Release_image_base_name}")
