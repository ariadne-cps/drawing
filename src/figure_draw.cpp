/***************************************************************************
 *            drawing/figure_draw.cpp
 *
 *  Copyright  2008-21  Pieter Collins, Mirko Albanese, Luca Geretti
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

#include "drawing/box_draw.hpp"
#include "rendering/figure.hpp"
#include "numeric/numeric.hpp"

namespace Ariadne {

Void draw(Figure& fig, const RealBox& box) {
    draw_to_figure(fig,box);
}

Void draw(Figure& fig, FloatDPApproximateBox const& box) {
    draw_to_figure(fig,box);
}

} // namespace Ariadne
