/***************************************************************************
 *            drawing/function_set_draw.cpp
 *
 *  Copyright  2008-20  Pieter Collins
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
#include "geometry/box.hpp"
#include "drawing/drawer_manager.hpp"
#include "rendering/rendering_interface.hpp"

namespace Ariadne {

Void
draw(CanvasInterface& c, const Projection2d& p, BoundedConstraintSet const& set)
{
    draw(c,p,ConstrainedImageSet(set));
}

Void
draw(CanvasInterface& cnvs, const Projection2d& proj, ConstrainedImageSet const& set)
{
    // Preserve the exact-box conversion used by geometry/function_set.cpp.
    DoublePrecision precision;
    ExactBoxType domain=cast_exact_box(ApproximateBoxType(set.domain(),precision));
    draw(cnvs,proj,ValidatedConstrainedImageSet(domain,set.function(),set.constraints()));
}

Void
draw(CanvasInterface& cnvs, const Projection2d& proj, ValidatedConstrainedImageSet const& set) {
    DrawerManager::instance().drawer().draw(cnvs,proj,set);
}

} // namespace Ariadne
