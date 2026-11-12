/***************************************************************************
 *            drawing/null_drawer.hpp
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

/** @file drawing/null_drawer.hpp
 *  @brief A drawer implementation that performs no rendering.
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
