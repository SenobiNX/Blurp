add_library(LibBlurp OBJECT
    ${CMAKE_CURRENT_SOURCE_DIR}/src/module.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/alloc.cpp
)

set(BLURP_MODULE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mod0.cpp
    PARENT_SCOPE
)

target_link_libraries(LibBlurp PRIVATE LibHakkun)
target_include_directories(LibBlurp PRIVATE ${CMAKE_SOURCE_DIR}/sys/hakkun/include)
target_include_directories(LibBlurp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
