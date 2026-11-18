/***************************************************************************
 *            src/affine_set_draw.cpp
 *
 *  Copyright  2009-20  Pieter Collins
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

/** @file src/affine_set_draw.cpp
 *  @brief Implement affine set draw.
 */

#include "drawing/geometry_draw.hpp"
#include "function/function.hpp"
#include "set/polytope.hpp"
#include "logging/logging.hpp"
#include "rendering/geometry2d.hpp"
#include "rendering/rendering_interface.hpp"

namespace Ariadne {

Void draw(CanvasInterface& canvas, const Projection2d& projection, const ValidatedAffineConstrainedImageSet& set) {
    LOGGING_SCOPE_CREATE;
    LOGGING_PRINTLN("set=" << set);
    LOGGING_PRINTLN("projection=" << projection);

    // A single definitely violated affine guard proves emptiness cheaply.
    // The full LP emptiness check is intentionally avoided for plotting large
    // families of enclosures (including the SPRE22 benchmark).
    for (const auto& constraint : set.constraint_models()) {
        const auto range = constraint.function().range();
        if (definitely(range.lower_bound() > constraint.upper_bound()) ||
            definitely(range.upper_bound() < constraint.lower_bound())) {
            LOGGING_PRINTLN("empty: inconsistent affine guard");
            return;
        }
    }

    // The certified outer projection does not traverse the potentially
    // cycling affine boundary. Geometry remains exact until this adapter
    // converts its vertices into display coordinates.
    const Polytope enclosure = outer_project2d(
        set, projection.x_coordinate(), projection.y_coordinate());
    LOGGING_PRINTLN("projection_vertices=" << enclosure.number_of_vertices());
    if (enclosure.empty()) return;

    List<Point2d> boundary;
    for (const auto& vertex : enclosure.vertices()) {
        boundary.push_back(Point2d(vertex[0].get_d(), vertex[1].get_d()));
    }
    LOGGING_PRINTLN("boundary=" << boundary);
    canvas.fill_boundary(boundary);
}

} // namespace Ariadne
