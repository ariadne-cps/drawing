#!/usr/bin/env python3
"""Verify the common C++/Python Drawing tutorial PNG output contract."""
from pathlib import Path

NAMES = (
    "boxes",
    "projection_xy",
    "projection_xz",
    "drawer_box",
    "drawer_affine",
    "drawer_grid",
    "points",
    "curve",
    "list",
    "cell",
    "paving",
    "bounded",
    "effective",
    "validated",
    "affine_set",
)
SIGNATURE = bytes.fromhex("89504e470d0a1a0a")


def main():
    for name in NAMES:
        path = Path(f"tutorial_drawing_{name}.png")
        assert path.is_file(), f"Missing tutorial image: {path}"
        with path.open("rb") as file:
            assert file.read(8) == SIGNATURE, f"Invalid PNG signature: {path}"
        assert path.stat().st_size > 8, f"Empty PNG payload: {path}"
    print(f"Verified {len(NAMES)} Drawing tutorial PNGs")


if __name__ == "__main__":
    main()
