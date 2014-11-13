#This need some refinement.
function(copy_dist_dlls target)
    set(DLL_DIRS
        ${SFML_ROOT}/bin
    )
    
    foreach(dir ${DLL_DIRS})
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${dir}"
            $<TARGET_FILE_DIR:${target}>)
    endforeach(dir)
endfunction()