// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <boost/geometry.hpp>

#include "literals.hpp"

int main()
{
    namespace bg = boost::geometry;
    
    using namespace bg::literals::cart2d;
    
    std::cout << bg::within("(1 1)"_pt, "(0 0, 2 2)"_box) << std::endl;
    std::cout << bg::length("(0 0, 1 1, 2 1)"_ls) << std::endl;
    std::cout << bg::area("((1 0, 1 3, 3 3, 3 0, 1 0))"_poly) << std::endl;
    std::cout << bg::intersects("(0 0, 1 1)"_box, "((1 0, 1 3, 3 3, 3 0, 1 0))"_ring) << std::endl;
}
