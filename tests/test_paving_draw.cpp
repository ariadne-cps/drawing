/***************************************************************************
 *            tests/test_paving_draw.cpp
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

/** @file tests/test_paving_draw.cpp
 *  @brief Test paving draw behavior.
 */

#include <type_traits>
#include "ariadne-testing.hpp"
#include "drawing/binary_tree_paving_draw.hpp"
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
    static_assert(not std::is_base_of_v<Drawable2dInterface,BinaryTreePaving>);

    Grid grid(2u);
    BinaryTreePaving paving(grid);
    paving.adjoin(GridCell(grid,0u,BinaryWord()));

    PavingCanvas canvas;
    Projection2d projection(2u,0u,1u);
    draw(canvas,projection,static_cast<SubPavingInterface const&>(paving));
    ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries,1u);

    Figure figure(ApproximateBoxType({{-2,+2},{-2,+2}}),projection);
    figure << static_cast<SubPavingInterface const&>(paving);
    Paving handle(new BinaryTreePaving(paving));
    figure << handle;
    SubPaving sub_handle(static_cast<SubPavingInterface const&>(paving));
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
