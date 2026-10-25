/***************************************************************************
 *            drawing_submodule.cpp
 *
 *  Copyright  2008-26  Luca Geretti, Pieter Collins
 ****************************************************************************/

#include "pybind11.hpp"
#include "kernel-utilities.hpp"

#include "drawing/drawing_command_line_interface.hpp"
#include "drawing/drawer.hpp"
#include "drawing/drawer_manager.hpp"
#include "drawing/box_draw.hpp"

#include "rendering/figure.hpp"
#include "geometry/box.hpp"

using namespace Ariadne;

namespace {

Void export_cli(pybind11::module& module)
{
    pybind11::class_<CommandLineInterface> base_class(module,"CommandLineInterface");
    base_class.def("acquire", pybind11::overload_cast<List<String> const&>(&CommandLineInterface::acquire,pybind11::const_));

    pybind11::class_<DrawingCommandLineInterface,CommandLineInterface> drawing_class(module,"DrawingCommandLineInterface");
    drawing_class.def(pybind11::init<>());
}

Void export_drawer(pybind11::module& module) {
    pybind11::class_<Drawer> drawer_class(module,"Drawer");
    drawer_class.def("__str__", &__cstr__<Drawer>);
    drawer_class.def("__repr__", &__cstr__<Drawer>);

    pybind11::class_<AffineDrawer> affine_drawer_class(module,"AffineDrawer");
    affine_drawer_class.def(pybind11::init<Nat>());
    pybind11::implicitly_convertible<AffineDrawer,Drawer>();
    drawer_class.def(pybind11::init<AffineDrawer>());

    pybind11::class_<GridDrawer> grid_drawer_class(module,"GridDrawer");
    grid_drawer_class.def(pybind11::init<Nat>());
    pybind11::implicitly_convertible<GridDrawer,Drawer>();
    drawer_class.def(pybind11::init<GridDrawer>());

    pybind11::class_<BoxDrawer> box_drawer_class(module,"BoxDrawer");
    box_drawer_class.def(pybind11::init<>());
    pybind11::implicitly_convertible<BoxDrawer,Drawer>();
    drawer_class.def(pybind11::init<BoxDrawer>());
}



Void export_drawer_manager(pybind11::module& module)
{
    auto const& reference = pybind11::return_value_policy::reference;
    pybind11::class_<DrawerManager> drawer_manager_class(module,"DrawerManager");
    drawer_manager_class.def_static("instance", &DrawerManager::instance, reference);
    drawer_manager_class.def("drawer", &DrawerManager::drawer, reference);
    drawer_manager_class.def("set_drawer", &DrawerManager::set_drawer);

}

Void export_drawing_figure_adapters(pybind11::module& module)
{
    static constexpr auto reference_internal = pybind11::return_value_policy::reference_internal;
    auto figure_class =
        pybind11::reinterpret_borrow<pybind11::class_<Figure>>(module.attr("Figure"));
    figure_class.def(pybind11::init([](ApproximateBoxType const& box,
                                      Projection2d const& projection) {
        return new Figure(to_rendering_box(box),projection);
    }));
    figure_class.def("set_bounding_box",
        [](Figure& figure, ApproximateBoxType const& box) -> Figure& {
            return figure.set_bounding_box(to_rendering_box(box));
        }, reference_internal);
    figure_class.def("draw",
        [](Figure& figure, RealBox const& box) -> Figure& {
            draw_to_figure(figure,box); return figure;
        }, reference_internal);
    figure_class.def("draw",
        [](Figure& figure, ApproximateBoxType const& box) -> Figure& {
            draw_to_figure(figure,box); return figure;
        }, reference_internal);
}

} // namespace

void drawing_submodule(pybind11::module& module)
{
    export_cli(module);
    export_drawer(module);
    export_drawer_manager(module);
    export_drawing_figure_adapters(module);
}
