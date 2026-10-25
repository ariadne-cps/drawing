if(NOT TARGET kernel)
    ensure_submodule_initialized(kernel)
    add_subdirectory(kernel)
endif()

if(NOT TARGET rendering)
    ensure_submodule_initialized(rendering)
    add_subdirectory(rendering)
endif()
