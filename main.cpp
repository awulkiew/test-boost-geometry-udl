#include <iostream>

#include <boost/geometry.hpp>

#include "literals.hpp"

int main()
{
	namespace bg = boost::geometry;

	using namespace bg::literals::cart2f;

	std::cout << bg::within("(1 1)"_pt, "(0 0, 2 2)"_box) << std::endl;
}