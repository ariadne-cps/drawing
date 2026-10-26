#!/usr/bin/python3

from pyariadne import *


def section(title):
    print(f"\n== {title} ==")


def show(label, value):
    print(f"{label}: {value}")


def real_box(bounds):
    # Construct Real values from decimal literals, never through FloatDP.
    # This follows the non-deprecated Real(Decimal) construction path.
    return RealBox([
        RealInterval(Real(Decimal(lower)), Real(Decimal(upper)))
        for lower, upper in bounds
    ])


def make_demo_set():
    u0 = EffectiveScalarMultivariateFunction.coordinate(3, 0)
    u1 = EffectiveScalarMultivariateFunction.coordinate(3, 1)
    u2 = EffectiveScalarMultivariateFunction.coordinate(3, 2)

    # Mathematical constants are represented exactly as rationals and then
    # lifted to EffectiveNumber.  Python float is intentionally avoided.
    five_quarters = EffectiveNumber(Rational("5/4"))
    seven_twentieths = EffectiveNumber(Rational("7/20"))
    one_fifth = EffectiveNumber(Rational("1/5"))
    three_tenths = EffectiveNumber(Rational("3/10"))

    mapping = EffectiveVectorMultivariateFunction([
        u0 * five_quarters + u2 * seven_twentieths,
        u1 + (u0 * u0) * one_fifth,
        u2 - u0 * three_tenths,
    ])
    domain = FloatDPExactBox([
        {exact(-1): exact(1)},
        {exact(-1): exact(1)},
        {exact(-1): exact(1)},
    ])
    return ValidatedConstrainedImageSet(domain, mapping)


def tutorial_rendering():
    section("Rendering backend and drawer policy")

    manager = RenderingManager.instance()
    drawer_manager = DrawerManager.instance()
    manager.set_backend(DefaultRenderingBackend())
    drawer_manager.set_drawer(AffineDrawer(1))
    show("current drawer", drawer_manager.drawer())

    section("Colours and reusable rendering properties")

    custom_blue = Colour(0.15, 0.35, 0.80, 0.60)
    style = RenderingProperties()
    style.set_line_width(2.0)
    style.set_line_colour(black)
    style.set_fill_colour(custom_blue)
    style.set_fill_opacity(0.60)

    show("custom colour", custom_blue)
    show("rendering properties", style)

    section("Layering a two-dimensional figure")

    viewport = FloatDPExactBox([
        {exact(-2.5): exact(2.5)},
        {exact(-2.0): exact(2.0)},
    ])
    figure = Figure(viewport, Projection2d(2, 0, 1))

    region_a = real_box([
        ("-1.8", "0.2"),
        ("-1.0", "0.7"),
    ])
    region_b = real_box([
        ("-0.4", "1.7"),
        ("-0.2", "1.4"),
    ])

    figure.set_fill_colour(0.20, 0.60, 0.90)
    figure.set_fill_opacity(0.45)
    figure.set_line_colour(0.05, 0.20, 0.35)
    figure.set_line_width(2.0)
    figure.draw(region_a)

    figure.set_fill_colour(0.95, 0.55, 0.15)
    figure.set_fill_opacity(0.35)
    figure.set_line_colour(0.45, 0.20, 0.05)
    figure.draw(region_b)

    show("figure bounding box", figure.get_bounding_box())
    show("line width", figure.get_line_width())
    show("fill opacity", figure.get_fill_opacity())

    figure.write("tutorial_drawing_layers")
    figure.write("tutorial_drawing_layers_large", 1000, 700)

    section("Reusing a figure with clear()")

    figure.clear()
    figure.set_fill_colour(green)
    figure.set_fill_opacity(0.30)
    figure.set_line_colour(darkgrey)
    figure.set_line_width(1.0)
    figure.draw(intersection(region_a, region_b))
    figure.write("tutorial_drawing_intersection")

    section("Projecting higher-dimensional sets")

    set3d = make_demo_set()
    viewport3d = FloatDPExactBox([
        {exact(-2.0): exact(2.0)},
        {exact(-2.0): exact(2.0)},
        {exact(-2.0): exact(2.0)},
    ])

    xy = Figure(viewport3d, Projection2d(3, 0, 1))
    xy.set_fill_colour(cyan)
    xy.set_fill_opacity(0.40)
    xy.draw(set3d)
    xy.write("tutorial_drawing_projection_xy")

    xz = Figure(viewport3d, Projection2d(3, 0, 2))
    xz.set_fill_colour(magenta)
    xz.set_fill_opacity(0.40)
    xz.draw(set3d)
    xz.write("tutorial_drawing_projection_xz")

    show("xy projection", xy.get_2d_projection_map())
    show("xz projection", xz.get_2d_projection_map())

    section("Choosing how validated nonlinear sets are drawn")

    drawer_manager.set_drawer(BoxDrawer())
    box_view = Figure(viewport3d, Projection2d(3, 0, 1))
    box_view.set_fill_colour(red)
    box_view.set_fill_opacity(0.25)
    box_view.draw(set3d)
    box_view.write("tutorial_drawing_drawer_box")

    drawer_manager.set_drawer(AffineDrawer(2))
    affine_view = Figure(viewport3d, Projection2d(3, 0, 1))
    affine_view.set_fill_colour(blue)
    affine_view.set_fill_opacity(0.25)
    affine_view.draw(set3d)
    affine_view.write("tutorial_drawing_drawer_affine")

    drawer_manager.set_drawer(GridDrawer(4))
    grid_view = Figure(viewport3d, Projection2d(3, 0, 1))
    grid_view.set_fill_colour(orange)
    grid_view.set_fill_opacity(0.25)
    grid_view.draw(set3d)
    grid_view.write("tutorial_drawing_drawer_grid")

    drawer_manager.set_drawer(AffineDrawer(0))


    section("Points, curves and mathematical collections")
    plane = Projection2d(2, 0, 1)
    view2d = FloatDPExactBox([{exact(-2): exact(2)}, {exact(-2): exact(2)}])
    drawer_manager.set_drawer(BoxDrawer())

    precision = DoublePrecision()
    pt = FloatDPPoint([FloatDP(exact("0.25"), precision),
                       FloatDP(exact("0.5"), precision)])
    points = Figure(view2d, plane)
    points.draw(pt)
    points.write("tutorial_drawing_points")

    def curve_point(x, y):
        return FloatDPApproximationPoint([
            FloatDPApproximation(exact(x), precision),
            FloatDPApproximation(exact(y), precision),
        ])

    curve = InterpolatedCurve(curve_point("-1", "-0.5"),
                              curve_point("0", "0.75"))
    curves = Figure(view2d, plane)
    curves.draw(curve)
    curves.write("tutorial_drawing_curve")

    list_set = ExactBoxListSet(2)
    list_set.adjoin(FloatDPExactBox([
        {exact("-1.5"): exact("-0.5")},
        {exact("-0.75"): exact("0.25")},
    ]))
    list_set.adjoin(FloatDPExactBox([
        {exact("0.25"): exact("1.25")},
        {exact("-0.25"): exact(1)},
    ]))
    collection = Figure(view2d, plane)
    collection.draw(list_set)
    collection.write("tutorial_drawing_list")

    grid = Grid(2)
    paving = GridTreePaving(grid)
    paving.adjoin_over_approximation(FloatDPExactBox([
        {exact(-1): exact(1)}, {exact(-1): exact(1)},
    ]), 0)
    cell = next(iter(paving))
    cells = Figure(view2d, plane)
    cells.draw(cell)
    cells.write("tutorial_drawing_cell")
    paving_view = Figure(view2d, plane)
    paving_view.draw(paving)
    paving_view.write("tutorial_drawing_paving")

    domain = real_box([("-1", "1"), ("-1", "1")])
    x0 = EffectiveScalarMultivariateFunction.coordinate(2, 0)
    x1 = EffectiveScalarMultivariateFunction.coordinate(2, 1)
    mapping = EffectiveVectorMultivariateFunction([x0, x1])
    bounded = BoundedConstraintSet(domain, mapping, domain)
    effective = ConstrainedImageSet(domain, mapping)
    validated = ValidatedConstrainedImageSet(FloatDPExactBox([
        {exact(-1): exact(1)}, {exact(-1): exact(1)},
    ]))
    affine_set = ValidatedAffineConstrainedImageSet(FloatDPExactBox([
        {exact(-1): exact(1)}, {exact(-1): exact(1)},
    ]))
    for name, item in (("bounded", bounded), ("effective", effective),
                       ("validated", validated), ("affine_set", affine_set)):
        illustration = Figure(view2d, plane)
        illustration.draw(item)
        illustration.write("tutorial_drawing_" + name)

    section("What the Drawing layer is responsible for")
    print("Figure: collect drawable objects and their per-layer style.")
    print("Projection2d: choose which coordinates of a higher-dimensional object are displayed.")
    print("RenderingProperties / Colour: control line, fill and opacity independently of geometry.")
    print("RenderingManager: choose the rendering backend and nonlinear-set drawer globally.")
    print("BoxDrawer / AffineDrawer / GridDrawer: trade rendering cost for geometric detail.")
    print("DefaultRenderingBackend: materialise figures as PNG files.")


if __name__ == "__main__":
    tutorial_rendering()
