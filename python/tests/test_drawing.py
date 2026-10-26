from pyariadne import *


def test_drawing_command_line():
    cli = DrawingCommandLineInterface()
    assert cli.acquire(["", "--concurrency", "0", "--verbosity", "2",
                        "--theme", "none", "--drawer", "none", "--rendering", "none"])
    assert not cli.acquire(["", "--drawer", "invalid"])

def test_drawing_bindings():
    import pyariadne
    for name in ("Drawer", "BoxDrawer", "AffineDrawer", "GridDrawer",
                 "DrawerManager", "DrawingCommandLineInterface", "Figure"):
        assert hasattr(pyariadne, name), name
    manager = DrawerManager.instance()
    manager.set_drawer(AffineDrawer(0))
    assert isinstance(manager.drawer(), Drawer)
    manager.set_drawer(BoxDrawer())
    assert isinstance(manager.drawer(), Drawer)


def test_tutorial_numeric_constructors():
    # exact() is bound to a double, while FloatDPApproximation also accepts
    # a decimal string. Both construction paths occur in the tutorials.
    precision = DoublePrecision()
    point = FloatDPPoint([
        FloatDP(exact(0.25), precision),
        FloatDP(exact(0.5), precision),
    ])
    curve_point = FloatDPApproximationPoint([
        FloatDPApproximation("-1", precision),
        FloatDPApproximation("0.75", precision),
    ])
    assert point.dimension() == 2
    assert curve_point.dimension() == 2
