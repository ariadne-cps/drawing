if(NOT TARGET paving)
    ensure_submodule_initialized(paving)
    add_subdirectory(paving)
endif()

if(NOT TARGET rendering)
    ensure_submodule_initialized(rendering)
    add_subdirectory(rendering)
endif()
