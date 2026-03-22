include(${PROJECT_SOURCE_DIR}/config/config.cmake)
include(${CMAKE_SOURCE_DIR}/sys/cmake/apply_config.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/generate_exefs.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/module_config.cmake)

if (MODULE_BINARY STREQUAL "rtld")
    message(FATAL_ERROR "Hakkun cannot be used in place of rtld")
endif()

set(CMAKE_EXECUTABLE_SUFFIX ".nss")
set(ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR})

target_link_options(${PROJECT_NAME} PRIVATE -T${MISC_LINKER_SCRIPT})

apply_config(${PROJECT_NAME})

if (HAKKUN_STANDALONE)
    if (IS_32_BIT)
        set(REGISTER_WIDTH 32)
    else()
        set(REGISTER_WIDTH 64)
    endif()
endif()
apply_module_config(${PROJECT_NAME} TRUE)
target_sources(${PROJECT_NAME} PRIVATE ${BLURP_MODULE_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE LibHakkunForModule)
target_link_libraries(boot2 PRIVATE LibBlurp)

generate_exefs()
