// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOEMTRY_LITERALS_HPP
#define BOOST_GEOEMTRY_LITERALS_HPP

#include <boost/config.hpp>
#include <boost/geometry/io/wkt/read.hpp>

#ifndef BOOST_NO_CXX11_USER_DEFINED_LITERALS

namespace boost { namespace geometry { namespace literals {

namespace cart2f {

namespace detail
{

struct prefix_empty
{
	static inline const char* apply() { return ""; }
};

}

model::point<float, 2, cs::cartesian> operator"" _pt (const char * c_str, unsigned long n)
{
	typedef model::point<float, 2, cs::cartesian> point;

	std::string str(c_str, n);

	/*tokenizer tokens(str, boost::char_separator<char>(" ", ",()"));
	tokenizer::iterator it = tokens.begin();
	tokenizer::iterator end = tokens.end();
	
	point result;

	detail::wkt::handle_open_parenthesis(it, end, str);
	detail::wkt::parsing_assigner<point, 0, dimension<point>::value>::apply(it, end, result, str);
	detail::wkt::handle_close_parenthesis(it, end, str);

	detail::wkt::check_end(it, end, str);*/

	point result;

	detail::wkt::geometry_parser<point, detail::wkt::point_parser, detail::prefix_empty>
		::apply(str, result);

	return result;
}

model::box< model::point<float, 2, cs::cartesian> > operator"" _box (const char * c_str, unsigned long n)
{
	typedef model::point<float, 2, cs::cartesian> point;
	typedef model::box<point> box;
	
	std::string str(c_str, n);

	tokenizer tokens(str, boost::char_separator<char>(" ", ",()"));
	tokenizer::iterator it = tokens.begin();
	tokenizer::iterator end = tokens.end();

	std::vector<point> points;
	detail::wkt::container_inserter<point>::apply(it, end, str, std::back_inserter(points));

	detail::wkt::check_end(it, end, str);

	int index = 0;
	int count = boost::size(points);
	if (count == 2)
	{
		index = 1;
	}
	else if (count == 4 || count == 5)
	{
		// In case of 4 or 5 points, we do not check the other ones, just
		// take the opposite corner which is always 2
		index = 2;
	}
	else
	{
		throw read_wkt_exception("Box should have 2,4 or 5 points", wkt);
	}

	box result;

	geometry::detail::assign_point_to_index<min_corner>(points.front(), result);
	geometry::detail::assign_point_to_index<max_corner>(points[index], result);

	return result;
}

} // namespace cart2f

#endif // BOOST_NO_CXX11_USER_DEFINED_LITERALS

}}} // namespace boost::geometry::literals

#endif // BOOST_GEOEMTRY_LITERALS_HPP
