/***************************************************************************
 *            drawing/affine_set_draw.cpp
 *
 *  Copyright  2009-20  Pieter Collins
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne.
 *
 *  Ariadne is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "function/function.hpp"
#include "drawing/geometry_draw.hpp"
#include "rendering/rendering_interface.hpp"
#include "rendering/geometry2d.hpp"
#include "logging/logging.hpp"

namespace Ariadne {

Void draw(CanvasInterface& canvas, Projection2d const& projection, ValidatedAffineConstrainedImageSet const& set) {
    LOGGING_SCOPE_CREATE;
    LOGGING_PRINTLN("set="<<set);
    LOGGING_PRINTLN("projection="<<projection);

    List<Point2d> boundary;

    for(auto const& xy:set.boundary(projection.x_coordinate(),projection.y_coordinate())) {
        boundary.push_back(Point2d(xy.first,xy.second));
    }
    LOGGING_PRINTLN("boundary="<<boundary);

    if(boundary.empty()) { return; }

    canvas.fill_boundary(boundary);
}

} // namespace Ariadne
