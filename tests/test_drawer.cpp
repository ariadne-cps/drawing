/***************************************************************************
 *            tests/test_drawer.cpp
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

/** @file tests/test_drawer.cpp
 *  @brief Test drawer behavior.
 */

#include <sstream>

#include "ariadne-testing.hpp"
#include "set/function_set.hpp"
#include "rendering/null_rendering.hpp"
#include "drawing/drawer.hpp"
#include "drawing/null_drawer.hpp"

using namespace Ariadne;

class TestDrawer : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    void test_concrete_drawers() {
        NullCanvas canvas;
        Projection2d projection(2,0,1);
        ValidatedConstrainedImageSet set(ExactBoxType::unit_box(2));

        BoxDrawer box_drawer;
        box_drawer.draw(canvas,projection,set);
        std::ostringstream box_stream;
        box_drawer._write(box_stream);
        ARIADNE_TESTING_EXPECT_EQUAL(box_stream.str(),"BoxDrawer()");

        AffineDrawer affine_drawer(1u);
        affine_drawer.draw(canvas,projection,set);
        std::ostringstream affine_stream;
        affine_drawer._write(affine_stream);
        ARIADNE_TESTING_EXPECT_EQUAL(affine_stream.str(),"AffineDrawer(splittings=1)");

        GridDrawer grid_drawer(1u);
        grid_drawer.draw(canvas,projection,set);
        std::ostringstream grid_stream;
        grid_drawer._write(grid_stream);
        ARIADNE_TESTING_EXPECT_EQUAL(grid_stream.str(),"GridDrawer(fineness=1)");
    }

    void test_drawer() {
        NullCanvas canvas;
        NullDrawer drawer;
        Projection2d projection(2, 0, 1);
        ValidatedConstrainedImageSet set(ExactBoxType::unit_box(2));

        drawer.draw(canvas, projection, set);

        std::ostringstream oss;
        drawer._write(oss);
        ARIADNE_TESTING_EXPECT_EQUAL(oss.str(), "NullDrawer()");

        Drawer handle = NullDrawer();
        std::ostringstream handle_oss;
        handle_oss << handle;
        ARIADNE_TESTING_EXPECT_EQUAL(handle_oss.str(), "NullDrawer()");
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_drawer");
    ARIADNE_TESTING_ADD_TEST(TestDrawer, test_drawer);
    ARIADNE_TESTING_ADD_TEST(TestDrawer, test_concrete_drawers);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
