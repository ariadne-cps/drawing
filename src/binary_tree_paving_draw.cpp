/***************************************************************************
 *            drawing/binary_tree_paving_draw.cpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/
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
