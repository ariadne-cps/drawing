#include <type_traits>
#include "macro/testing.hpp"
#include "drawing/grid_paving_draw.hpp"
#include "drawing/box_draw.hpp"
#include "rendering/null_rendering.hpp"

using namespace Ariadne;

class PavingCanvas final : public NullCanvas {
  public:
    Nat boundaries=0u;
    Void fill_boundary(List<Point2d> const&) override { ++boundaries; }
};

Void test_paving_adapters() {
    static_assert(not std::is_base_of_v<Drawable2dInterface,SubPavingInterface>);
    static_assert(not std::is_base_of_v<Drawable2dInterface,GridTreePaving>);

    Grid grid(2u);
    GridTreePaving paving(grid);
    paving.adjoin(GridCell(grid,0u,BinaryWord()));

    PavingCanvas canvas;
    Projection2d projection(2u,0u,1u);
    draw(canvas,projection,static_cast<SubPavingInterface const&>(paving));
    ARIADNE_TEST_EQUALS(canvas.boundaries,1u)

    Figure figure(ApproximateBoxType({{-2,+2},{-2,+2}}),projection);
    figure << static_cast<SubPavingInterface const&>(paving);
    PavingHandle handle(new GridTreePaving(paving));
    figure << handle;
    SubPavingHandle sub_handle(static_cast<SubPavingInterface const&>(paving));
    figure << sub_handle;
    figure.draw(static_cast<SubPavingInterface const&>(paving));
    figure.draw(paving);
    figure.draw(handle);
    figure.draw(sub_handle);

    // Figure owns independent clones of each paving.
    figure._paint_all(canvas);
    ARIADNE_TEST_EQUALS(canvas.boundaries,8u)
}

Int main() {
    ARIADNE_TEST_CALL(test_paving_adapters())
    return ARIADNE_TEST_FAILURES;
}
