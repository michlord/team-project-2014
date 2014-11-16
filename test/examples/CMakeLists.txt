include(add_example.cmake)

# If you want to use sources from the main project tree, you
# must either specify an appropriate path here or the
# project modules should be built as libraries with add_library().
# Once there are libraries you can do target_link_libraries.
# Includes from /include dir can be referenced in cpp source with
# #include <lib> because our cmake script has custom
# include_directories preset.

set_sources(input
    "input/main.cpp"
    
    "../../src/EngineSystem/Input/Input.cpp"
    "../../src/EngineSystem/Input/BinaryInput.cpp"
    "../../src/EngineSystem/Input/AxisInput.cpp"
    
    "../../src/EngineSystem/Input/InputHandler.cpp"
    "../../src/EngineSystem/Input/Context.cpp"
)

set_assets(input
    "assets/sansation.ttf"
)

add_example(input)

target_link_libraries(input ${SFML_LIBRARIES})

copy_dist_dlls(input)