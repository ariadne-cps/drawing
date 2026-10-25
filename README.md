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
- [ariadne-cps/rendering](https://github.com/ariadne-cps/rendering), provided by the kernel dependency tree, for `Figure`, `CanvasInterface` and the rendering backend.
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

## Python bindings

When a compatible Python development environment is available, the standalone build is intended to build `pyariadne` from the kernel and rendering bindings plus the drawing adapters. Python bindings are organized as a separate drawing layer, extending the classes registered by Rendering and Kernel. A standalone build produces the combined `pyariadne` module when Python development dependencies are available.

## Extraction status

**Work in progress.** This branch imports the original drawing module, but its currently pinned kernel commit still builds the drawing implementations into `ariadne-kernel`. The remaining work is to remove the mathematical classes' `Drawable2dInterface` inheritance, move the drawing-only tests and Python registrations, and validate independent linking and installation. Do not merge or release this branch until the Unix, Windows and Coverage checks and standalone consumer tests pass.

## Contribution guidelines

Please contact the Ariadne maintainers for contributions.

## License

Ariadne Drawing is released under the GNU General Public License v3.0.
