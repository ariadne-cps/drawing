/***************************************************************************
 *            drawing/drawer_interface.hpp
 *
 *  Copyright  2011-20  Pieter Collins
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

/** @file drawing/drawer_interface.hpp
 *  @brief Abstract interface for geometric drawers.
 */

#ifndef ARIADNE_DRAWER_INTERFACE_HPP
#define ARIADNE_DRAWER_INTERFACE_HPP

#include <iosfwd>

#include "utility/handle.hpp"
#include "utility/writable.hpp"

namespace Ariadne {

typedef Void Void;
/** @brief CanvasInterface provides abstract interface for geometric drawers. */
class CanvasInterface;
/** @brief Projection2d provides abstract interface for geometric drawers. */
struct Projection2d;
typedef Projection2d Projection2d;
/** @brief ValidatedConstrainedImageSet provides abstract interface for geometric drawers. */
class ValidatedConstrainedImageSet;

//! \brief A class for computing outer approximations to sets defined by functions.
class DrawerInterface : public WritableInterface {
  public:
    /** @brief Draw the object on a canvas. */
    virtual Void draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set) const = 0;
};

//! \brief A class for computing outer approximations to sets defined by functions.
class Drawer
    : public Handle<const DrawerInterface> {
  public:
    using Handle<const DrawerInterface>::Handle;
    /** @brief Draw the object on a canvas. */
    inline Void draw(CanvasInterface& cnvs, const Projection2d& proj, const ValidatedConstrainedImageSet& set) const {
        return this->_ptr->draw(cnvs, proj, set);
    }
    friend inline OutputStream& operator<<(OutputStream& os, const Drawer& drw) {
        return drw._ptr->_write(os);
    }
};

} // namespace Ariadne

#endif /* ARIADNE_DRAWER_INTERFACE_HPP */
