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

#include "geometry/function_set.hpp"
#include "geometry/box.hpp"
#include "drawing/drawer_manager.hpp"
#include "rendering/rendering_interface.hpp"

namespace Ariadne {

Void
BoundedConstraintSet::draw(CanvasInterface& c, const Projection2d& p) const
{
    return ConstrainedImageSet(*this).draw(c,p);
}

Void
ConstrainedImageSet::draw(CanvasInterface& cnvs, const Projection2d& proj) const
{
    // Preserve the exact-box conversion used by geometry/function_set.cpp.
    DoublePrecision precision;
    ExactBoxType domain=cast_exact_box(ApproximateBoxType(this->_domain,precision));
    ValidatedConstrainedImageSet(domain,this->_function,this->_constraints).draw(cnvs,proj);
}

Void
ValidatedConstrainedImageSet::draw(CanvasInterface& cnvs, const Projection2d& proj) const {
    DrawerManager::instance().drawer().draw(cnvs,proj,*this);
}

} // namespace Ariadne
