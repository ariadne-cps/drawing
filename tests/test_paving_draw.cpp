#include <type_traits>
#include "ariadne-testing.hpp"
#include "drawing/grid_paving_draw.hpp"
#include "drawing/box_draw.hpp"
#include "rendering/null_rendering.hpp"

using namespace Ariadne;

class PavingCanvas final : public NullCanvas {
  public:
    Nat boundaries=0u;
    Void fill_boundary(List<Point2d> const&) override { ++boundaries; }
};

class TestPavingDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_paving_adapters() {
    static_assert(not std::is_base_of_v<Drawable2dInterface,SubPavingInterface>);
    static_assert(not std::is_base_of_v<Drawable2dInterface,GridTreePaving>);

    Grid grid(2u);
    GridTreePaving paving(grid);
    paving.adjoin(GridCell(grid,0u,BinaryWord()));

    PavingCanvas canvas;
    Projection2d projection(2u,0u,1u);
    draw(canvas,projection,static_cast<SubPavingInterface const&>(paving));
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,1u);

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
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,8u);
}

};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_paving_draw");
    ARIADNE_TESTING_ADD_TEST(TestPavingDraw, test_paving_adapters);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
