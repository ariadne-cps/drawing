#!/usr/bin/env python3
"""Run the Drawing tutorial against an installed pyariadne on Windows.

Python >= 3.8 does not use PATH to resolve extension-module DLL dependencies.
Register the installed Ariadne and vcpkg runtime directories before importing.
"""

import argparse
from contextlib import ExitStack
import os
from pathlib import Path
import runpy
import sys


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--install-prefix", type=Path, required=True)
    parser.add_argument("--dependency-bin", type=Path, action="append", default=[])
    args = parser.parse_args()

    prefix = args.install_prefix.resolve(strict=True)
    site_packages = prefix / "Lib" / "site-packages"
    if not site_packages.is_dir():
        raise FileNotFoundError(f"Installed Python module directory missing: {site_packages}")

    # The installer output must be used, never the repository build directory.
    sys.path.insert(0, str(site_packages))
    with ExitStack() as dll_dirs:
        if sys.platform == "win32":
            for path in [prefix / "bin", *args.dependency_bin]:
                directory = path.resolve(strict=True)
                dll_dirs.enter_context(os.add_dll_directory(str(directory)))

        import pyariadne

        module_path = Path(pyariadne.__file__).resolve(strict=True)
        if not module_path.is_relative_to(site_packages.resolve()):
            raise AssertionError(f"Imported {module_path}, not installed module under {site_packages}")

        print(f"Running tutorial with installed pyariadne: {module_path}", flush=True)
        runpy.run_path(str(Path(__file__).with_name("tutorial_drawing.py")),
                       run_name="__main__")


if __name__ == "__main__":
    main()
