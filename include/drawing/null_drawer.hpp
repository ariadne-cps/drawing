/*
 * Ariadne - free software under the GNU General Public License version 3
 * or (at your option) any later version. No warranty.
 */
#ifndef ARIADNE_NULL_DRAWER_HPP
#define ARIADNE_NULL_DRAWER_HPP

#include <ostream>
#include "drawing/drawer_interface.hpp"

namespace Ariadne {

//! \brief No-op drawer for validated constrained image sets.
class NullDrawer : public DrawerInterface {
  public:
    Void draw(CanvasInterface&, const Projection2d&, const ValidatedConstrainedImageSet&) const override { }
    OutputStream& _write(OutputStream& os) const override { return os << "NullDrawer()"; }
};

} // namespace Ariadne

#endif // ARIADNE_NULL_DRAWER_HPP
