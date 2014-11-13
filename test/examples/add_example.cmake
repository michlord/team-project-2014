macro (set_assets target)
    set(ASSETS_${target} ${ARGN})
endmacro()

macro (set_sources target)
    set(SRCS_${target} ${ARGN})
endmacro()

function (add_example target)
    add_executable(${target} ${SRCS_${target}})
    add_test(${target} ${target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

    foreach(asset ${ASSETS_${target}})
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/"${asset}"
            ${CMAKE_CURRENT_BINARY_DIR}/"${asset}")
    endforeach(asset)
endfunction()