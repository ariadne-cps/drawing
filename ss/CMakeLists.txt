if(NOT TARGET set)
    ariadne_add_submodule(set)
endif()

if(NOT TARGET rendering)
    ariadne_add_submodule(rendering)
endif()

if(NOT TARGET threading)
    ariadne_add_submodule(threading)
endif()

