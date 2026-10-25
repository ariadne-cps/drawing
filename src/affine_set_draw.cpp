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
#include "geometry/affine_set.hpp"
#include "rendering/rendering_interface.hpp"
#include "rendering/geometry2d.hpp"
#include "logging/logging.hpp"

namespace Ariadne {

Void ValidatedAffineConstrainedImageSet::draw(CanvasInterface& canvas, const Projection2d& projection) const {
    LOGGING_SCOPE_CREATE;
    LOGGING_PRINTLN("set="<<*this);
    LOGGING_PRINTLN("projection="<<projection);

    List<Point2d> boundary;

    boundary=this->boundary(projection.x_coordinate(),projection.y_coordinate());
    LOGGING_PRINTLN("boundary="<<boundary);

    if(boundary.empty()) { return; }

    canvas.fill_boundary(boundary);
}

} // namespace Ariadne
