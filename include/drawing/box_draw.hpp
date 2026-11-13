/***************************************************************************
 *            drawing/box_draw.hpp
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

/** @file drawing/box_draw.hpp
 *  @brief Conversion and rendering of geometric boxes.
 */

#ifndef ARIADNE_BOX_DRAW_HPP
#define ARIADNE_BOX_DRAW_HPP

#include "geometry/box.hpp"
#include "numeric/numeric.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

// Conversion from mathematical Box to primitive rendering coordinates.
inline RenderingBox to_rendering_box(const RenderingBox& box) { return box; }
template<class I>
inline RenderingBox to_rendering_box(const Box<I>& box) {
    /** @brief Perform the requested drawing operation. */
    ApproximateBoxType approximate_box(box);
    /** @brief Perform the requested drawing operation. */
    RenderingBox result(box.dimension());
    for (DimensionType i = 0; i != box.dimension(); ++i) {
        result[i] = RenderingInterval(numeric_cast<double>(approximate_box[i].lower_bound()),
                                      /** @brief Perform the requested drawing operation. */
                                      numeric_cast<double>(approximate_box[i].upper_bound()));
    }
    return result;
}
/** @brief Perform the requested drawing operation. */
inline RenderingBox to_rendering_box(const RealBox& box) {
    return to_rendering_box(ApproximateBoxType(box, dp));
}

/** @brief Draw the object on a canvas. */
Void draw(CanvasInterface&, const Projection2d&, const ApproximateBoxType&);

// Out-of-line, value-owning Figure adapters implemented in figure_draw.cpp.
/** @brief Draw the object on a canvas. */
Void draw(Figure&, const RealBox&);
/** @brief Draw the object on a canvas. */
Void draw(Figure&, const FloatDPApproximateBox&);

template<class I>
/** @brief Draw the object on a canvas. */
inline Void draw(CanvasInterface& canvas, const Projection2d& projection, const Box<I>& box) {
    /** @brief Draw the object on a canvas. */
    Ariadne::draw(canvas, projection, ApproximateBoxType(box));
}

template<>
inline Void draw<RealInterval>(CanvasInterface& canvas, const Projection2d& projection, const RealBox& box) {
    /** @brief Draw the object on a canvas. */
    Ariadne::draw(canvas, projection, ApproximateBoxType(box, dp));
}

//! Value-owning adapter for figures and renderers.
template<class I>
/** @brief BoxDrawable provides conversion and rendering of geometric boxes. */
class BoxDrawable final : public Drawable2dInterface {
  public:
    explicit BoxDrawable(const Box<I>& box) : _box(box) {}
    BoxDrawable<I>* clone() const override { return new BoxDrawable<I>(*this); }
    DimensionType dimension() const override { return _box.dimension(); }
    /** @brief Draw the object on a canvas. */
    Void draw(CanvasInterface& canvas, const Projection2d& projection) const override {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas, projection, _box);
    }

  private:
    Box<I> _box;
};

template<class I>
/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, const Box<I>& box) {
    /** @brief Draw the object on a canvas. */
    figure.draw(BoxDrawable<I>(box));
}

template<class I>
/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, const Box<I>& box) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure, box);
}

template<class I>
inline Figure& operator<<(Figure& figure, const Box<I>& box) {
    /** @brief Draw the object on a canvas. */
    draw(figure, box);
    return figure;
}

inline Void plot(const char* filename, const Projection2d& projection,
                 const ApproximateBoxType& bbox,
                 const List<Pair<Colour, const Drawable2dInterface&>>& sets) {
    /** @brief Perform the requested drawing operation. */
    plot(filename, projection, to_rendering_box(bbox), sets);
}

template<class... Sets>
inline Void plot(const char* filename, const Projection2d& projection,
                 const ApproximateBoxType& bbox, const Sets&... sets) {
    /** @brief Perform the requested drawing operation. */
    Figure figure(to_rendering_box(bbox), projection);
    /** @brief Draw the object on a canvas. */
    draw(figure, sets...);
    /** @brief Perform the requested drawing operation. */
    figure.write(filename);
}
template<class... Sets>
/** @brief Perform the requested drawing operation. */
inline Void plot(const char* filename, const ApproximateBoxType& bbox, const Sets&... sets) {
    /** @brief Perform the requested drawing operation. */
    plot(filename, Projection2d(2u, 0u, 1u), bbox, sets...);
}

} // namespace Ariadne

#endif // ARIADNE_BOX_DRAW_HPP
