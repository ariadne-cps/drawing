from pyariadne_drawing import *


def test_drawing_command_line():
    cli = DrawingCommandLineInterface()
    assert cli.acquire(["", "--concurrency", "0", "--verbosity", "2",
                        "--theme", "none", "--drawer", "none", "--rendering", "none"])
    assert not cli.acquire(["", "--drawer", "invalid"])

def test_drawing_bindings():
    import pyariadne_drawing
    for name in ("Drawer", "BoxDrawer", "AffineDrawer", "GridDrawer",
                 "DrawerManager", "DrawingCommandLineInterface", "Figure"):
        assert hasattr(pyariadne_drawing, name), name
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


def test_drawing_single_box_constructors():
    # The same RealBox-based constructors are used by the C++ tutorial.
    domain = RealBox([
        RealInterval(Real(Decimal("-1")), Real(Decimal("1"))),
        RealInterval(Real(Decimal("-1")), Real(Decimal("1"))),
    ])
    assert BoundedConstraintSet(domain).dimension() == 2
    assert ConstrainedImageSet(domain).dimension() == 2

def test_exact_box_list_set_uses_existing_set_binding():
    # Drawing must not register ListSet<ExactBoxType> twice.
    import pyariadne_drawing
    assert pyariadne_drawing.ExactBoxListSet is pyariadne_drawing.ListSetFloatDPExactBox
    boxes = pyariadne_drawing.ExactBoxListSet(2)
    assert boxes.size() == 0
    boxes.adjoin(pyariadne_drawing.FloatDPExactBox([
        {pyariadne_drawing.exact(-1): pyariadne_drawing.exact(1)},
        {pyariadne_drawing.exact(-1): pyariadne_drawing.exact(1)},
    ]))
    assert boxes.size() == 1
    assert boxes.dimension() == 2
