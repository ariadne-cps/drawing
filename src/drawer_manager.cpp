/*
 * Ariadne - free software under the GNU General Public License version 3
 * or (at your option) any later version. No warranty.
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
