// Drawing adapter for augmented pavings (independent of the mathematical type).
#ifndef ARIADNE_DRAWING_AUGMENTED_PAVING_DRAW_HPP
#define ARIADNE_DRAWING_AUGMENTED_PAVING_DRAW_HPP

#include "paving/augmented_paving.hpp"
#include "drawing/binary_tree_paving_draw.hpp"
#include "rendering/figure.hpp"

namespace Ariadne {

// Render the auxiliary graph of a state paving.
inline Void draw(CanvasInterface& canvas, Projection2d const& projection, AugmentedPaving const& paving) {
    Ariadne::draw(canvas,projection,paving.state_auxiliary_set());
}

// An independent copy is owned because Figure retains drawable clones.
class AugmentedPavingDrawable final : public Drawable2dInterface {
  public:
    explicit AugmentedPavingDrawable(AugmentedPaving const& paving) : _paving(paving) { }
    AugmentedPavingDrawable* clone() const override { return new AugmentedPavingDrawable(*this); }
    DimensionType dimension() const override {
        return _paving.dimension()+_paving.auxiliary_mapping().result_size();
    }
    Void draw(CanvasInterface& canvas, Projection2d const& projection) const override {
        Ariadne::draw(canvas,projection,_paving);
    }
  private:
    AugmentedPaving _paving;
};

inline Void draw_to_figure(Figure& figure, AugmentedPaving const& paving) {
    figure.draw(AugmentedPavingDrawable(paving));
}
inline Void draw(Figure& figure, AugmentedPaving const& paving) {
    draw_to_figure(figure,paving);
}
inline Figure& operator<<(Figure& figure, AugmentedPaving const& paving) {
    draw_to_figure(figure,paving); return figure;
}

} // namespace Ariadne
#endif // ARIADNE_DRAWING_AUGMENTED_PAVING_DRAW_HPP
