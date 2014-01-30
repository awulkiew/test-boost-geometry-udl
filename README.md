### C++11 UDLs for Boost.Geometry

A quick implementation of UDLs for Boost.Geometry models.

Ideally compile-time WKT would be great, something like this:

    "LINESTRING(0 0, 1 1, 2 2)"_wkt

but it's impossible to parse string literals in compile-time (AFAIK, for now(?)), unfortunately. And no, preprocessor is not the answer.

We're forced to use run-time parsing which probably ruin the whole idea but for test/learning purposes it's ok.

Since Boost.Geometry hasn't any run-time geometry yet, currently each geometry model has it's own suffix:

    using namespace bg::literals::cart2d;

    "(1 1)"_pt; // point<double, 2, cs::cartesian>
    "(0 0, 2 2)"_box; // box<p2d>
    "(0 0, 1 1, 2 1)"_ls; // linestring<p2d>
    
    // polygon<p2d> - for now the default cw closed, should probably be ccw
    "((1 0, 1 3, 3 3, 3 0, 1 0))"_poly
    
    // ring<p2d> - for now the default cw closed, should probably be ccw
    // also non-WKT definition could be used - without doubled parentheses
    "((1 0, 1 3, 3 3, 3 0, 1 0))"_ring
    
