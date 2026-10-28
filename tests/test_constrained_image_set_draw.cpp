/***************************************************************************
 * Figure adapters for effective constrained images and their subdivisions.
 * Set and Paving algorithms are tested in their respective modules.
 ***************************************************************************/
#include <limits>
#include "function/function.hpp"
#include "geometry/box.hpp"
#include "set/function_set.hpp"
#include "paving/grid_paving.hpp"
#include "paving/set_approximation.hpp"
#include "drawing/box_draw.hpp"
#include "drawing/geometry_draw.hpp"
#include "drawing/paving_draw.hpp"
#include "drawing/grid_paving_draw.hpp"
#include "macro/testing.hpp"
using namespace Ariadne;

class TestConstrainedImageSetDraw {
    Figure figure;
  public:
    TestConstrainedImageSetDraw()
        : figure(ApproximateBoxType({{-1,+1},{-1,+1}}),Projection2d(2,0,1)) { }
    Void test_draw(const StringType& str, const EffectiveConstrainedImageSet& set, Nat acc) {
        figure.clear();
        figure.set_bounding_box(ExactBoxType({{-2.75_x,+2.75_x},{-1.5_x,+2.0_x}}));
        ARIADNE_TEST_ASSERT(set.dimension()<=std::numeric_limits<Nat>::max());
        GridTreePaving paving(static_cast<Nat>(set.dimension()));
        adjoin_outer_approximation_to(paving,set,acc+1);
        figure.set_fill_opacity(1.0);
        figure.set_fill_colour(red);
        paving.recombine();
        draw(figure,paving);
        figure.set_fill_colour(green);
        figure.set_fill_opacity(0.5);
        typedef EffectiveConstrainedImageSet CIS;
        CIS s1,s2,s3,s4,s5,s6,s7,s8, s9,s10,s11,s12,s13,s14,s15,s16;
        make_lpair(s1,s2)=set.split();
        make_lpair(s3,s4)=s2.split(); make_lpair(s1,s2)=s1.split();
        make_lpair(s7,s8)=s4.split(); make_lpair(s5,s6)=s3.split(); make_lpair(s3,s4)=s2.split(); make_lpair(s1,s2)=s1.split();
        make_lpair(s15,s16)=s8.split(); make_lpair(s13,s14)=s7.split(); make_lpair(s11,s12)=s6.split(); make_lpair(s9,s10)=s5.split();
        make_lpair(s7,s8)=s4.split(); make_lpair(s5,s6)=s3.split(); make_lpair(s3,s4)=s2.split(); make_lpair(s1,s2)=s1.split();
        figure.draw(s1); figure.draw(s2); figure.draw(s3); figure.draw(s4);
        figure.draw(s5); figure.draw(s6); figure.draw(s7); figure.draw(s8);
        figure.draw(s9); figure.draw(s10); figure.draw(s11); figure.draw(s12);
        figure.draw(s13); figure.draw(s14); figure.draw(s15); figure.draw(s16);
        figure.write((StringType("test_function_set-draw-")+str).c_str());
        figure.clear();
    }

    Void test_draw() {
        EffectiveScalarMultivariateFunction s=EffectiveScalarMultivariateFunction::coordinate(2,0);
        EffectiveScalarMultivariateFunction t=EffectiveScalarMultivariateFunction::coordinate(2,1);
        EffectiveScalarMultivariateFunction x=EffectiveScalarMultivariateFunction::coordinate(2,0);
        EffectiveScalarMultivariateFunction y=EffectiveScalarMultivariateFunction::coordinate(2,1);
        Nat acc = 2u;

        test_draw("ellipse",EffectiveConstrainedImageSet(RealBox(2,RealInterval(-1,1)),{2*s+t,s+t},{s*s+t*t<=0.75_x}),acc+1u);
        test_draw("concave",EffectiveConstrainedImageSet(RealBox(2,RealInterval(-1.01_dec,1.01_dec)),{s,1.0_x*s*s+t},{2*s+0.25_x*s*s+t-2.0_x<=0}),acc);
    }
};
Int main() {
    TestConstrainedImageSetDraw test;
    ARIADNE_TEST_CALL(test.test_draw());
    return ARIADNE_TEST_FAILURES;
}
