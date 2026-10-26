/***************************************************************************
 *            test_point_draw.cpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/

/*
 *  This file is part of Ariadne.
 *
 *  Ariadne is free software under the GNU General Public License,
 *  version 3 or (at your option) any later version.
 */

#include <memory>
#include <type_traits>

#include "macro/testing.hpp"
#include "geometry/box.hpp"
#include "drawing/point_draw.hpp"
#include "drawing/box_draw.hpp"
#include "rendering/null_rendering.hpp"

using namespace Ariadne;

class PointCanvas final : public NullCanvas {
  public:
    double x=0,y=0;
    Nat dots=0,strokes=0;
    Void dot(double px,double py) override { x=px; y=py; ++dots; }
    Void stroke() override { ++strokes; }
};

Void test_canvas_point() {
    static_assert(not std::is_base_of_v<Drawable2dInterface,Point<FloatDPApproximation>>);
    Point<FloatDPApproximation> pt({1.0_x,2.0_x},dp);
    PointCanvas canvas;

    draw(canvas,Projection2d(2u,1u,0u),pt);
    ARIADNE_TEST_EQUALS(canvas.dots,1u)
    ARIADNE_TEST_EQUALS(canvas.strokes,1u)
    ARIADNE_TEST_EQUALS(canvas.x,2.0)
    ARIADNE_TEST_EQUALS(canvas.y,1.0)

    PointDrawable<FloatDPApproximation> adapter(pt);
    ARIADNE_TEST_EQUALS(adapter.dimension(),2u)
    std::unique_ptr<Drawable2dInterface> copy(adapter.clone());
    copy->draw(canvas,Projection2d(2u,0u,1u));
    ARIADNE_TEST_EQUALS(canvas.dots,2u)
    ARIADNE_TEST_EQUALS(canvas.strokes,2u)
    ARIADNE_TEST_EQUALS(canvas.x,1.0)
    ARIADNE_TEST_EQUALS(canvas.y,2.0)
}

Void test_point_projection() {
    Point<FloatDPApproximation> pt({1.0_x,2.0_x},dp);
    auto joined=product(pt,pt);
    ARIADNE_TEST_ASSERT(decide(project(joined,Projection2d(4u,2u,3u))==pt))
    ARIADNE_TEST_FAIL(project(pt,Projection2d(3u,0u,1u)))
}

Void test_figure_point() {
    Point<FloatDPApproximation> pt({1.0_x,2.0_x},dp);
    Figure figure(ApproximateBoxType({{-1,+3},{-1,+3}}),Projection2d(2u,0u,1u));

    draw(figure,pt);
    figure << pt;
    figure.draw(pt); // Test template dispatch in addition to free draw.

    PointCanvas canvas;
    figure._paint_all(canvas);
    ARIADNE_TEST_EQUALS(canvas.dots,3u)
    ARIADNE_TEST_EQUALS(canvas.strokes,3u)
    ARIADNE_TEST_EQUALS(canvas.x,1.0)
    ARIADNE_TEST_EQUALS(canvas.y,2.0)
}

Int main() {
    ARIADNE_TEST_CALL(test_canvas_point())
    ARIADNE_TEST_CALL(test_point_projection())
    ARIADNE_TEST_CALL(test_figure_point())
    return ARIADNE_TEST_FAILURES;
}
