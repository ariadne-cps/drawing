/***************************************************************************
 *            src/drawer_manager.cpp
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

/** @file src/drawer_manager.cpp
 *  @brief Implement drawer manager.
 */

#include "drawing/drawer_manager.hpp"
#include "drawing/drawer.hpp"

namespace Ariadne {

DrawerManager::DrawerManager() : _drawer(AffineDrawer(0)) { }

DrawerManager& DrawerManager::instance() {
    static DrawerManager instance;
    return instance;
}

Drawer const& DrawerManager::drawer() const {
    return _drawer;
}

Void DrawerManager::set_drawer(Drawer const& drawer) {
    _drawer = drawer;
}

} // namespace Ariadne
