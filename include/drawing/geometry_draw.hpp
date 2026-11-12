/***************************************************************************
 *            drawing/geometry_draw.hpp
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

// Mathematical rendering adapters owned exclusively by Drawing.
/** @file drawing/geometry_draw.hpp
 *  @brief Value-owning drawing adapters for geometric sets.
 */

#ifndef ARIADNE_GEOMETRY_DRAW_HPP
#define ARIADNE_GEOMETRY_DRAW_HPP

// Load complete numeric and function types before affine_set.hpp.
#include "function/function.hpp"
#include "set/affine_set.hpp"
#include "set/function_set.hpp"
#include "set/curve.hpp"
// Figure constructors from mathematical boxes need the Drawing conversion adapter.
#include "drawing/box_draw.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, BoundedConstraintSet const&);
/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, ConstrainedImageSet const&);
/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, ValidatedConstrainedImageSet const&);
/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, ValidatedAffineConstrainedImageSet const&);
/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, Projection2d const&, InterpolatedCurve const&);

// A Figure owns clones of its drawables. The adapters must therefore own
// their mathematical values, rather than references to short-lived objects.
template<class Set>
/** @brief GeometryDrawable2d provides value-owning drawing adapters for geometric sets. */
class GeometryDrawable2d final : public Drawable2dInterface {
  public:
    explicit GeometryDrawable2d(Set const& set) : _set(set) { }
    GeometryDrawable2d* clone() const override { return new GeometryDrawable2d(*this); }
    DimensionType dimension() const override { return _set.dimension(); }
    /** @brief Draw the object on a canvas. */
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas,projection,_set);
    }
  private:
    Set _set;
};

#define ARIADNE_DRAWING_ADAPT(TYPE) \
    inline Void draw_to_figure(Figure& figure, TYPE const& set) { \
        figure.draw(GeometryDrawable2d<TYPE>(set)); \
    } \
    inline Void draw(Figure& figure, TYPE const& set) { \
        draw_to_figure(figure,set); \
    } \
    inline Figure& operator<<(Figure& figure, TYPE const& set) { \
        draw(figure,set); return figure; \
    }

ARIADNE_DRAWING_ADAPT(BoundedConstraintSet)
ARIADNE_DRAWING_ADAPT(ConstrainedImageSet)
ARIADNE_DRAWING_ADAPT(ValidatedConstrainedImageSet)
ARIADNE_DRAWING_ADAPT(ValidatedAffineConstrainedImageSet)
ARIADNE_DRAWING_ADAPT(InterpolatedCurve)

#undef ARIADNE_DRAWING_ADAPT

} // namespace Ariadne
#endif
