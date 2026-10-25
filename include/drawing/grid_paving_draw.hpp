/***************************************************************************
 *            drawing/grid_paving_draw.hpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/
/*
 *  This file is part of Ariadne, free software under the GNU General
 *  Public License version 3 or (at your option) any later version.
 */
#ifndef ARIADNE_GRID_PAVING_DRAW_HPP
#define ARIADNE_GRID_PAVING_DRAW_HPP

#include "drawing/paving_draw.hpp"
#include "geometry/grid_paving.hpp"

namespace Ariadne {

Void draw(CanvasInterface&, Projection2d const&, GridTreeSubpaving const&);
Void draw(CanvasInterface&, Projection2d const&, GridCell const&);
Void draw(CanvasInterface&, Projection2d const&, GridTreePaving const&);
Void draw(CanvasInterface&, Projection2d const&, EffectiveEuclideanCompactSetInterface const&);

} // namespace Ariadne

#endif // ARIADNE_GRID_PAVING_DRAW_HPP
