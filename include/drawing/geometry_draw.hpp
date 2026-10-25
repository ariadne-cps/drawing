/***************************************************************************
 *            drawing/geometry_draw.hpp
 *  Mathematical rendering adapters owned exclusively by Drawing.
 ***************************************************************************/
#ifndef ARIADNE_GEOMETRY_DRAW_HPP
#define ARIADNE_GEOMETRY_DRAW_HPP

// Load complete numeric and function types before affine_set.hpp.
#include "function/function.hpp"
#include "geometry/affine_set.hpp"
#include "geometry/function_set.hpp"
#include "geometry/curve.hpp"
// Figure constructors from mathematical boxes need the Drawing conversion adapter.
#include "drawing/box_draw.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

Void draw(CanvasInterface&, Projection2d const&, BoundedConstraintSet const&);
Void draw(CanvasInterface&, Projection2d const&, ConstrainedImageSet const&);
Void draw(CanvasInterface&, Projection2d const&, ValidatedConstrainedImageSet const&);
Void draw(CanvasInterface&, Projection2d const&, ValidatedAffineConstrainedImageSet const&);
Void draw(CanvasInterface&, Projection2d const&, InterpolatedCurve const&);

// A Figure owns clones of its drawables. The adapters must therefore own
// their mathematical values, rather than references to short-lived objects.
template<class Set>
class GeometryDrawable2d final : public Drawable2dInterface {
  public:
    explicit GeometryDrawable2d(Set const& set) : _set(set) { }
    GeometryDrawable2d* clone() const override { return new GeometryDrawable2d(*this); }
    DimensionType dimension() const override { return _set.dimension(); }
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
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
