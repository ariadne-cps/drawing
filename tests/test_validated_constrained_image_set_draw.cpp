/***************************************************************************
 * Figure and canvas dispatch for validated constrained image sets.
 ***************************************************************************/
#include "drawing/geometry_draw.hpp"
#include "drawing/drawer.hpp"
#include "drawing/drawer_manager.hpp"
#include "rendering/null_rendering.hpp"
#include "macro/testing.hpp"
using namespace Ariadne;

class ValidatedImageCanvas final : public NullCanvas {
  public:
    Nat boundaries=0u;
    Void fill_boundary(List<Point2d> const&) override { ++boundaries; }
};
Void test_validated_constrained_image_set_draw() {
    auto x=ValidatedScalarMultivariateFunction::coordinate(2u,0u);
    auto y=ValidatedScalarMultivariateFunction::coordinate(2u,1u);
    ValidatedVectorMultivariateFunction mapping({x+y,x-y});
    ValidatedConstrainedImageSet set(ExactBoxType{{-1.0_x,1.0_x},{-2.0_x,2.0_x}},mapping);
    Projection2d projection(2u,0u,1u);
    ValidatedImageCanvas canvas;

    DrawerManager::instance().set_drawer(BoxDrawer());
    draw(canvas,projection,set);
    ARIADNE_TEST_ASSERT(canvas.boundaries>0u);

    Figure figure(ApproximateBoxType({{-4,+4},{-4,+4}}),projection);
    draw(figure,set);
    figure._paint_all(canvas);
    ARIADNE_TEST_ASSERT(canvas.boundaries>1u);

    DrawerManager::instance().set_drawer(AffineDrawer(0u));
    draw(canvas,projection,set);
    ARIADNE_TEST_ASSERT(canvas.boundaries>2u);
}
Int main() {
    ARIADNE_TEST_CALL(test_validated_constrained_image_set_draw());
    return ARIADNE_TEST_FAILURES;
}
