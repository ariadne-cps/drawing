# Ariadne Drawing

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Unix Status](https://github.com/ariadne-cps/drawing/actions/workflows/unix.yml/badge.svg)](https://github.com/ariadne-cps/drawing/actions/workflows/unix.yml)
[![Windows Status](https://github.com/ariadne-cps/drawing/actions/workflows/win.yml/badge.svg)](https://github.com/ariadne-cps/drawing/actions/workflows/win.yml)
[![Coverage Status](https://github.com/ariadne-cps/drawing/actions/workflows/coverage.yml/badge.svg)](https://github.com/ariadne-cps/drawing/actions/workflows/coverage.yml)
[![codecov](https://codecov.io/gh/ariadne-cps/drawing/branch/main/graph/badge.svg)](https://codecov.io/gh/ariadne-cps/drawing)

Ariadne Drawing provides mathematical drawing adapters and drawing strategies that connect Ariadne's kernel geometry to the independent Rendering library. Drawing is distinct from rasterization: it converts mathematical sets into drawing operations and selects approximation strategies.

## Layout

Public headers live under `include/drawing`, implementations under `src`, C++ tests under `tests`, optional Python bindings and tests under `python`, design documentation under `doc`, and standalone examples under `tutorials`.

The umbrella header is `include/ariadne-drawing.hpp`.

## Dependencies

Drawing depends on:

- [ariadne-cps/kernel](https://github.com/ariadne-cps/kernel), as a Git submodule, for mathematical functions and geometric sets.
- [ariadne-cps/rendering](https://github.com/ariadne-cps/rendering), as a direct Git submodule, for `Figure`, `CanvasInterface` and the rendering backend.
- [ariadne-cps/configuration](https://github.com/ariadne-cps/configuration) for shared build configuration.

The intended graph is **drawing → kernel and rendering**. Kernel and rendering must build without drawing.

## Build

```bash
git clone --recurse-submodules https://github.com/ariadne-cps/drawing.git
cd drawing
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel --target everything
ctest --test-dir build --output-on-failure
```

## C++ tutorial

The C++ tutorial is an external consumer of an installed library. Build and install Drawing first, then configure the tutorial with `CMAKE_PREFIX_PATH` pointing to the install prefix:

```bash
cmake --install build --prefix "$PWD/install"
cmake -S tutorials/tutorial_drawing -B build-tutorial -DCMAKE_PREFIX_PATH="$PWD/install"
cmake --build build-tutorial --parallel
./build-tutorial/tutorial_drawing
```

## Python bindings

When a compatible Python development environment is available, the standalone build is intended to build `pyariadne` from the kernel and rendering bindings plus the drawing adapters. Python bindings are organized as a separate drawing layer, extending the classes registered by Rendering and Kernel. A standalone build produces the combined `pyariadne` module when Python development dependencies are available. The module is installed under the chosen CMake prefix (`lib/pythonX.Y/site-packages` on Unix and `Lib/site-packages` on Windows). CI runs the Python tutorial **after installation**, with `PYTHONPATH` pointing to that installed copy and a check that the module is not imported from the build tree.

## Extraction status

The drawing adapters live in this repository; Kernel and Rendering remain independent dependencies. CI verifies installed-library consumption through a separately configured C++ tutorial.

## Windows Python tutorial

Windows CI runs the Python tutorial after installing Drawing, using the
installed `Lib/site-packages` directory and the installed library
`bin` directory on `PATH`. This intentionally tests the conventional
installed import without a custom DLL-loading launcher. The INTERFACE
target `pyariadne-kernel` contributes its compiled objects to the
`pyariadne` extension; it does not produce a separate `.pyd` file.

## Contribution guidelines

Please contact the Ariadne maintainers for contributions.

## License

Ariadne Drawing is released under the GNU General Public License v3.0.
