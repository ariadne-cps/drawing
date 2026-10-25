/***************************************************************************
 *            drawing/drawer.cpp
 *
 *  Copyright  2011-20  Pieter Collins
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

#include "function/functional.hpp"
#include "drawing/drawer.hpp"
#include "drawing/geometry_draw.hpp"
#include "drawing/box_draw.hpp"
#include "drawing/grid_paving_draw.hpp"

#include "macro/general.hpp"
#include "geometry/function_set.hpp"
#include "geometry/affine_set.hpp"
#include "geometry/grid_paving.hpp"

#include "rendering/rendering_interface.hpp"

namespace Ariadne {

Void box_draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set);
Void affine_draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set, Nat splittings_remaining);

OutputStream& BoxDrawer::_write(OutputStream& os) const {
    return os << "BoxDrawer()"; }
OutputStream& AffineDrawer::_write(OutputStream& os) const {
    return os << "AffineDrawer(splittings=" << this->_splittings << ")"; }
OutputStream& GridDrawer::_write(OutputStream& os) const {
    return os << "GridDrawer(fineness=" << this->_fineness << ")"; }

Void BoxDrawer::draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set) const {
    box_draw(cnvs,proj,set);
}

Void AffineDrawer::draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set) const {
    affine_draw(cnvs,proj,set,this->_splittings);
}

Void GridDrawer::draw(CanvasInterface& canvas, const Projection2d& projection, const ValidatedConstrainedImageSet& set) const {
    Ariadne::draw(canvas,projection,set.outer_approximation(Grid(set.dimension()),this->_fineness));
}

Void box_draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set)
{
    Ariadne::draw(cnvs,proj,cast_exact_box(apply(set.function(),set.domain())));
}

Void affine_draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set, Nat splittings_remaining)
{
    if(splittings_remaining==0) {
        Ariadne::draw(cnvs,proj,set.affine_over_approximation());
    } else {
        Pair<ValidatedConstrainedImageSet,ValidatedConstrainedImageSet> split=set.split();
        affine_draw(cnvs,proj,split.first,splittings_remaining-1u);
        affine_draw(cnvs,proj,split.second,splittings_remaining-1u);
    }
}

} // namespace Ariadne


