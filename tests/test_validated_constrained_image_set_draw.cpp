/***************************************************************************
 *            tests/test_validated_constrained_image_set_draw.cpp
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

/** @file tests/test_validated_constrained_image_set_draw.cpp
 *  @brief Test validated constrained image set draw behavior.
 */

#include "drawing/drawer.hpp"
#include "drawing/drawer_manager.hpp"
#include "drawing/geometry_draw.hpp"
#include "rendering/null_rendering.hpp"

#include "ariadne-testing.hpp"
using namespace Ariadne;

class ValidatedImageCanvas final : public NullCanvas {
  public:
    Nat boundaries = 0u;
    Void fill_boundary(const List<Point2d>&) override { ++boundaries; }
};
class TestValidatedConstrainedImageSetDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_validated_constrained_image_set_draw() {
        auto x = ValidatedScalarMultivariateFunction::coordinate(2u, 0u);
        auto y = ValidatedScalarMultivariateFunction::coordinate(2u, 1u);
        ValidatedVectorMultivariateFunction mapping({x + y, x - y});
        ValidatedConstrainedImageSet set(ExactBoxType{
                                             {-1.0_x, 1.0_x},
                                             {-2.0_x, 2.0_x}
        },
                                         mapping);
        Projection2d projection(2u, 0u, 1u);
        ValidatedImageCanvas canvas;

        DrawerManager::instance().set_drawer(BoxDrawer());
        draw(canvas, projection, set);
        ARIADNE_TESTING_PROVE(canvas.boundaries > 0u);

        Figure figure(ApproximateBoxType({
                          {-4, +4},
                          {-4, +4}
        }),
                      projection);
        draw(figure, set);
        figure._paint_all(canvas);
        ARIADNE_TESTING_PROVE(canvas.boundaries > 1u);

        DrawerManager::instance().set_drawer(AffineDrawer(0u));
        draw(canvas, projection, set);
        ARIADNE_TESTING_PROVE(canvas.boundaries > 2u);
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_validated_constrained_image_set_draw");
    ARIADNE_TESTING_ADD_TEST(TestValidatedConstrainedImageSetDraw, test_validated_constrained_image_set_draw);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
