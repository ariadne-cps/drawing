/***************************************************************************
 * Drawing-only dispatch for grid cells, pavings and compact box sets.
 ***************************************************************************/
#include "drawing/grid_paving_draw.hpp"
#include "drawing/geometry_draw.hpp"
#include "rendering/null_rendering.hpp"
#include "ariadne-testing.hpp"
using namespace Ariadne;

class GridPavingCanvas final : public NullCanvas {
  public:
    Nat boundaries=0u;
    Void fill_boundary(List<Point2d> const&) override { ++boundaries; }
};
class TestGridPavingDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_grid_paving_draw() {
    GridCell cell(Grid(1u),0u,BinaryWord("01"));
    GridTreePaving set(cell);
    auto product_set=product(cell,set);
    GridPavingCanvas canvas;
    Projection2d projection(2u,0u,1u);

    draw(canvas,projection,*product_set.begin());
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,1u);
    draw(canvas,projection,product_set);
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,2u);

    // The borrowed GridTreeSubpaving view must render the same enabled cells.
    // Also verify that its empty range does not emit a boundary.
    GridTreeSubpaving const& subpaving=product_set;
    draw(canvas,projection,subpaving);
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,3u);
    GridTreePaving empty_paving(2u);
    GridTreeSubpaving const& empty_subpaving=empty_paving;
    draw(canvas,projection,empty_subpaving);
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,3u);

    Figure figure(ApproximateBoxType({{-2,+2},{-2,+2}}),projection);
    figure.draw(*product_set.begin());
    figure.draw(subpaving);

    // All three public Figure entry points must retain and render the cell.
    // These also cover the free draw(Figure&, GridCell) overload and operator<<.
    draw(figure,*product_set.begin());
    figure << *product_set.begin();
    GridPavingCanvas figure_canvas;
    figure._paint_all(figure_canvas);
    ARIADNE_TESTING_EXPECT_EQUAL(figure_canvas.boundaries,4u);

    ExactBoxSetType box(ExactBoxType{{0.125_x,0.12500762939453125_x},{0.125_x,0.12500762939453125_x}});
    // Compact sets are first outer-approximated on a grid: the chosen depth
    // subdivides this narrow box into four cells, each with its own boundary.
    GridPavingCanvas compact_canvas;
    draw(compact_canvas,projection,static_cast<EffectiveEuclideanCompactSetInterface const&>(box));
    ARIADNE_TESTING_EXPECT_EQUAL(compact_canvas.boundaries,4u);
}
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_grid_paving_draw");
    ARIADNE_TESTING_ADD_TEST(TestGridPavingDraw, test_grid_paving_draw);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
