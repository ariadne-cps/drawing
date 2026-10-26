/***************************************************************************
 *            drawing/list_set_draw.hpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/
/*
 *  This file is part of Ariadne, free software under the GNU General
 *  Public License version 3 or (at your option) any later version.
 */
#ifndef ARIADNE_LIST_SET_DRAW_HPP
#define ARIADNE_LIST_SET_DRAW_HPP

#include "geometry/list_set.hpp"
#include "drawing/box_draw.hpp"

namespace Ariadne {

template<class BS>
inline Void draw(CanvasInterface& canvas, Projection2d const& projection, ListSet<BS> const& set) {
    for(SizeType i=0; i!=set.size(); ++i) {
        Ariadne::draw(canvas,projection,set[i]);
    }
}

// A list is copied into the Figure so the caller can reuse or destroy it.
template<class BS>
class ListSetDrawable final : public Drawable2dInterface {
  public:
    explicit ListSetDrawable(ListSet<BS> const& set) : _set(set) { }
    ListSetDrawable* clone() const override { return new ListSetDrawable(*this); }
    DimensionType dimension() const override { return _set.dimension(); }
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        Ariadne::draw(canvas,projection,_set);
    }
  private:
    ListSet<BS> _set;
};

template<class BS>
inline Void draw_to_figure(Figure& figure, ListSet<BS> const& set) {
    figure.draw(ListSetDrawable<BS>(set));
}

template<class BS>
inline Void draw(Figure& figure, ListSet<BS> const& set) {
    draw_to_figure(figure,set);
}

} // namespace Ariadne

#endif // ARIADNE_LIST_SET_DRAW_HPP
