/***************************************************************************
 *            tests/test_binary_tree_paving_draw.cpp
 *
 *  Copyright  2026  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne Drawing.
 *
 *  Ariadne Drawing is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne Drawing is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne Drawing. If not, see <https://www.gnu.org/licenses/>.
 */

/** @file tests/test_binary_tree_paving_draw.cpp
 *  @brief Test binary tree paving draw behavior.
 */

#include "drawing/binary_tree_paving_draw.hpp"
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

    Void test_binary_tree_paving_draw() {
    GridCell cell(Grid(1u),0u,BinaryWord("01"));
    BinaryTreePaving set(cell);
    auto product_set=product(cell,set);
    GridPavingCanvas canvas;
    Projection2d projection(2u,0u,1u);

    draw(canvas,projection,*product_set.begin());
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,1u);
    draw(canvas,projection,product_set);
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,2u);

    // The borrowed BinaryTreeSubpaving view must render the same enabled cells.
    // Also verify that its empty range does not emit a boundary.
    BinaryTreeSubpaving const& subpaving=product_set;
    draw(canvas,projection,subpaving);
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,3u);
    BinaryTreePaving empty_paving(2u);
    BinaryTreeSubpaving const& empty_subpaving=empty_paving;
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
    ARIADNE_TESTING_SUITE("test_binary_tree_paving_draw");
    ARIADNE_TESTING_ADD_TEST(TestGridPavingDraw, test_binary_tree_paving_draw);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
