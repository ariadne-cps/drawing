"""Smoke test for the standalone Drawing Python extension."""

import pyariadne_drawing as drawing


def test_drawing_smoke():
    cli = drawing.DrawingCommandLineInterface()
    assert cli.acquire(["", "--drawer", "box", "--rendering", "none"])

    manager = drawing.DrawerManager.instance()
    manager.set_drawer(drawing.BoxDrawer())
    assert isinstance(manager.drawer(), drawing.Drawer)
    drawing.AffineDrawer(0)
    drawing.Projection2d(2, 0, 1)
