/***************************************************************************
 *            tests/test_constrained_image_set_draw.cpp
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

/** @file tests/test_constrained_image_set_draw.cpp
 *  @brief Test constrained image set draw behavior.
 */


#include "drawing/box_draw.hpp"
#include "drawing/drawer.hpp"
#include "drawing/drawer_manager.hpp"
#include "drawing/geometry_draw.hpp"
#include "function/function.hpp"
#include "geometry/box.hpp"
#include "logging/test_runner.hpp"
#include "rendering/null_rendering.hpp"
#include "set/function_set.hpp"

#include "ariadne-testing.hpp"
using namespace Ariadne;

// Count rendering operations rather than merely checking that the drawing
// scenario completed without raising an exception.
class CountingConstrainedImageCanvas final : public NullCanvas {
  public:
    Nat boundaries = 0u;
    Void fill_boundary(const List<Point2d>&) override { ++boundaries; }
};

class TestConstrainedImageSetDraw : public Ariadne::Testing::ContextFixture {
    Figure figure;

  public:
    explicit TestConstrainedImageSetDraw(Ariadne::Testing::Context& context)
        : ContextFixture(context), figure(ApproximateBoxType({
                                              {-1, +1},
                                              {-1, +1}
    }),
                                          Projection2d(2, 0, 1)) {}
    Void draw_constrained_image_case(const StringType& str, const EffectiveConstrainedImageSet& set) {
        figure.clear();
        figure.set_bounding_box(ExactBoxType({
            {-2.75_x, +2.75_x},
            { -1.5_x,  +2.0_x}
        }));
        figure.set_fill_opacity(1.0);
        figure.set_fill_colour(red);
        draw(figure, set);
        figure.set_fill_colour(green);
        figure.set_fill_opacity(0.5);
        typedef EffectiveConstrainedImageSet CIS;
        CIS s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16;
        make_lpair(s1, s2) = set.split();
        make_lpair(s3, s4) = s2.split();
        make_lpair(s1, s2) = s1.split();
        make_lpair(s7, s8) = s4.split();
        make_lpair(s5, s6) = s3.split();
        make_lpair(s3, s4) = s2.split();
        make_lpair(s1, s2) = s1.split();
        make_lpair(s15, s16) = s8.split();
        make_lpair(s13, s14) = s7.split();
        make_lpair(s11, s12) = s6.split();
        make_lpair(s9, s10) = s5.split();
        make_lpair(s7, s8) = s4.split();
        make_lpair(s5, s6) = s3.split();
        make_lpair(s3, s4) = s2.split();
        make_lpair(s1, s2) = s1.split();
        figure.draw(s1);
        figure.draw(s2);
        figure.draw(s3);
        figure.draw(s4);
        figure.draw(s5);
        figure.draw(s6);
        figure.draw(s7);
        figure.draw(s8);
        figure.draw(s9);
        figure.draw(s10);
        figure.draw(s11);
        figure.draw(s12);
        figure.draw(s13);
        figure.draw(s14);
        figure.draw(s15);
        figure.draw(s16);
        CountingConstrainedImageCanvas canvas;
        figure._paint_all(canvas);
        // The original set and all 16 refinements must each render a boundary.
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.boundaries, 17u);
        figure.write((StringType("test_function_set-draw-") + str).c_str());
        figure.clear();
    }

    Void test_draw() {
        DrawerManager::instance().set_drawer(BoxDrawer());
        EffectiveScalarMultivariateFunction s = EffectiveScalarMultivariateFunction::coordinate(2, 0);
        EffectiveScalarMultivariateFunction t = EffectiveScalarMultivariateFunction::coordinate(2, 1);
        EffectiveScalarMultivariateFunction x = EffectiveScalarMultivariateFunction::coordinate(2, 0);
        EffectiveScalarMultivariateFunction y = EffectiveScalarMultivariateFunction::coordinate(2, 1);

        draw_constrained_image_case("ellipse", EffectiveConstrainedImageSet(RealBox(2, RealInterval(-1, 1)), {2 * s + t, s + t}, {s * s + t * t <= 0.75_x}));
        draw_constrained_image_case("concave", EffectiveConstrainedImageSet(RealBox(2, RealInterval(-1.01_dec, 1.01_dec)), {s, 1.0_x * s * s + t}, {2 * s + 0.25_x * s * s + t - 2.0_x <= 0}));
    }
};
int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_constrained_image_set_draw");
    ARIADNE_TESTING_ADD_TEST(TestConstrainedImageSetDraw, test_draw);
    return Ariadne::Testing::run_logging_suite(ariadne_test_suite, argc, argv);
}
