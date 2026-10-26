/***************************************************************************
 *            drawing/paving_draw.hpp
 *
 *  Copyright  2026  Luca Geretti
 ****************************************************************************/
/*
 *  This file is part of Ariadne, free software under the GNU General
 *  Public License version 3 or (at your option) any later version.
 */
#ifndef ARIADNE_PAVING_DRAW_HPP
#define ARIADNE_PAVING_DRAW_HPP

#include <memory>
#include "geometry/paving_interface.hpp"
#include "drawing/box_draw.hpp"

namespace Ariadne {

//! Draw the cells of a paving through its mathematical interface.
inline Void draw(CanvasInterface& canvas, Projection2d const& projection, SubPavingInterface const& paving) {
    for(auto iter=paving.begin(); iter!=paving.end(); ++iter) {
        Ariadne::draw(canvas,projection,iter->box());
    }
}

//! A value-owning rendering adapter; the paving can outlive its original handle.
class SubPavingDrawable final : public Drawable2dInterface {
  public:
    explicit SubPavingDrawable(SubPavingInterface const& paving) : _paving(paving.clone()) { }
    SubPavingDrawable(SubPavingDrawable const& other) : _paving(other._paving->clone()) { }
    SubPavingDrawable* clone() const override { return new SubPavingDrawable(*this); }
    DimensionType dimension() const override { return _paving->dimension(); }
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        Ariadne::draw(canvas,projection,*_paving);
    }
  private:
    std::unique_ptr<SubPavingInterface> _paving;
};

inline Void draw_to_figure(Figure& figure, SubPavingInterface const& paving) {
    figure.draw(SubPavingDrawable(paving));
}

inline Void draw(Figure& figure, SubPavingInterface const& paving) {
    draw_to_figure(figure,paving);
}
inline Figure& operator<<(Figure& figure, SubPavingInterface const& paving) {
    draw(figure,paving); return figure;
}

inline Void draw_to_figure(Figure& figure, PavingHandle const& paving) {
    draw_to_figure(figure,static_cast<PavingInterface const&>(paving));
}
inline Void draw(Figure& figure, PavingHandle const& paving) {
    draw_to_figure(figure,paving);
}
inline Figure& operator<<(Figure& figure, PavingHandle const& paving) {
    draw(figure,paving); return figure;
}
inline Void draw_to_figure(Figure& figure, SubPavingHandle const& paving) {
    draw_to_figure(figure,static_cast<SubPavingInterface const&>(paving));
}
inline Void draw(Figure& figure, SubPavingHandle const& paving) {
    draw_to_figure(figure,paving);
}
inline Figure& operator<<(Figure& figure, SubPavingHandle const& paving) {
    draw(figure,paving); return figure;
}

} // namespace Ariadne

#endif // ARIADNE_PAVING_DRAW_HPP
