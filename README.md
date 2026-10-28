# Ariadne Drawing

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Unix Status](https://github.com/ariadne-cps/drawing/actions/workflows/unix.yml/badge.svg)](https://github.com/ariadne-cps/drawing/actions/workflows/unix.yml)
[![Windows Status](https://github.com/ariadne-cps/drawing/actions/workflows/win.yml/badge.svg)](https://github.com/ariadne-cps/drawing/actions/workflows/win.yml)
[![Sanitizers Status](https://github.com/ariadne-cps/drawing/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/ariadne-cps/drawing/actions/workflows/sanitizers.yml)
[![Coverage Status](https://github.com/ariadne-cps/drawing/actions/workflows/coverage.yml/badge.svg)](https://github.com/ariadne-cps/drawing/actions/workflows/coverage.yml)
[![codecov](https://codecov.io/gh/ariadne-cps/drawing/branch/main/graph/badge.svg)](https://codecov.io/gh/ariadne-cps/drawing)

Ariadne Drawing provides mathematical drawing adapters and drawing strategies that connect Ariadne's Paving and Set layers to the independent Rendering library. Drawing is distinct from rasterization: it converts mathematical sets into drawing operations and selects approximation strategies.

## Layout

Public headers live under `include/drawing`, implementations under `src`, C++ tests under `tests`, optional Python bindings and tests under `python`, design documentation under `doc`, and standalone examples under `tutorials`.

The umbrella header is `include/ariadne-drawing.hpp`.

## Dependencies

Drawing depends on:

- [ariadne-cps/paving](https://github.com/ariadne-cps/paving), as Git submodule `ss/pav`, providing sets, grids, pavings, functions and their lower dependencies.
- [ariadne-cps/rendering](https://github.com/ariadne-cps/rendering), as a direct Git submodule, for `Figure`, `CanvasInterface` and the rendering backend.
- [ariadne-cps/configuration](https://github.com/ariadne-cps/configuration) for shared build configuration.

The intended graph is **drawing → paving and rendering**. Paving and Rendering build independently of Drawing. Paving provides Set, BDD, and their transitive dependencies. Rendering and Paving pin the same Configuration commit; CMake checks cross-path commit consistency.

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

When a compatible Python development environment is available, the standalone build produces `pyariadne` from the transitive Paving and Set bindings plus the Rendering and Drawing bindings.

## Extraction status

The drawing adapters live in this standalone repository; Paving and Rendering remain independent submodules. CMake checks Configuration consistency in the Paving dependency chain and Python Common consistency across Paving and Rendering. Rendering now pins the same Configuration commit, and cross-chain Configuration and Utility equality are checked. Release CI verifies the installed Drawing library through a separately configured C++ tutorial.

## Windows Python tutorial

Windows Release CI installs Drawing, then runs `python/tutorials/tutorial_drawing.py` using the installed `Lib/site-packages` directory on `PYTHONPATH` and the installed `bin` directory on `PATH`. The `pyariadne-paving` INTERFACE target contributes objects to the combined `pyariadne` extension; it does not produce a separate `.pyd` file.

## Contribution guidelines

If you would like to contribute to Ariadne Drawing, please contact the developer:

- Luca Geretti <luca.geretti@univr.it>

## License

Ariadne Drawing is released under the GNU General Public License v3.0.
