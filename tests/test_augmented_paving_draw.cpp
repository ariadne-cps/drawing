#include <type_traits>
#include "drawing/augmented_paving_draw.hpp"
#include "rendering/null_rendering.hpp"
#include "ariadne-testing.hpp"

using namespace Ariadne;
class AugmentedCanvas final : public NullCanvas {
  public:
    Nat boundaries=0u;
    Void fill_boundary(List<Point2d> const&) override { ++boundaries; }
};
class TestAugmentedDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;
    Void test_augmented_draw() {
        static_assert(!std::is_base_of_v<Drawable2dInterface,AugmentedPaving>);
        Grid grid(2u);
        EffectiveVectorMultivariateFunction f=EffectiveVectorMultivariateFunction::identity(2u);
        AugmentedPaving paving(grid,f);
        paving.adjoin_outer_approximation(ExactBoxType({{-1,1},{-1,1}}),2u);
        Projection2d projection(4u,0u,1u);
        AugmentedCanvas canvas;
        draw(canvas,projection,paving);
        ARIADNE_TESTING_PROVE(canvas.boundaries>0u);

        AugmentedPavingDrawable drawable(paving);
        ARIADNE_TESTING_EXPECT_EQUAL(drawable.dimension(),paving.dimension());
        auto copy=std::unique_ptr<Drawable2dInterface>(drawable.clone());
        copy->draw(canvas,projection);
        ARIADNE_TESTING_PROVE(canvas.boundaries>0u);

        Figure figure(ApproximateBoxType({{-2,+2},{-2,+2}}),projection);
        draw(figure,paving);
        figure << paving;
        figure._paint_all(canvas);
        ARIADNE_TESTING_PROVE(canvas.boundaries>0u);
    }
};
int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_augmented_paving_draw");
    ARIADNE_TESTING_ADD_TEST(TestAugmentedDraw,test_augmented_draw);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc,argv);
}
