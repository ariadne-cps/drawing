/***************************************************************************
 *            drawing/paving_draw.hpp
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

/** @file drawing/paving_draw.hpp
 *  @brief Rendering adapters for paving and subpaving objects.
 */

#ifndef ARIADNE_PAVING_DRAW_HPP
#define ARIADNE_PAVING_DRAW_HPP

#include <memory>

#include "drawing/box_draw.hpp"
#include "paving/paving_interface.hpp"

namespace Ariadne {

//! Draw the cells of a paving through its mathematical interface.
inline Void draw(CanvasInterface& canvas, const Projection2d& projection, const SubPavingInterface& paving) {
    for (auto iter = paving.begin(); iter != paving.end(); ++iter) {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas, projection, iter->box());
    }
}

//! A value-owning rendering adapter; the paving can outlive its original handle.
class SubPavingDrawable final : public Drawable2dInterface {
  public:
    explicit SubPavingDrawable(const SubPavingInterface& paving) : _paving(paving.clone()) {}
    SubPavingDrawable(const SubPavingDrawable& other) : _paving(other._paving->clone()) {}
    SubPavingDrawable* clone() const override { return new SubPavingDrawable(*this); }
    DimensionType dimension() const override { return _paving->dimension(); }
    /** @brief Draw the object on a canvas. */
    Void draw(CanvasInterface& canvas, const Projection2d& projection) const override {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas, projection, *_paving);
    }

  private:
    std::unique_ptr<SubPavingInterface> _paving;
};

/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, const SubPavingInterface& paving) {
    /** @brief Draw the object on a canvas. */
    figure.draw(SubPavingDrawable(paving));
}

/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, const SubPavingInterface& paving) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure, paving);
}
inline Figure& operator<<(Figure& figure, const SubPavingInterface& paving) {
    /** @brief Draw the object on a canvas. */
    draw(figure, paving);
    return figure;
}

/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, const Paving& paving) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure, static_cast<const PavingInterface&>(paving));
}
/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, const Paving& paving) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure, paving);
}
inline Figure& operator<<(Figure& figure, const Paving& paving) {
    /** @brief Draw the object on a canvas. */
    draw(figure, paving);
    return figure;
}
/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, const SubPaving& paving) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure, static_cast<const SubPavingInterface&>(paving));
}
/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, const SubPaving& paving) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure, paving);
}
inline Figure& operator<<(Figure& figure, const SubPaving& paving) {
    /** @brief Draw the object on a canvas. */
    draw(figure, paving);
    return figure;
}

} // namespace Ariadne

#endif // ARIADNE_PAVING_DRAW_HPP
