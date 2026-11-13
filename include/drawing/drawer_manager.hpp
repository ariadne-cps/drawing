/***************************************************************************
 *            drawing/drawer_manager.hpp
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

/** @file drawing/drawer_manager.hpp
 *  @brief Selection and management of active drawers.
 */

#ifndef ARIADNE_DRAWER_MANAGER_HPP
#define ARIADNE_DRAWER_MANAGER_HPP

#include "drawing/drawer_interface.hpp"

namespace Ariadne {

//! \brief Manage the rendering strategy for validated constrained image sets.
class DrawerManager {
  private:
    /** @brief Construct the drawing object. */
    DrawerManager();

  public:
    /** @brief Construct the drawing object. */
    DrawerManager(const DrawerManager &) = delete;
    Void operator=(const DrawerManager &) = delete;

    /** @brief Get or set the selected drawing strategy. */
    static DrawerManager &instance();
    /** @brief Draw the object on a canvas. */
    const Drawer &drawer() const;
    /** @brief Get or set the selected drawing strategy. */
    Void set_drawer(const Drawer &drawer);

  private:
    Drawer _drawer;
};

} // namespace Ariadne

#endif // ARIADNE_DRAWER_MANAGER_HPP
