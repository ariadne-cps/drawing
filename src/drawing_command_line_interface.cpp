/***************************************************************************
 *            drawing/drawing_command_line_interface.cpp
 *
 *  Copyright  2007-26  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne.
 *
 *  Ariadne is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "drawing/drawer.hpp"
#include "drawing/null_drawer.hpp"
#include "drawing/drawer_manager.hpp"
#include "rendering/rendering_manager.hpp"
#include "rendering/default_rendering.hpp"
#include "rendering/null_rendering.hpp"
#include "drawing/drawing_command_line_interface.hpp"

namespace Ariadne {

namespace {

ArgumentParser make_drawer_argument_parser() {
    return make_valued_argument_parser(
        "d",
        "drawer",
        "Choose the drawer as a <value> in [ box | grid@X | affine@X | none ] with X a non-negative integer, where none disables drawing (default: affine@0)",
        [](String const& value) -> VoidFunction {
            Drawer drawer=NullDrawer();

            if (value != "none") {
                if (value == "box") {
                    drawer=BoxDrawer();
                } else {
                    SizeType const at_pos=value.find('@',0);
                    if (at_pos == String::npos) {
                        throw std::runtime_error("invalid drawer");
                    }

                    Int const accuracy=std::stoi(value.substr(at_pos+1));
                    if (accuracy < 0) {
                        throw std::runtime_error("negative drawer accuracy");
                    }

                    String const drawer_name=value.substr(0,at_pos);
                    if (drawer_name == "grid") {
                        drawer=GridDrawer(static_cast<Nat>(accuracy));
                    } else if (drawer_name == "affine") {
                        drawer=AffineDrawer(static_cast<Nat>(accuracy));
                    } else {
                        throw std::runtime_error("invalid drawer");
                    }
                }
            }

            return [drawer] {
                DrawerManager::instance().set_drawer(drawer);
            };
        });
}

ArgumentParser make_rendering_argument_parser() {
    return make_valued_argument_parser(
        "g",
        "rendering",
        "Choose the rendering backend as a <value> in [ default | none ] (default: default)",
        [](String const& value) -> VoidFunction {
            if (value == "default") {
                return [] { RenderingManager::instance().set_backend(DefaultRenderingBackend()); };
            }
            if (value == "none") {
                return [] {
                    RenderingManager::instance().set_backend(
                        NullRenderingBackend());
                };
            }
            throw std::runtime_error("invalid rendering backend");
        });
}

} // namespace

DrawingCommandLineInterface::DrawingCommandLineInterface() {
    add(CommandLineContribution(
        "drawing",
        {
            make_drawer_argument_parser(),
            make_rendering_argument_parser()
        }));
}

} // namespace Ariadne
