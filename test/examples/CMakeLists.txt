include(add_example.cmake)

copy_dist_dlls()

# If you want to use sources from the main project tree, you
# must either specify an appropriate path here or the
# project modules should be built as libraries with add_library().
# Once there are libraries you can do target_link_libraries.
# Includes from /include dir can be referenced in cpp source with
# #include <lib> because our cmake script has custom
# include_directories preset.

set_sources(example
    "example/main.cpp"
    "example/util.cpp"
    "example/util.h"
)

set_assets(example
    "assets/sansation.ttf"
)


add_example(example)

target_link_libraries(example ${SFML_LIBRARIES})