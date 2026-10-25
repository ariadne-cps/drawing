/***************************************************************************
 *            drawing/box_draw.cpp
 *
 *  Copyright  2013-20  Pieter Collins
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

/*! \file drawing/box_draw.cpp
 *  \brief
 */


#include "drawing/box_draw.hpp"
#include "rendering/rendering_interface.hpp"
#include "rendering/geometry2d.hpp"

namespace Ariadne {

Void draw(CanvasInterface& c, Projection2d const& p, ApproximateBoxType const& bx) {
    auto const& xl = numeric_cast<double>(bx[p.x_coordinate()].lower_bound());
    auto const& xu = numeric_cast<double>(bx[p.x_coordinate()].upper_bound());
    auto const& yl = numeric_cast<double>(bx[p.y_coordinate()].lower_bound());
    auto const& yu = numeric_cast<double>(bx[p.y_coordinate()].upper_bound());
    List<Point2d> boundary = {Point2d(xl,yl),Point2d(xu,yl),Point2d(xu,yu),Point2d(xl,yu)};
    c.fill_boundary(boundary);
}

} // namespace Ariadne
