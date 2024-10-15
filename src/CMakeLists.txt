add_executable(surgen 
    main.c
)

target_link_libraries(surgen PUBLIC m)

target_include_directories(surgen PUBLIC ${CMAKE_SOURCE_DIR}/include)