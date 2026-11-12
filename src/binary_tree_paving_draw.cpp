/***************************************************************************
 *            src/binary_tree_paving_draw.cpp
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

/** @file src/binary_tree_paving_draw.cpp
 *  @brief Implement binary tree paving draw.
 */

#include "function/functional.hpp"
#include "drawing/binary_tree_paving_draw.hpp"

namespace Ariadne {

Void draw(CanvasInterface& theGraphic, const Projection2d& theProjection, BinaryTreeSubpaving const& paving) {
    for(BinaryTreeSubpaving::ConstIterator iter=paving.begin(); iter!=paving.end(); ++iter) {
        Ariadne::draw(theGraphic,theProjection,iter->box());
    }
}

Void draw(CanvasInterface& theGraphic, const Projection2d& theProjection, const GridCell& theGridCell) {
    Ariadne::draw(theGraphic,theProjection,theGridCell.box());
}

Void draw(CanvasInterface& theGraphic, const Projection2d& theProjection, const BinaryTreePaving& theBinaryTreePaving) {
    for(BinaryTreePaving::ConstIterator iter=theBinaryTreePaving.begin(); iter!=theBinaryTreePaving.end(); ++iter) {
        Ariadne::draw(theGraphic,theProjection,iter->box());
    }
}

Void draw(CanvasInterface& theGraphic, const Projection2d& theProjection, const EffectiveEuclideanCompactSetInterface& theSet) {
    static const Int DRAWING_DEPTH=16;
    draw(theGraphic,theProjection,outer_approximation(theSet,Grid(theSet.dimension()),DRAWING_DEPTH));
}

} // namespace Ariadne
