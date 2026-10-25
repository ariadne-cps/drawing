#include <iostream>
#include "ariadne-drawing.hpp"
#include "rendering/default_rendering.hpp"

using namespace Ariadne;

int main() {
    RenderingManager::instance().set_backend(DefaultRenderingBackend());
    DrawerManager& manager=DrawerManager::instance();
    manager.set_drawer(AffineDrawer(1));

    RealBox first({{-1.8_dec,0.2_dec},{-1.0_dec,0.7_dec}});
    RealBox second({{-0.4_dec,1.7_dec},{-0.2_dec,1.4_dec}});
    ApproximateBoxType viewport({{-2.5,2.5},{-2.0,2.0}});
    Figure boxes(to_rendering_box(viewport),Projection2d(2,0,1));
    draw(boxes,first);
    draw(boxes,second);
    boxes.write("tutorial_drawing_boxes");

    auto coordinates=EffectiveScalarMultivariateFunction::coordinates(3);
    EffectiveVectorMultivariateFunction map({
        1.25_dec*coordinates[0]+0.35_dec*coordinates[2],
        coordinates[1]+0.20_dec*coordinates[0]*coordinates[0],
        coordinates[2]-0.30_dec*coordinates[0]
    });
    ValidatedConstrainedImageSet set(ExactBoxType::unit_box(3),map);
    ApproximateBoxType viewport3d({{-2.0,2.0},{-2.0,2.0},{-2.0,2.0}});
    Figure xy(to_rendering_box(viewport3d),Projection2d(3,0,1));
    draw(xy,set);
    xy.write("tutorial_drawing_projection_xy");
    Figure xz(to_rendering_box(viewport3d),Projection2d(3,0,2));
    draw(xz,set);
    xz.write("tutorial_drawing_projection_xz");

    manager.set_drawer(BoxDrawer());
    Figure box_view(to_rendering_box(viewport3d),Projection2d(3,0,1));
    draw(box_view,set);
    box_view.write("tutorial_drawing_drawer_box");

    manager.set_drawer(AffineDrawer(2));
    Figure affine_view(to_rendering_box(viewport3d),Projection2d(3,0,1));
    draw(affine_view,set);
    affine_view.write("tutorial_drawing_drawer_affine");

    manager.set_drawer(GridDrawer(4));
    Figure grid_view(to_rendering_box(viewport3d),Projection2d(3,0,1));
    draw(grid_view,set);
    grid_view.write("tutorial_drawing_drawer_grid");

    manager.set_drawer(AffineDrawer(0));
    std::cout << "Drawing mathematical objects and strategy comparisons complete.\n";
}
