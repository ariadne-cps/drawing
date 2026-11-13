/***************************************************************************
 *            tests/test_curve_draw.cpp
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

/** @file tests/test_curve_draw.cpp
 *  @brief Test curve draw behavior.
 */

#include "drawing/geometry_draw.hpp"
#include "rendering/null_rendering.hpp"

#include "ariadne-testing.hpp"
using namespace Ariadne;

class CurveCanvas : public NullCanvas {
  public:
    Nat moves = 0u, lines = 0u, fills = 0u, strokes = 0u;
    double last_x = 0.0, last_y = 0.0;
    Void move_to(double x, double y) override {
        ++moves;
        last_x = x;
        last_y = y;
    }
    Void line_to(double x, double y) override {
        ++lines;
        last_x = x;
        last_y = y;
    }
    Void fill() override { ++fills; }
    Void stroke() override { ++strokes; }
};

class TestCurveDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_interpolated_curve_draw() {
        using P = InterpolatedCurve::PointType;
        P a({FloatDPApproximation(1, dp), FloatDPApproximation(2, dp)});
        P b({FloatDPApproximation(3, dp), FloatDPApproximation(4, dp)});
        Projection2d projection(2u, 0u, 1u);

        InterpolatedCurve empty;
        CurveCanvas empty_canvas;
        draw(empty_canvas, projection, empty);
        ARIADNE_TESTING_EXPECT_EQUAL(empty_canvas.moves, 0u);
        ARIADNE_TESTING_EXPECT_EQUAL(empty_canvas.lines, 0u);
        ARIADNE_TESTING_EXPECT_EQUAL(empty_canvas.fills, 0u);
        ARIADNE_TESTING_EXPECT_EQUAL(empty_canvas.strokes, 0u);

        InterpolatedCurve single(a);
        CurveCanvas single_canvas;
        draw(single_canvas, projection, single);
        ARIADNE_TESTING_EXPECT_EQUAL(single_canvas.moves, 1u);
        ARIADNE_TESTING_EXPECT_EQUAL(single_canvas.lines, 0u);
        ARIADNE_TESTING_EXPECT_EQUAL(single_canvas.fills, 1u);

        CurveCanvas canvas;
        InterpolatedCurve open(a, b);
        draw(canvas, projection, open);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.moves, 1u);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.lines, 1u);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.strokes, 1u);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.last_x, 3.0);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.last_y, 4.0);

        open.insert(Dyadic(2), a);
        draw(canvas, projection, open);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.fills, 1u);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.lines, 3u);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.last_x, 1.0);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.last_y, 2.0);

        InterpolatedCurve flat(FloatDP(0, dp), Vector<FloatDP>({1.0_x, 2.0_x}, dp));
        flat.insert(FloatDP(1, dp), Vector<FloatDP>({1.0_x, 2.0_x}, dp));
        draw(canvas, projection, flat);
        ARIADNE_TESTING_EXPECT_EQUAL(canvas.fills, 2u);
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_curve_draw");
    ARIADNE_TESTING_ADD_TEST(TestCurveDraw, test_interpolated_curve_draw);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
