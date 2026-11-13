/***************************************************************************
 *            tests/test_augmented_paving_draw.cpp
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

/** @file tests/test_augmented_paving_draw.cpp
 *  @brief Test augmented paving draw behavior.
 */

#include <type_traits>

#include "drawing/augmented_paving_draw.hpp"
#include "rendering/null_rendering.hpp"

#include "ariadne-testing.hpp"

using namespace Ariadne;
class AugmentedCanvas final : public NullCanvas {
  public:
    Nat boundaries = 0u;
    Void fill_boundary(const List<Point2d>&) override { ++boundaries; }
};
class TestAugmentedDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;
    Void test_augmented_draw() {
        static_assert(!std::is_base_of_v<Drawable2dInterface, AugmentedPaving>);
        Grid grid(2u);
        EffectiveVectorMultivariateFunction f = EffectiveVectorMultivariateFunction::identity(2u);
        AugmentedPaving paving(grid, f);
        paving.adjoin_outer_approximation(ExactBoxType({
                                              {-1, 1},
                                              {-1, 1}
        }),
                                          2u);
        Projection2d projection(4u, 0u, 1u);
        AugmentedCanvas canvas;
        draw(canvas, projection, paving);
        ARIADNE_TESTING_PROVE(canvas.boundaries > 0u);

        AugmentedPavingDrawable drawable(paving);
        // Rendering the auxiliary graph requires the state and auxiliary axes.
        ARIADNE_TESTING_EXPECT_EQUAL(paving.dimension(), 2u);
        ARIADNE_TESTING_EXPECT_EQUAL(drawable.dimension(), 4u);
        ARIADNE_TESTING_EXPECT_EQUAL(drawable.dimension(), paving.state_auxiliary_paving().dimension());
        auto copy = std::unique_ptr<Drawable2dInterface>(drawable.clone());
        ARIADNE_TESTING_EXPECT_EQUAL(copy->dimension(), drawable.dimension());
        copy->draw(canvas, projection);
        ARIADNE_TESTING_PROVE(canvas.boundaries > 0u);

        Figure figure(ApproximateBoxType({
                          {-2, +2},
                          {-2, +2},
                          {-2, +2},
                          {-2, +2}
        }),
                      projection);
        draw(figure, paving);
        figure << paving;
        const Nat boundaries_before_figure = canvas.boundaries;
        figure._paint_all(canvas);
        ARIADNE_TESTING_PROVE(canvas.boundaries > boundaries_before_figure);
    }
};
int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_augmented_paving_draw");
    ARIADNE_TESTING_ADD_TEST(TestAugmentedDraw, test_augmented_draw);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
