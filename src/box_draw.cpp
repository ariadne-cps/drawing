/***************************************************************************
 *            src/box_draw.cpp
 *
 *  Copyright  2013-20  Pieter Collins
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

/** @file src/box_draw.cpp
 *  @brief Implement box draw.
 */

#include "drawing/box_draw.hpp"

#include "rendering/geometry2d.hpp"
#include "rendering/rendering_interface.hpp"

namespace Ariadne {

Void draw(CanvasInterface& c, const Projection2d& p, const ApproximateBoxType& bx) {
    const auto& xl = numeric_cast<double>(bx[p.x_coordinate()].lower_bound());
    const auto& xu = numeric_cast<double>(bx[p.x_coordinate()].upper_bound());
    const auto& yl = numeric_cast<double>(bx[p.y_coordinate()].lower_bound());
    const auto& yu = numeric_cast<double>(bx[p.y_coordinate()].upper_bound());
    List<Point2d> boundary = {Point2d(xl, yl), Point2d(xu, yl), Point2d(xu, yu), Point2d(xl, yu)};
    c.fill_boundary(boundary);
}

} // namespace Ariadne
