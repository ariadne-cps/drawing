/***************************************************************************
 *            drawing/point_draw.hpp
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

/** @file drawing/point_draw.hpp
 *  @brief Canvas rendering of mathematical points.
 */

#ifndef ARIADNE_POINT_DRAW_HPP
#define ARIADNE_POINT_DRAW_HPP

#include "geometry/point.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

//! Draw a point on a canvas without coupling the mathematical Point to rendering.
template<class X>
/** @brief Draw the object on a canvas. */
inline Void draw(CanvasInterface& canvas, const Projection2d& projection, const Point<X>& point) {
    canvas.dot(numeric_cast<double>(point[projection.x_coordinate()]),
               /** @brief Perform the requested drawing operation. */
               numeric_cast<double>(point[projection.y_coordinate()]));
    /** @brief Perform the requested drawing operation. */
    canvas.stroke();
}

//! Drawable adapter owning a copy of the mathematical point.
template<class X>
/** @brief PointDrawable provides canvas rendering of mathematical points. */
class PointDrawable final : public Drawable2dInterface {
  public:
    explicit PointDrawable(const Point<X>& point) : _point(point) {}

    PointDrawable<X>* clone() const override { return new PointDrawable<X>(*this); }
    DimensionType dimension() const override { return _point.dimension(); }

    /** @brief Draw the object on a canvas. */
    Void draw(CanvasInterface& canvas, const Projection2d& projection) const override {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas, projection, _point);
    }

  private:
    Point<X> _point;
};

//! The Figure clones its drawable, so the temporary adapter is safe.
template<class X>
/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, const Point<X>& point) {
    /** @brief Draw the object on a canvas. */
    figure.draw(PointDrawable<X>(point));
}

template<class X>
/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, const Point<X>& point) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure, point);
}

template<class X>
inline Figure& operator<<(Figure& figure, const Point<X>& point) {
    /** @brief Draw the object on a canvas. */
    draw(figure, point);
    return figure;
}

//! Project a point using rendering's two-coordinate projection descriptor.
template<class X>
/** @brief Perform the requested drawing operation. */
inline Point<X> project(const Point<X>& pt, const Projection2d& p) {
    /** @brief Construct the drawing object. */
    ARIADNE_PRECONDITION(pt.dimension() == p.n);
    /** @brief Perform the requested drawing operation. */
    Vector<X> rv = pt.vector();
    /** @brief Perform the requested drawing operation. */
    rv.resize(2u);
    /** @brief Perform the requested drawing operation. */
    rv.set(0, pt.at(p.i));
    /** @brief Perform the requested drawing operation. */
    rv.set(1, pt.at(p.j));
    return Point<X>(rv);
}

} // namespace Ariadne

#endif // ARIADNE_POINT_DRAW_HPP
