# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "/home/khephrengould/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(Mech458ObjectSorting_Debug_Debug_avr_gcc_assemble_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "${MP_EXTRA_AS_PRE}"
        "-mmcu=atmega2560"
        "-B${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/gcc/dev/atmega2560"
        "-c"
        "-mrelax"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST}")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega2560__"
        PRIVATE "Debug=Debug")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/include")
endfunction()
function(Mech458ObjectSorting_Debug_Debug_avr_gcc_assembleWithPreprocess_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "${MP_EXTRA_AS_PRE}"
        "-mmcu=atmega2560"
        "-B${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/gcc/dev/atmega2560"
        "-c"
        "-mrelax"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST}")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega2560__"
        PRIVATE "Debug=Debug")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/include")
endfunction()
function(Mech458ObjectSorting_Debug_Debug_avr_gcc_compile_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "${MP_EXTRA_CC_PRE}"
        "-mmcu=atmega2560"
        "-B${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/gcc/dev/atmega2560"
        "-x"
        "c"
        "-c"
        "-mrelax"
        "-funsigned-char"
        "-funsigned-bitfields"
        "-O1"
        "-ffunction-sections"
        "-fdata-sections"
        "-fpack-struct"
        "-fshort-enums"
        "-Wall")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega2560__"
        PRIVATE "Debug=Debug")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/include")
endfunction()
function(Mech458ObjectSorting_Debug_Debug_avr_gcc_compile_cpp_rule target)
    set(options
        "-g"
        "-gdwarf-2"
        "${MP_EXTRA_CC_PRE}"
        "-mmcu=atmega2560"
        "-B${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/gcc/dev/atmega2560"
        "-x"
        "c++"
        "-c"
        "-mrelax"
        "-O0"
        "-ffunction-sections"
        "-fdata-sections")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega2560__"
        PRIVATE "Debug=Debug")
    target_include_directories(${target} PRIVATE "${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/include")
endfunction()
function(Mech458ObjectSorting_Debug_link_rule target)
    set(options
        "-gdwarf-2"
        "${MP_EXTRA_LD_PRE}"
        "-mmcu=atmega2560"
        "-B${PACK_REPO_PATH}/Microchip/ATmega_DFP/3.6.299/gcc/dev/atmega2560"
        "-Wl,-Map=mem.map"
        "-mrelax"
        "-Wl,--defsym=__MPLAB_BUILD=1${MP_EXTRA_LD_POST}"
        "-Wl,--gc-sections")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target}
        PRIVATE "__ATmega2560__"
        PRIVATE "Debug=Debug")
    target_link_libraries(${target} PRIVATE "m")
endfunction()
function(Mech458ObjectSorting_Debug_objcopy_ihex_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=ihex ${Mech458ObjectSorting_Debug_image_name} ${Mech458ObjectSorting_Debug_image_base_name}.hex
        WORKING_DIRECTORY ${Mech458ObjectSorting_Debug_output_dir})
endfunction()
function(Mech458ObjectSorting_Debug_objcopy_eep_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --only-section=.eeprom --change-section-lma .eeprom=0 --no-change-warnings --output-target=ihex ${Mech458ObjectSorting_Debug_image_name} ${Mech458ObjectSorting_Debug_image_base_name}.eep
        WORKING_DIRECTORY ${Mech458ObjectSorting_Debug_output_dir})
endfunction()
function(Mech458ObjectSorting_Debug_objcopy_lss_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS --disassemble --wide --demangle --line-numbers --section-headers --source ${Mech458ObjectSorting_Debug_image_name} > ${Mech458ObjectSorting_Debug_image_base_name}.lss
        WORKING_DIRECTORY ${Mech458ObjectSorting_Debug_output_dir})
endfunction()
function(Mech458ObjectSorting_Debug_objcopy_srec_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --output-target=srec --remove-section=.eeprom --remove-section=.fuse --remove-section=.lock --remove-section=.signature ${Mech458ObjectSorting_Debug_image_name} ${Mech458ObjectSorting_Debug_image_base_name}.srec
        WORKING_DIRECTORY ${Mech458ObjectSorting_Debug_output_dir})
endfunction()
function(Mech458ObjectSorting_Debug_objcopy_sig_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJCOPY}
        ARGS --only-section=.user_signatures --change-section-lma .user_signatures=0 --no-change-warnings --output-target=ihex ${Mech458ObjectSorting_Debug_image_name} ${Mech458ObjectSorting_Debug_image_base_name}.usersignatures
        WORKING_DIRECTORY ${Mech458ObjectSorting_Debug_output_dir})
endfunction()
function(Mech458ObjectSorting_Debug_objcopy_memusage_rule target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${OBJDUMP}
        ARGS -Pmem-usage ${Mech458ObjectSorting_Debug_image_name}
        WORKING_DIRECTORY ${Mech458ObjectSorting_Debug_output_dir})
endfunction()
