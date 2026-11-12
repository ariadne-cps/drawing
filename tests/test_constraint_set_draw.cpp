/***************************************************************************
 *            tests/test_constraint_set_draw.cpp
 *
 *  Copyright  2026  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne Drawing.
 *
 *  Ariadne Drawing is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne Drawing is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne Drawing. If not, see <https://www.gnu.org/licenses/>.
 */

/** @file tests/test_constraint_set_draw.cpp
 *  @brief Test constraint set draw behavior.
 */

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
