include(add_example.cmake)

# If you want to use sources from the main project tree, you
# must either specify an appropriate path here or the
# project modules should be built as libraries with add_library().
# Once there are libraries you can do target_link_libraries.
# Includes from /include dir can be referenced in cpp source with
# #include <lib> because our cmake script has custom
# include_directories preset.

##############
# INPUT TEST #
##############

set_sources(input
    "input/main.cpp"
)

set_assets(input
    "assets/sansation.ttf"
)

add_example(input)

target_link_libraries(input gamelib)

copy_dist_dlls(input)

###############
# SPRITE TEST #
###############

set_sources(sprite
    "sprite/main.cpp"
)

set_assets(sprite
    "assets/sprite.png"
)

add_example(sprite)

target_link_libraries(sprite gamelib)

copy_dist_dlls(sprite)

###############
# ENTITY TEST #
###############

set_sources(entity
    "entity/main.cpp"
    "entity/animation.cpp"
    "entity/PlayerEntity.cpp"
    "entity/PlayerStates.cpp"
)

set_assets(entity
    "assets/elisa-spritesheet1.png"
)

add_example(entity)

target_link_libraries(entity gamelib)

copy_dist_dlls(entity)


#######################
# ASSETS MANAGER TEST #
#######################

set_sources(assetsManager
    "assetsManager/main.cpp"
)

set_assets(assetsManager
    "assets/sprite.png"
    "assets/placeholder.png"
    "assets/sansation.ttf"
)

add_example(assetsManager)

target_link_libraries(assetsManager gamelib)

copy_dist_dlls(assetsManager)


######################
# PLAYER ENTITY TEST #
######################

set_sources(playerEntity
    "playerEntity/main.cpp"
    "playerEntity/GameplayScene.cpp"
    "playerEntity/PlayerEntity.cpp"
    "playerEntity/CreatePlayerAnimation.cpp"
    
    "playerEntity/states/AirSlash.cpp"
    "playerEntity/states/Cast.cpp"
    "playerEntity/states/Fall.cpp"
    # "playerEntity/states/Hurt.cpp"
    "playerEntity/states/Idle.cpp"
    "playerEntity/states/InAir.cpp"
    "playerEntity/states/Jump.cpp"
    "playerEntity/states/OnGround.cpp"
    # "playerEntity/states/PlayerGlobal.cpp"
    "playerEntity/states/Run.cpp"
    "playerEntity/states/Slash.cpp"
)

set_assets(playerEntity
    "assets/dummy_player_spritesheet.png"
)

add_example(playerEntity)

target_link_libraries(playerEntity gamelib)

copy_dist_dlls(assetsManager)

#######################
# PARALAX CLOUDS TEST #
#######################

set_sources(paralaxClouds
    "paralaxClouds/main.cpp"
    "paralaxClouds/Scene.cpp"
)

set_assets(paralaxClouds
    "assets/clouds/cumulus-big1.png"
    "assets/clouds/cumulus-big2.png"
    "assets/clouds/cumulus-big3.png"
    "assets/clouds/cumulus-huge.png"
    "assets/clouds/cumulus-small1.png"
    "assets/clouds/cumulus-small2.png"
    "assets/clouds/cumulus-small3.png"
)

add_example(paralaxClouds)

target_link_libraries(paralaxClouds gamelib)

copy_dist_dlls(paralaxClouds)



