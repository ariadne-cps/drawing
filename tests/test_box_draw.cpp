/***************************************************************************
 *            test_box_draw.cpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/
#include <memory>
#include <type_traits>
#include "macro/testing.hpp"
#include "drawing/box_draw.hpp"
#include "drawing/list_set_draw.hpp"
#include "rendering/null_rendering.hpp"

using namespace Ariadne;

class CountingBoxCanvas final : public NullCanvas {
  public:
    Nat boundaries=0u;
    Void fill_boundary(List<Point2d> const&) override { ++boundaries; }
};

Void test_box_drawing() {
    static_assert(not std::is_base_of_v<Drawable2dInterface,ExactBoxSetType>);
    static_assert(not std::is_base_of_v<Drawable2dInterface,ApproximateBoxSetType>);
    static_assert(not std::is_base_of_v<Drawable2dInterface,RealBoxSet>);

    CountingBoxCanvas canvas;
    Projection2d projection(2u,0u,1u);
    ExactBoxType exact{{0.0_x,2.0_x},{1.0_x,5.0_x}};
    ApproximateBoxType approximate_box(exact);
    RealBox real{{0,2},{1,5}};
    ExactBoxSetType exact_set(exact);
    ApproximateBoxSetType approx_set(approximate_box);
    RealBoxSet real_set(real);

    draw(canvas,projection,exact_set);
    draw(canvas,projection,approx_set);
    draw(canvas,projection,real_set);
    ARIADNE_TEST_EQUALS(canvas.boundaries,3u)

    BoxDrawable<ExactIntervalType> adapter(exact);
    std::unique_ptr<Drawable2dInterface> copy(adapter.clone());
    copy->draw(canvas,projection);
    ARIADNE_TEST_EQUALS(canvas.boundaries,4u)

    ListSet<ExactBoxType> list(2u);
    list.adjoin(exact);
    list.adjoin(exact);
    draw(canvas,projection,list);
    ARIADNE_TEST_EQUALS(canvas.boundaries,6u)
}

Void test_box_figure() {
    CountingBoxCanvas canvas;
    ExactBoxType exact{{0.0_x,2.0_x},{1.0_x,5.0_x}};
    Figure figure(ApproximateBoxType({{-1,+3},{0,+6}}),Projection2d(2u,0u,1u));
    draw(figure,exact);
    figure << exact;
    figure.draw(ApproximateBoxType(exact));
    figure._paint_all(canvas);
    ARIADNE_TEST_EQUALS(canvas.boundaries,3u)
}

Int main() {
    ARIADNE_TEST_CALL(test_box_drawing())
    ARIADNE_TEST_CALL(test_box_figure())
    return ARIADNE_TEST_FAILURES;
}
