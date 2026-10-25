/***************************************************************************
 *            drawing/box_draw.hpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/
/*
 *  This file is part of Ariadne, free software under the GNU General
 *  Public License version 3 or (at your option) any later version.
 */
#ifndef ARIADNE_BOX_DRAW_HPP
#define ARIADNE_BOX_DRAW_HPP

#include "geometry/box.hpp"
#include "numeric/numeric.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

// Conversion from mathematical Box to primitive rendering coordinates.
inline RenderingBox to_rendering_box(RenderingBox const& box) { return box; }
template<class I> inline RenderingBox to_rendering_box(Box<I> const& box) {
    ApproximateBoxType approximate_box(box);
    RenderingBox result(box.dimension());
    for(DimensionType i=0; i!=box.dimension(); ++i) {
        result[i]=RenderingInterval(numeric_cast<double>(approximate_box[i].lower_bound()),
                                     numeric_cast<double>(approximate_box[i].upper_bound()));
    }
    return result;
}
inline RenderingBox to_rendering_box(RealBox const& box) {
    return to_rendering_box(ApproximateBoxType(box,dp));
}


Void draw(CanvasInterface&, Projection2d const&, ApproximateBoxType const&);

template<class I>
inline Void draw(CanvasInterface& canvas, Projection2d const& projection, Box<I> const& box) {
    Ariadne::draw(canvas,projection,ApproximateBoxType(box));
}

template<>
inline Void draw<RealInterval>(CanvasInterface& canvas, Projection2d const& projection, RealBox const& box) {
    Ariadne::draw(canvas,projection,ApproximateBoxType(box,dp));
}

//! Value-owning adapter for figures and renderers.
template<class I>
class BoxDrawable final : public Drawable2dInterface {
  public:
    explicit BoxDrawable(Box<I> const& box) : _box(box) { }
    BoxDrawable<I>* clone() const override { return new BoxDrawable<I>(*this); }
    DimensionType dimension() const override { return _box.dimension(); }
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        Ariadne::draw(canvas,projection,_box);
    }
  private:
    Box<I> _box;
};

template<class I>
inline Void draw_to_figure(Figure& figure, Box<I> const& box) {
    figure.draw(BoxDrawable<I>(box));
}

template<class I>
inline Void draw(Figure& figure, Box<I> const& box) {
    draw_to_figure(figure,box);
}

template<class I>
inline Figure& operator<<(Figure& figure, Box<I> const& box) {
    draw(figure,box);
    return figure;
}

inline Void plot(const char* filename, Projection2d const& projection,
                 ApproximateBoxType const& bbox,
                 List<Pair<Colour,Drawable2dInterface const&>> const& sets) {
    plot(filename,projection,to_rendering_box(bbox),sets);
}

template<class... Sets>
inline Void plot(const char* filename, Projection2d const& projection,
                 ApproximateBoxType const& bbox, Sets const&... sets) {
    Figure figure(to_rendering_box(bbox),projection);
    draw(figure,sets...);
    figure.write(filename);
}
template<class... Sets>
inline Void plot(const char* filename, ApproximateBoxType const& bbox, Sets const&... sets) {
    plot(filename,Projection2d(2u,0u,1u),bbox,sets...);
}

} // namespace Ariadne

#endif // ARIADNE_BOX_DRAW_HPP
