/***************************************************************************
 *            drawing/list_set_draw.hpp
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

/** @file drawing/list_set_draw.hpp
 *  @brief Rendering adapters for lists of sets.
 */

#ifndef ARIADNE_LIST_SET_DRAW_HPP
#define ARIADNE_LIST_SET_DRAW_HPP

#include "set/list_set.hpp"
#include "drawing/box_draw.hpp"

namespace Ariadne {

template<class BS>
/** @brief Draw the object on a canvas. */
inline Void draw(CanvasInterface& canvas, Projection2d const& projection, ListSet<BS> const& set) {
    for(SizeType i=0; i!=set.size(); ++i) {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas,projection,set[i]);
    }
}

// A list is copied into the Figure so the caller can reuse or destroy it.
template<class BS>
/** @brief ListSetDrawable provides rendering adapters for lists of sets. */
class ListSetDrawable final : public Drawable2dInterface {
  public:
    explicit ListSetDrawable(ListSet<BS> const& set) : _set(set) { }
    ListSetDrawable* clone() const override { return new ListSetDrawable(*this); }
    DimensionType dimension() const override { return _set.dimension(); }
    /** @brief Draw the object on a canvas. */
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas,projection,_set);
    }
  private:
    ListSet<BS> _set;
};

template<class BS>
/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, ListSet<BS> const& set) {
    /** @brief Draw the object on a canvas. */
    figure.draw(ListSetDrawable<BS>(set));
}

template<class BS>
/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, ListSet<BS> const& set) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure,set);
}

} // namespace Ariadne

#endif // ARIADNE_LIST_SET_DRAW_HPP
