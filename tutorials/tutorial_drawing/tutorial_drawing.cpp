#include <iostream>
#include "ariadne-drawing.hpp"
#include "rendering/default_rendering.hpp"

using namespace Ariadne;

// Emit a completion only after a successful write, with immediate flushing.
void save(Figure const& figure, char const* filename) {
    figure.write(filename);
    std::cout << "Completed: " << filename << ".png" << std::endl;
}

int main() {
    RenderingManager::instance().set_backend(DefaultRenderingBackend());
    DrawerManager& manager=DrawerManager::instance();
    manager.set_drawer(AffineDrawer(1));
    std::cout << "Completed: rendering backend and initial drawer" << std::endl;

    RealBox first({{-1.8_dec,0.2_dec},{-1.0_dec,0.7_dec}});
    RealBox second({{-0.4_dec,1.7_dec},{-0.2_dec,1.4_dec}});
    ApproximateBoxType viewport({{-2.5,2.5},{-2.0,2.0}});
    Figure boxes(to_rendering_box(viewport),Projection2d(2,0,1));
    draw(boxes,first);
    draw(boxes,second);
    save(boxes,"tutorial_drawing_boxes");

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
    save(xy,"tutorial_drawing_projection_xy");
    Figure xz(to_rendering_box(viewport3d),Projection2d(3,0,2));
    draw(xz,set);
    save(xz,"tutorial_drawing_projection_xz");

    manager.set_drawer(BoxDrawer());
    Figure box_view(to_rendering_box(viewport3d),Projection2d(3,0,1));
    draw(box_view,set);
    save(box_view,"tutorial_drawing_drawer_box");

    manager.set_drawer(AffineDrawer(2));
    Figure affine_view(to_rendering_box(viewport3d),Projection2d(3,0,1));
    draw(affine_view,set);
    save(affine_view,"tutorial_drawing_drawer_affine");

    manager.set_drawer(GridDrawer(4));
    Figure grid_view(to_rendering_box(viewport3d),Projection2d(3,0,1));
    draw(grid_view,set);
    save(grid_view,"tutorial_drawing_drawer_grid");


    // Additional mathematical objects supported by the Drawing adapters.
    manager.set_drawer(BoxDrawer());
    ApproximateBoxType view2d({{-2.0,2.0},{-2.0,2.0}});
    Projection2d plane(2u,0u,1u);
    Figure points(to_rendering_box(view2d),plane);
    points.draw(Point<FloatDP>({FloatDP(0.25_x,dp),FloatDP(0.5_x,dp)}));
    save(points,"tutorial_drawing_points");

    using CurvePoint=InterpolatedCurve::PointType;
    CurvePoint p0({FloatDPApproximation(-1.0_x,dp),FloatDPApproximation(-0.5_x,dp)});
    CurvePoint p1({FloatDPApproximation(0.0_x,dp),FloatDPApproximation(0.75_x,dp)});
    InterpolatedCurve curve(p0,p1);
    Figure curves(to_rendering_box(view2d),plane);
    curves.draw(curve);
    save(curves,"tutorial_drawing_curve");

    ListSet<ExactBoxType> list(2u);
    list.adjoin(ExactBoxType{{-1.5_x,-0.5_x},{-0.75_x,0.25_x}});
    list.adjoin(ExactBoxType{{0.25_x,1.25_x},{-0.25_x,1.0_x}});
    Figure boxes_list(to_rendering_box(view2d),plane);
    boxes_list.draw(list);
    save(boxes_list,"tutorial_drawing_list");

    Grid grid(2u);
    GridCell cell(grid,0u,BinaryWord());
    Figure cells(to_rendering_box(view2d),plane);
    cells.draw(cell);
    save(cells,"tutorial_drawing_cell");
    GridTreePaving paving(grid);
    paving.adjoin(cell);
    Figure paving_figure(to_rendering_box(view2d),plane);
    paving_figure.draw(static_cast<SubPavingInterface const&>(paving));
    save(paving_figure,"tutorial_drawing_paving");

    RealBox domain({{-1.0_dec,1.0_dec},{-1.0_dec,1.0_dec}});
    BoundedConstraintSet bounded(domain);
    ConstrainedImageSet effective(domain);
    ValidatedConstrainedImageSet validated(ExactBoxType::unit_box(2));
    ValidatedAffineConstrainedImageSet affine_set(ExactBoxType::unit_box(2));
    Figure bounded_figure(to_rendering_box(view2d),plane);
    bounded_figure.draw(bounded);
    save(bounded_figure,"tutorial_drawing_bounded");
    Figure effective_figure(to_rendering_box(view2d),plane);
    effective_figure.draw(effective);
    save(effective_figure,"tutorial_drawing_effective");
    Figure validated_figure(to_rendering_box(view2d),plane);
    validated_figure.draw(validated);
    save(validated_figure,"tutorial_drawing_validated");
    Figure affine_set_figure(to_rendering_box(view2d),plane);
    affine_set_figure.draw(affine_set);
    save(affine_set_figure,"tutorial_drawing_affine_set");

    manager.set_drawer(AffineDrawer(0));
    std::cout << "Drawing mathematical objects and strategy comparisons complete.\n";
}
