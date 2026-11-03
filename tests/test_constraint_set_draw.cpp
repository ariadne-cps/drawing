/***************************************************************************
 * The bounded constraint-set drawing adapter is owned by Drawing.
 ***************************************************************************/
#include "drawing/geometry_draw.hpp"
#include "drawing/drawer_manager.hpp"
#include "drawing/drawer.hpp"
#include "rendering/null_rendering.hpp"
#include "ariadne-testing.hpp"

using namespace Ariadne;

class ConstraintCanvas final : public NullCanvas {
  public:
    Nat boundaries=0u;
    Void fill_boundary(List<Point2d> const&) override { ++boundaries; }
};

class TestConstraintSetDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_bounded_constraint_set_draw() {
    auto x=EffectiveScalarMultivariateFunction::coordinate(2u,0u);
    auto y=EffectiveScalarMultivariateFunction::coordinate(2u,1u);
    EffectiveVectorMultivariateFunction identity({x,y});
    RealBox domain{{-2,2},{-3,3}};
    BoundedConstraintSet bounded(domain,identity,RealBox{{-1,1},{-1,1}});

    DrawerManager::instance().set_drawer(BoxDrawer());
    ConstraintCanvas canvas;
    draw(canvas,Projection2d(2u,0u,1u),bounded);
    ARIADNE_TESTING_PROVE(canvas.boundaries>0u);
    DrawerManager::instance().set_drawer(AffineDrawer(0u));
}
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_constraint_set_draw");
    ARIADNE_TESTING_ADD_TEST(TestConstraintSetDraw, test_bounded_constraint_set_draw);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
