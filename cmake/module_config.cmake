include(${PROJECT_SOURCE_DIR}/config/config.cmake)
include(${CMAKE_SOURCE_DIR}/sys/cmake/apply_config.cmake)
include(${CMAKE_SOURCE_DIR}/sys/cmake/watch.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/generate_exefs.cmake)

if (IS_32_BIT)
    set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/sys/data/link.armv7a.ld")
else()
    set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/sys/data/link.aarch64.ld")
endif()
set(MISC_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/sys/data/misc.ld")

watch(${PROJECT_NAME} "${LINKER_SCRIPT};${MISC_LINKER_SCRIPT}")

function(apply_module_config module useLinkerScript)
    if (useLinkerScript)
        target_link_options(${module} PRIVATE -T${LINKER_SCRIPT} -Wl,--Bdynamic)
    endif()
    if (${ARGC} EQUAL 3)
        target_link_options(${module} PRIVATE -Wl,-init=${ARGV2})
    endif()
    target_link_options(${module} PRIVATE -Wl,--pie)

    apply_config(${module})

    target_link_libraries(${module} PRIVATE LibHakkun LibBlurp)
    target_include_directories(${module} PRIVATE ${CMAKE_SOURCE_DIR}/sys/hakkun/include ${CMAKE_SOURCE_DIR}/lib/blurp/include)
endfunction()
