/***************************************************************************
 * Drawing adapters for affine constrained sets.
 * Mathematical algorithms are exercised by kernel/tests/geometry.
 ***************************************************************************/
#include <iostream>
#include "function/function.hpp"
#include "geometry/box.hpp"
#include "geometry/affine_set.hpp"
#include "rendering/geometry2d.hpp"
#include "drawing/box_draw.hpp"
#include "drawing/geometry_draw.hpp"
#include "macro/testing.hpp"

using namespace Ariadne;
using namespace std;

static const Colour colour(0.5,1.0,1.0);
static const Colour expected_colour(1.0,0.25,0.25);

namespace Ariadne {

template<class X> AffineConstraint<X> operator<=(const Dyadic& l, const Affine<X>& a) {
    return AffineConstraint<X>({l,a.value().precision()},a,{+infty,a.value().precision()}); }
template<class X> AffineConstraint<X> operator<=(const Affine<X>& a, const Dyadic& u) {
    return AffineConstraint<X>(-infty,a,u); }
template<class X> AffineConstraint<X> operator<=(const AffineConstraint<X>& ac, const Dyadic& u) {
    ARIADNE_ASSERT(decide(ac.upper_bound()==infty));
    return AffineConstraint<X>(ac.lower_bound(),ac.function(),{u,ac.lower_bound().precision()}); }
template<class X> AffineConstraint<X> operator==(const Affine<X>& a, const Dyadic& u) {
    return AffineConstraint<X>(u,a,u); }
}

struct FloatDPVector2d : FloatDPVector, Vector2d {
    FloatDPVector2d(double vx, double vy) : FloatDPVector({ExactDouble(vx),ExactDouble(vy)},dp), Vector2d(vx,vy) { }
};


class TestAffineSetDraw {
    Figure figure;
    ExactBoxType D;
    Vector< Affine<FloatDPBounds> > x;
    ValidatedAffineConstrainedImageSet set;
  public:
    TestAffineSetDraw()
        : figure(ApproximateBoxType({{-1,+1},{-1,+1}}),Projection2d(2,0,1)),
          set(ExactBoxType::unit_box(2),Matrix<FloatDP>(2,2,dp),Vector<FloatDP>(2,dp)) { }

    Void test_draw() {
        FloatDPVector2d offsets{0.0,0.0}; // Offsets
        FloatDPVector& o=offsets;
        Polytope2d expected_set({{0.0,0.0}});
        Vector< Affine<FloatDPBounds> > a;
        ExactBoxType dom;
        figure.clear();
        figure.set_bounding_box(ExactBoxType{{-1.0_x,+15.0_x},{-1.0_x,+15.0_x}});
        figure.set_fill_colour(0.5,1.0,1.0);
        figure.set_fill_opacity(0.5);

        {
            // Draw overlapping sets to check colours
            figure << fill_colour(expected_colour) << Polytope2d({{0.,-0.5},{2.,-0.5},{2.,0.},{0.,0.}})
                   << fill_colour(colour) << Polytope2d({{1.,-0.5},{3.,-0.5},{3.,0.},{1.,0.}});
        }

        {
            // Test draw of nondegenerate two-dimensional image set
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{1.0,13.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+0.5_x*a[0],o[1]+0.25_x*a[1]});
            expected_set=Polytope2d({{-0.5,-0.25}, {+0.5,-0.25}, {+0.5,+0.25},{-0.5,+0.25}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of nondegenerate two-dimensional constrained image set
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d(4.0,13.0);
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+0.5_x*a[0],o[1]+0.25_x*a[1]},{a[0]+a[1]<=0.5_x});
            expected_set=Polytope2d({{-0.5,-0.25}, {+0.5,-0.25}, {+0.5,-0.125}, {-0.25,+0.25},{-0.5,+0.25}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of two-dimensional image set with errors
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{7.0,13.0};
            FloatDPBounds e=FloatDPBounds(-1.0_x,+1.0_x,dp);

            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+0.25_x*a[0]+0.25_x*a[1]+0.5_x*e,o[1]+0.5_x*a[0]-0.5_x*a[1]});
            expected_set=Polytope2d({{-1.0,0.0}, {-0.5,-1.0}, {+0.5,-1.0}, {+1.0,0.0}, {+0.5,+1.0}, {-0.5,+1.0}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of nondegenerate one-dimensional image set
            a=Affine<FloatDPBounds>::variables(1,dp);
            dom=ExactBoxType::unit_box(1);
            offsets=FloatDPVector2d{1.0,1.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+0.5_x*a[0],o[1]+0.25_x*a[0]},{0.0_x*a[0]<=1.0_x,a[0]==0.75_x});
            expected_set=Polytope2d({{0.375, 0.1875}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of one-dimensional image set
            a=Affine<FloatDPBounds>::variables(1,dp);
            dom=ExactBoxType::unit_box(1);
            offsets=FloatDPVector2d{4.0,1.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+0.5_x*a[0],o[1]+0.25_x*a[0]});
            expected_set=Polytope2d({{-0.5,-0.25}, {0.5,0.25}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of one-dimensional constraint set
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{7.0,1.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{0.0_x*a[0]<=1.0_x,a[0]+a[1]==0.5_x});
            expected_set=Polytope2d({{-0.5,+1.0}, {+1.0,-0.5}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of one-dimensional constraint set with one proper constraint on boundary
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{10.0,1.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{1.0_x<=a[0], a[1]<=0.5_x});
            expected_set=Polytope2d({{+1.0,-1.0}, {+1.0,+0.5}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of set with constraint a<=0 and a>=0
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{13.0,1.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{a[0]+0.5_x*a[1]<=0.75_x,0.75_x<=a[0]+0.5_x*a[1]});
            expected_set=Polytope2d({{+0.25,+1.0}, {+1.0,-0.5}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of set with constraint 0<=a<=0
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{13.0,1.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{0.75_x<=a[0]+0.5_x*a[1]<=0.75_x});
            expected_set=Polytope2d({{+0.25,+1.0}, {+1.0,-0.5}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of set with degenerate constraints at corner of box
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{1.0,4.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{a[0]+2*a[1]<=3,1.5_x*(a[0]+a[1])<=3,2*a[0]+a[1]<=3});
            expected_set=Polytope2d({{-1.0,-1.0}, {+1.0,-1.0}, {+1.0,+1.0}, {-1.0,+1.0}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of set with degenerate constraints near corner of box
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{4.0,4.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{a[0]+2*a[1]<=2,1.5_x*(a[0]+a[1])<=2,2*a[0]+a[1]<=2});
            expected_set=Polytope2d({{-1.0,-1.0}, {+1.0,-1.0}, {+1.0,0.0}, {+0.667,+0.667}, {0.0,+1.0}, {-1.0,+1.0}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of set repeated constraints
            a=Affine<FloatDPBounds>::variables(2,dp);
            dom=ExactBoxType::unit_box(2);
            offsets=FloatDPVector2d{7.0,4.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{a[0]+2.0_x*a[1]<=2.0_x,a[0]/3.0_x+a[1]*2.0_x/3.0_x<=0.333333333333333333_pr});
            expected_set=Polytope2d({{-1.0,-1.0}, {+1.0,-1.0}, {+1.0,0.5}, {0.0,+1.0}, {-1.0,+1.0}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of projection of three-dimensional box with single equality constraint
            a=Affine<FloatDPBounds>::variables(3,dp);
            dom=ExactBoxType::unit_box(3);
            offsets=FloatDPVector2d{10.0,4.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+a[0],o[1]+a[1]},{a[0]+2.0_x*a[1]+a[2]==1.5_x});
            expected_set=Polytope2d({{+1.0,-0.25}, {+1.0,+0.75}, {+0.5,+1.0}, {-1.0,+1.0}, {-1.0,+0.75}}) + offsets;
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        {
            // Test draw of two-dimensional set with nondegenerate inequality and equality constraints
            a=Affine<FloatDPBounds>::variables(3,dp);
            dom=ExactBoxType::unit_box(3);
            offsets=FloatDPVector2d{1.0,7.0};
            set=ValidatedAffineConstrainedImageSet(dom, {o[0]+0.3_pr*a[0]+0.20_pr*a[1]+0.05_pr*a[2],o[1]-0.10_pr*a[0]+0.1_pr*a[1]+0.05_pr*a[2]},{a[1]-a[2]<=-0.25_x,a[0]+a[1]+a[2]==0.5_x});
            expected_set=Polytope2d({{+0.0,0.0}}) + offsets; // Unknown
            figure << fill_colour(expected_colour) << expected_set << fill_colour(colour) << set;
        }

        figure.write("test_affine_set-draw");
    }
};
Int main() {
    TestAffineSetDraw test;
    ARIADNE_TEST_CALL(test.test_draw());
    return ARIADNE_TEST_FAILURES;
}
