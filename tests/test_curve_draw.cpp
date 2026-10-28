/***************************************************************************
 * Canvas rendering of InterpolatedCurve. Its constructors, bounding boxes,
 * cloning and functional semantics are tested by Set.
 ***************************************************************************/
#include "drawing/geometry_draw.hpp"
#include "rendering/null_rendering.hpp"
#include "macro/testing.hpp"
using namespace Ariadne;

class CurveCanvas : public NullCanvas {
  public:
    Nat moves=0u, lines=0u, fills=0u, strokes=0u;
    double last_x=0.0, last_y=0.0;
    Void move_to(double x,double y) override { ++moves; last_x=x; last_y=y; }
    Void line_to(double x,double y) override { ++lines; last_x=x; last_y=y; }
    Void fill() override { ++fills; }
    Void stroke() override { ++strokes; }
};

Void test_interpolated_curve_draw() {
    using P=InterpolatedCurve::PointType;
    P a({FloatDPApproximation(1,dp),FloatDPApproximation(2,dp)});
    P b({FloatDPApproximation(3,dp),FloatDPApproximation(4,dp)});
    Projection2d projection(2u,0u,1u);

    InterpolatedCurve empty;
    CurveCanvas empty_canvas;
    draw(empty_canvas,projection,empty);
    ARIADNE_TEST_EQUALS(empty_canvas.moves,0u);
    ARIADNE_TEST_EQUALS(empty_canvas.lines,0u);
    ARIADNE_TEST_EQUALS(empty_canvas.fills,0u);
    ARIADNE_TEST_EQUALS(empty_canvas.strokes,0u);

    InterpolatedCurve single(a);
    CurveCanvas single_canvas;
    draw(single_canvas,projection,single);
    ARIADNE_TEST_EQUALS(single_canvas.moves,1u);
    ARIADNE_TEST_EQUALS(single_canvas.lines,0u);
    ARIADNE_TEST_EQUALS(single_canvas.fills,1u);

    CurveCanvas canvas;
    InterpolatedCurve open(a,b);
    draw(canvas,projection,open);
    ARIADNE_TEST_EQUALS(canvas.moves,1u);
    ARIADNE_TEST_EQUALS(canvas.lines,1u);
    ARIADNE_TEST_EQUALS(canvas.strokes,1u);
    ARIADNE_TEST_EQUALS(canvas.last_x,3.0);
    ARIADNE_TEST_EQUALS(canvas.last_y,4.0);

    open.insert(Dyadic(2),a);
    draw(canvas,projection,open);
    ARIADNE_TEST_EQUALS(canvas.fills,1u);
    ARIADNE_TEST_EQUALS(canvas.lines,3u);
    ARIADNE_TEST_EQUALS(canvas.last_x,1.0);
    ARIADNE_TEST_EQUALS(canvas.last_y,2.0);

    InterpolatedCurve flat(FloatDP(0,dp),Vector<FloatDP>({1.0_x,2.0_x},dp));
    flat.insert(FloatDP(1,dp),Vector<FloatDP>({1.0_x,2.0_x},dp));
    draw(canvas,projection,flat);
    ARIADNE_TEST_EQUALS(canvas.fills,2u);
}
Int main() {
    ARIADNE_TEST_CALL(test_interpolated_curve_draw());
    return ARIADNE_TEST_FAILURES;
}
