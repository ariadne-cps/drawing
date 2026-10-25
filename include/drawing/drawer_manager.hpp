/*
 * Ariadne - free software under the GNU General Public License version 3
 * or (at your option) any later version. No warranty.
 */
#ifndef ARIADNE_DRAWER_MANAGER_HPP
#define ARIADNE_DRAWER_MANAGER_HPP

#include "drawing/drawer_interface.hpp"

namespace Ariadne {

//! \brief Manage the rendering strategy for validated constrained image sets.
class DrawerManager {
  private:
    DrawerManager();
  public:
    DrawerManager(DrawerManager const&) = delete;
    Void operator=(DrawerManager const&) = delete;

    static DrawerManager& instance();
    Drawer const& drawer() const;
    Void set_drawer(Drawer const& drawer);

  private:
    Drawer _drawer;
};

} // namespace Ariadne

#endif // ARIADNE_DRAWER_MANAGER_HPP
