add_executable(surgen)

target_sources(surgen PRIVATE
    main.c
    game.c
    level.c
    draw.c
)

target_link_libraries(surgen PUBLIC m raylib)