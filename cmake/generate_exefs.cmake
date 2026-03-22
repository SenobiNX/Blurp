function(generate_exefs)
    configure_file(${PROJECT_SOURCE_DIR}/config/npdm.json ${CMAKE_CURRENT_BINARY_DIR}/npdm.json)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "-- Generating main.npdm"
        COMMAND python ${CMAKE_SOURCE_DIR}/sys/tools/senobi/build_npdm.py ${CMAKE_CURRENT_BINARY_DIR}/npdm.json ${CMAKE_CURRENT_BINARY_DIR}/main.npdm
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "-- Generating ${PROJECT_NAME}.nso"
        COMMAND ${CMAKE_SOURCE_DIR}/sys/tools/elf2nso.py ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.nso -c
    )
endfunction()
