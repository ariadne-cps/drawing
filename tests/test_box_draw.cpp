/***************************************************************************
 *            test_box_draw.cpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/
#include <fstream>
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

    // Exercise the out-of-line overloads and verify that their owned
    // adapters survive until the Figure renders them.
    RealBox real{{0,2},{1,5}};
    ApproximateBoxType approximate(exact);
    draw(figure,real);
    draw(figure,approximate);
    figure._paint_all(canvas);
    ARIADNE_TEST_EQUALS(canvas.boundaries,5u)

    // Both conversion overloads preserve the actual display bounds.
    RenderingBox primitive{{-1.0,3.0},{0.0,6.0}};
    RenderingBox identity=to_rendering_box(primitive);
    ARIADNE_TEST_EQUALS(identity.dimension(),2u)
    ARIADNE_TEST_EQUALS(identity[0].lower_bound(),-1.0)
    ARIADNE_TEST_EQUALS(identity[1].upper_bound(),6.0)
    RenderingBox real_bounds=to_rendering_box(real);
    ARIADNE_TEST_EQUALS(real_bounds.dimension(),2u)
    ARIADNE_TEST_EQUALS(real_bounds[0].lower_bound(),0.0)
    ARIADNE_TEST_EQUALS(real_bounds[1].upper_bound(),5.0)
}

Void test_coloured_box_plot() {
    ExactBoxType exact{{0.0_x,1.0_x},{0.0_x,1.0_x}};
    BoxDrawable<ExactIntervalType> drawable(exact);
    List<Pair<Colour,Drawable2dInterface const&>> layers;
    layers.push_back(Pair<Colour,Drawable2dInterface const&>(blue,drawable));
    ApproximateBoxType viewport{{-1.0,2.0},{-1.0,2.0}};
    plot("test_box_draw-coloured",Projection2d(2u,0u,1u),viewport,layers);

    // An installed Rendering backend must produce a real PNG, not only
    // accept the overload or silently skip the output.
    std::ifstream image("test_box_draw-coloured.png",std::ios::binary);
    unsigned char signature[8]{};
    image.read(reinterpret_cast<char*>(signature),8);
    const unsigned char expected[8]={137,80,78,71,13,10,26,10};
    ARIADNE_TEST_ASSERT(image.gcount()==8)
    for(unsigned i=0; i!=8; ++i) {
        ARIADNE_TEST_EQUALS(signature[i],expected[i])
    }
}

Int main() {
    ARIADNE_TEST_CALL(test_box_drawing())
    ARIADNE_TEST_CALL(test_box_figure())
    ARIADNE_TEST_CALL(test_coloured_box_plot())
    return ARIADNE_TEST_FAILURES;
}
