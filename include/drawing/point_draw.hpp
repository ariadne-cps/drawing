/***************************************************************************
 *            drawing/point_draw.hpp
 *
 *  Copyright  2026  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne.
 *
 *  Ariadne is free software under the GNU General Public License,
 *  version 3 or (at your option) any later version.
 */

#ifndef ARIADNE_POINT_DRAW_HPP
#define ARIADNE_POINT_DRAW_HPP

#include "geometry/point.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

//! Draw a point on a canvas without coupling the mathematical Point to rendering.
template<class X>
inline Void draw(CanvasInterface& canvas, Projection2d const& projection, Point<X> const& point) {
    canvas.dot(numeric_cast<double>(point[projection.x_coordinate()]),
               numeric_cast<double>(point[projection.y_coordinate()]));
    canvas.stroke();
}

//! Drawable adapter owning a copy of the mathematical point.
template<class X>
class PointDrawable final : public Drawable2dInterface {
  public:
    explicit PointDrawable(Point<X> const& point) : _point(point) { }

    PointDrawable<X>* clone() const override { return new PointDrawable<X>(*this); }
    DimensionType dimension() const override { return _point.dimension(); }

    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        Ariadne::draw(canvas,projection,_point);
    }

  private:
    Point<X> _point;
};

//! The Figure clones its drawable, so the temporary adapter is safe.
template<class X>
inline Void draw(Figure& figure, Point<X> const& point) {
    figure.draw(PointDrawable<X>(point));
}

template<class X>
inline Figure& operator<<(Figure& figure, Point<X> const& point) {
    draw(figure,point);
    return figure;
}

//! Project a point using rendering's two-coordinate projection descriptor.
template<class X>
inline Point<X> project(Point<X> const& pt, Projection2d const& p) {
    ARIADNE_PRECONDITION(pt.dimension() == p.n);
    Vector<X> rv = pt.vector();
    rv.resize(2u);
    rv.set(0,pt.at(p.i));
    rv.set(1,pt.at(p.j));
    return Point<X>(rv);
}

} // namespace Ariadne

#endif // ARIADNE_POINT_DRAW_HPP
