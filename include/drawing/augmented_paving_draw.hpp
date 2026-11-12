/***************************************************************************
 *            drawing/augmented_paving_draw.hpp
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

/** @file drawing/augmented_paving_draw.hpp
 *  @brief Rendering adapters for augmented pavings.
 */

// Drawing adapter for augmented pavings (independent of the mathematical type).
#ifndef ARIADNE_DRAWING_AUGMENTED_PAVING_DRAW_HPP
#define ARIADNE_DRAWING_AUGMENTED_PAVING_DRAW_HPP

#include "paving/augmented_paving.hpp"
#include "drawing/binary_tree_paving_draw.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

// Render the auxiliary graph of a state paving.
/** @brief Draw the object on a canvas. */
inline Void draw(CanvasInterface& canvas, Projection2d const& projection, AugmentedPaving const& paving) {
    /** @brief Draw the object on a canvas. */
    Ariadne::draw(canvas,projection,paving.state_auxiliary_set());
}

// An independent copy is owned because Figure retains drawable clones.
/** @brief AugmentedPavingDrawable provides rendering adapters for augmented pavings. */
class AugmentedPavingDrawable final : public Drawable2dInterface {
  public:
    explicit AugmentedPavingDrawable(AugmentedPaving const& paving) : _paving(paving) { }
    AugmentedPavingDrawable* clone() const override { return new AugmentedPavingDrawable(*this); }
    /** @brief Return the number of dimensions. */
    DimensionType dimension() const override {
        return _paving.dimension()+_paving.auxiliary_mapping().result_size();
    }
    /** @brief Draw the object on a canvas. */
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        /** @brief Draw the object on a canvas. */
        Ariadne::draw(canvas,projection,_paving);
    }
  private:
    AugmentedPaving _paving;
};

/** @brief Draw the object on a canvas. */
inline Void draw_to_figure(Figure& figure, AugmentedPaving const& paving) {
    /** @brief Draw the object on a canvas. */
    figure.draw(AugmentedPavingDrawable(paving));
}
/** @brief Draw the object on a canvas. */
inline Void draw(Figure& figure, AugmentedPaving const& paving) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure,paving);
}
inline Figure& operator<<(Figure& figure, AugmentedPaving const& paving) {
    /** @brief Draw the object on a canvas. */
    draw_to_figure(figure,paving); return figure;
}

} // namespace Ariadne
#endif // ARIADNE_DRAWING_AUGMENTED_PAVING_DRAW_HPP
