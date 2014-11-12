#This need some refinement.
function(copy_dist_dlls)
    set(DLL_DIRS
        ${SFML_ROOT}/bin
    )
    foreach(dir ${DLL_DIRS})
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${dir} ${CMAKE_CURRENT_BINARY_DIR})
    endforeach(dir)
endfunction()