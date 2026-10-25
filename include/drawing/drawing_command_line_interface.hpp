/***************************************************************************
 *            drawing/drawing_command_line_interface.hpp
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

/*! \file drawing/drawing_command_line_interface.hpp
 *  \brief Drawing command-line composition.
 */

#ifndef ARIADNE_DRAWING_COMMAND_LINE_INTERFACE_HPP
#define ARIADNE_DRAWING_COMMAND_LINE_INTERFACE_HPP

#include "threading/threading_command_line_interface.hpp"

namespace Ariadne {

//! \brief Threading command-line interface extended with drawing options.
//! \details Inherits logging and concurrency options; adds drawer strategy
//! and rendering backend selection.
class DrawingCommandLineInterface : public ThreadingCommandLineInterface {
  public:
    DrawingCommandLineInterface();
};

} // namespace Ariadne

#endif // ARIADNE_DRAWING_COMMAND_LINE_INTERFACE_HPP
