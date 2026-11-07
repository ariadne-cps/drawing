/***************************************************************************
 *            drawing/binary_tree_paving_draw.hpp
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
#include "paving/binary_tree_paving.hpp"

namespace Ariadne {

Void draw(CanvasInterface&, Projection2d const&, BinaryTreeSubpaving const&);
Void draw(CanvasInterface&, Projection2d const&, GridCell const&);
Void draw(CanvasInterface&, Projection2d const&, BinaryTreePaving const&);
Void draw(CanvasInterface&, Projection2d const&, EffectiveEuclideanCompactSetInterface const&);

// The Figure clones the adapter; it must not retain a borrowed grid cell.
class GridCellDrawable final : public Drawable2dInterface {
  public:
    explicit GridCellDrawable(GridCell const& cell) : _cell(cell) { }
    GridCellDrawable* clone() const override { return new GridCellDrawable(*this); }
    DimensionType dimension() const override { return _cell.dimension(); }
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        Ariadne::draw(canvas,projection,_cell);
    }
  private:
    GridCell _cell;
};

inline Void draw_to_figure(Figure& figure, GridCell const& cell) {
    figure.draw(GridCellDrawable(cell));
}

inline Void draw(Figure& figure, GridCell const& cell) {
    draw_to_figure(figure,cell);
}
inline Figure& operator<<(Figure& figure, GridCell const& cell) {
    draw(figure,cell); return figure;
}

} // namespace Ariadne

#endif // ARIADNE_GRID_PAVING_DRAW_HPP
