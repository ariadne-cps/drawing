/***************************************************************************
 *            drawing/curve_draw.cpp
 *
 *  Copyright  2007-20  Pieter Collins
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

#include "drawing/geometry_draw.hpp"
#include "geometry/point.hpp"
#include "algebra/vector.hpp"
#include "numeric/numeric.hpp"
#include "rendering/rendering_interface.hpp"

namespace Ariadne {


Void draw(CanvasInterface& c, Projection2d const& p, InterpolatedCurve const& curve)
{
    DimensionType xi=p.x_coordinate(); DimensionType yi=p.y_coordinate();
    ConstIterator iter=curve.begin();
    auto pt=join(iter->second,iter->first);
    c.move_to(numeric_cast<double>(pt[xi]),numeric_cast<double>(pt[yi]));
    while(iter!=curve.end()) {
        ++iter;
        pt=join(iter->second,iter->first);
        c.line_to(numeric_cast<double>(pt[xi]),numeric_cast<double>(pt[yi]));
    }
    if( decide(this->begin()->second==(this->end())->second) ) {
        c.fill();
    } else {
        c.stroke();
    }
}

} // namespace Ariadne
