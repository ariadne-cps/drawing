/***************************************************************************
 *            test_figure_drawing.cpp
 *
 *  Copyright  2008-26  Pieter Collins, Luca Geretti
 ****************************************************************************/

#include "macro/testing.hpp"

#include "function/function.hpp"
#include "rendering/figure.hpp"
#include "drawing/drawer.hpp"
#include "drawing/box_draw.hpp"
#include "drawing/geometry_draw.hpp"
#include "drawing/paving_draw.hpp"
#include "geometry/box.hpp"
#include "set/curve.hpp"
#include "set/function_set.hpp"
#include "paving/grid_paving.hpp"

using namespace Ariadne;

class TestFigureDrawing {
  public:
    void test() {
        ARIADNE_TEST_CALL(test_box_adapters())
        ARIADNE_TEST_CALL(test_default_drawer())
    }

    void test_box_adapters() {
        RealBox real_box({{-0.5_dec,0.5_dec},{-0.25_dec,0.25_dec}});
        Figure figure(ApproximateBoxType({{-1,+1},{-1,+1}}),Projection2d(2,0,1));
        draw(figure,real_box);
        figure.draw(real_box);
    }

    void test_default_drawer() {
        ExactBoxType bx1(2); bx1[0]=ExactIntervalType(-0.2_pr,0.2_pr); bx1[1]=ExactIntervalType(-0.1_pr,0.10_pr);
        ExactBoxType bx2(2); bx2[0]=ExactIntervalType(0.1_pr,0.3_pr); bx2[1]=ExactIntervalType(0.05_pr,0.15_pr);
        ExactBoxType bx3(2); bx3[0]=ExactIntervalType(0.2_pr,0.4_pr); bx3[1]=ExactIntervalType(0.10_pr,0.25_pr);
        ExactBoxType bx4(2); bx4[0]=ExactIntervalType(0.25_pr,0.5_pr); bx4[1]=ExactIntervalType(0.20_pr,0.50_pr);
        ExactBoxType bx5(2); bx5[0]=ExactIntervalType(0.4_pr,0.8_pr); bx5[1]=ExactIntervalType(0.40_pr,1.1_pr);

        Real p(0.5_x);
        EffectiveVectorMultivariateFunction x=EffectiveVectorMultivariateFunction::identity(3);
        EffectiveVectorMultivariateFunction afn1={0.05_dec*x[0]+0.05_dec*x[2]+0.15_dec,0.05_dec*x[1]+0.05_dec*x[2]+0.6_dec};
        ValidatedConstrainedImageSet s1(ExactBoxType::unit_box(3),afn1);
        ApproximateBoxType bbx1=widen(s1.bounding_box(),0.25_x);

        EffectiveVectorMultivariateFunction rf(1u,sqr(x[0])+sqr(x[1])-sqr(p));
        ConstraintSet cs1(rf,RealBox(1u,RealInterval(-1,0)));
        (void)cs1;

        {
            ExactDouble h=10000;
            Figure g(ExactBoxType{{-1.0_x,+1.0_x},{-h,+h}},Projection2d(2,0,1));
            g.set_fill_colour(0.5,1.0,1.0);
            g.set_line_width(10);
            g << ExactBoxType({{-0.5_x,+0.0_x},{-h/two,+h/two}});
            g.set_line_width(1);
            g << ExactBoxType({{0.25_x,+0.75_x},{-h/two,+h/two}});
            g.write("test_rendering-canvas");
        }

        Figure g(ApproximateBoxType({{-1,+1},{-1,+1}}),Projection2d(2,0,1));
        g << fill_colour(0.5,1.0,1.0)
          << line_colour(0.0,0.0,0.0)
          << bx1 << bx2 << bx3 << bx4 << bx5;
        g.write("test_rendering-bx1");
        g.clear();

        g.set_fill_colour(1.0,0.5,1.0);
        g.draw(bx1);
        g.draw(bx2);
        g.set_fill_colour(magenta);
        g.draw(bx5);
        g.write("test_rendering-bx2");
        g.clear();

        ExactBoxType bx3d(3);
        bx3d[0]=ExactIntervalType(0.2_pr,0.4_pr);
        bx3d[1]=ExactIntervalType(0.2_pr,0.5_pr);
        bx3d[2]=ExactIntervalType(0.2_pr,0.7_pr);
        g.set_bounding_box(bx3d.bounding_box());
        g.set_projection(3,0,1);
        g.draw(bx3d);
        g.write("test_rendering-bx3");
        g.clear();

        plot("test_rendering_set",Projection2d(2,0,1),bbx1,orange,s1);

        InterpolatedCurve cv(0,Point<FloatDP>(2,FloatDP(0.0_x,dp)));
        for(Int i=1; i<=10; ++i) {
            Point<FloatDP> pt(2,dp);
            pt[0]=FloatDP(cast_exact(i/10.),dp);
            pt[1]=FloatDP(cast_exact(i*i/100.),dp);
            cv.insert(i,pt);
        }
        g.set_bounding_box(cv.bounding_box());
        g.set_projection(2,0,1);
        g.set_line_colour(1,0,0);
        g.draw(cv);
        g.set_line_colour(0,0,0);
        g.write("test_rendering-curve");
        g.clear();

        GridTreePaving gts(2);
        gts.adjoin_outer_approximation(bx1,4);
        gts.adjoin_outer_approximation(bx2,5);
        gts.adjoin_outer_approximation(bx3,6);
        gts.adjoin_outer_approximation(bx4,7);
        gts.adjoin_outer_approximation(bx5,8);
        gts.recombine();

        ExactBoxType bbox(2);
        bbox[0]=ExactIntervalType(-2,2);
        bbox[1]=ExactIntervalType(-2,2);
        g.set_bounding_box(bbox);
        g.set_projection(2,0,1);
        g << gts;
        g.write("test_rendering-paving");
        g.clear();
    }
};

Int main() {
    TestFigureDrawing().test();
    return ARIADNE_TEST_FAILURES;
}
