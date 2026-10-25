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

} // namespace Ariadne

#endif // ARIADNE_LIST_SET_DRAW_HPP
