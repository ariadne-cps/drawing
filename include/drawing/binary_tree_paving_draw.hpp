/***************************************************************************
 *            drawing/binary_tree_paving_draw.hpp
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

/** @file drawing/binary_tree_paving_draw.hpp
 *  @brief Rendering of binary-tree pavings and grid cells.
 */

#ifndef ARIADNE_GRID_PAVING_DRAW_HPP
#define ARIADNE_GRID_PAVING_DRAW_HPP

#include "drawing/paving_draw.hpp"
#include "paving/binary_tree_paving.hpp"

namespace Ariadne {

/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, BinaryTreeSubpaving const&);
/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, GridCell const&);
/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, BinaryTreePaving const&);
/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, EffectiveEuclideanCompactSetInterface const&);

// The Figure clones the adapter; it must not retain a borrowed grid cell.
/** @brief GridCellDrawable provides rendering of binary-tree pavings and grid cells. */
class GridCellDrawable final : public Drawable2dInterface {
  public:
    explicit GridCellDrawable(GridCell const& cell) : _cell(cell) { }
    GridCellDrawable* clone() const override { return new GridCellDrawable(*this); }
    DimensionType dimension() const override { return _cell.dimension(); }
    /** @brief Draw the object on a canvas. */
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas,projection,_cell);
    }
  private:
    GridCell _cell;
};

/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, GridCell const& cell) {
    /** @brief Draw the object on a canvas. */
    figure.draw(GridCellDrawable(cell));
}

/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, GridCell const& cell) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure,cell);
}
inline Figure& operator<<(Figure& figure, GridCell const& cell) {
    /** @brief Draw the object on a canvas. */
    draw(figure,cell); return figure;
}

} // namespace Ariadne

#endif // ARIADNE_GRID_PAVING_DRAW_HPP
