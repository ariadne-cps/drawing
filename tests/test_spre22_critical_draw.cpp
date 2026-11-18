/***************************************************************************
 *            tests/test_spre22_critical_draw.cpp
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

/** @file tests/test_spre22_critical_draw.cpp
 *  @brief End-to-end rendering regression for the original stalled SPRE22 input 11591.
 */

#include <cmath>

#include "ariadne-testing.hpp"
#include "drawing/geometry_draw.hpp"
#include "logging/test_runner.hpp"
#include "rendering/geometry2d.hpp"
#include "rendering/null_rendering.hpp"

// Set's immutable, bit-exact test fixture is pinned transitively through
// Drawing -> Paving -> Set. Only this integration test uses Set's test data.
#include "../ss/pav/ss/set/tests/fixtures/spre22_critical_11591.hpp"
#include "../ss/pav/ss/set/tests/fixtures/spre22_snapshot_reader.hpp"

using namespace Ariadne;

namespace {

class RecordingAffineCanvas final : public NullCanvas {
  public:
    SizeType calls = 0u;
    SizeType vertices = 0u;
    bool finite = true;

    Void fill_boundary(const List<Point2d>& boundary) override {
        ++calls;
        vertices = boundary.size();
        for (const auto& point : boundary) {
            if (!std::isfinite(point.x) || !std::isfinite(point.y))
                finite = false;
        }
    }
};

} // namespace

class TestSPRE22CriticalDraw : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_11591_draw_terminates() {
        const auto captured = SPRE22Fixture::decode_critical_11591(
            SPRE22Fixture::encoded_record_11591);
        ARIADNE_TESTING_EXPECT_EQUAL(captured.set.dimension(), 9u);
        ARIADNE_TESTING_EXPECT_EQUAL(captured.set.number_of_parameters(), 26u);
        ARIADNE_TESTING_EXPECT_EQUAL(captured.set.number_of_constraints(), 4u);

        const auto affine = captured.set.affine_over_approximation();
        RecordingAffineCanvas canvas;
        draw(canvas, Projection2d(affine.dimension(), captured.x, captured.y), affine);

        ARIADNE_TESTING_EXPECT_EQUAL(canvas.calls, 1u);
        ARIADNE_TESTING_PROVE(canvas.vertices >= 3u);
        ARIADNE_TESTING_PROVE(canvas.finite);
        ARIADNE_TESTING_NOTE("SPRE22 original index 11591: drawing completed with "
                             << canvas.vertices << " outer polygon vertices");
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_spre22_critical_draw");
    ARIADNE_TESTING_ADD_TEST(TestSPRE22CriticalDraw, test_11591_draw_terminates);
    return Ariadne::Testing::run_logging_suite(ariadne_test_suite, argc, argv);
}
