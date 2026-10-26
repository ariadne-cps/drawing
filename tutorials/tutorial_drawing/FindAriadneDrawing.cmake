find_library(ARIADNE_DRAWING_LIBRARY NAMES ariadne-drawing)
find_path(ARIADNE_DRAWING_INCLUDE_DIR ariadne-drawing.hpp
          PATH_SUFFIXES ariadne-drawing)

find_package(Threads REQUIRED)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AriadneDrawing DEFAULT_MSG
    ARIADNE_DRAWING_LIBRARY
    ARIADNE_DRAWING_INCLUDE_DIR
)

if(AriadneDrawing_FOUND)
    get_filename_component(ARIADNE_DRAWING_INCLUDE_PARENT_DIR
        "${ARIADNE_DRAWING_INCLUDE_DIR}" DIRECTORY)
    if(NOT TARGET AriadneDrawing::ariadne-drawing)
        add_library(AriadneDrawing::ariadne-drawing UNKNOWN IMPORTED)
        set_target_properties(AriadneDrawing::ariadne-drawing PROPERTIES
            IMPORTED_LOCATION "${ARIADNE_DRAWING_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES
                "${ARIADNE_DRAWING_INCLUDE_PARENT_DIR};${ARIADNE_DRAWING_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES "Threads::Threads"
        )
    endif()
endif()
