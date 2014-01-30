// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOEMTRY_LITERALS_HPP
#define BOOST_GEOEMTRY_LITERALS_HPP

#include <boost/config.hpp>
#include <boost/geometry/io/wkt/read.hpp>

#ifndef BOOST_NO_CXX11_USER_DEFINED_LITERALS

namespace boost { namespace geometry {

namespace detail { namespace wkt {

struct prefix_empty
{
    static inline const char* apply() { return ""; }
};

template <typename Geometry, template<typename> class Parser>
struct unprefixed_geometry_parser
{
    // warning! geometry must be empty!
    static inline void apply(std::string const& wkt, Geometry& geometry)
    {
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

        tokenizer tokens(wkt, boost::char_separator<char>(" ", ",()"));
        tokenizer::iterator it = tokens.begin();
        tokenizer::iterator end = tokens.end();

        Parser<Geometry>::apply(it, end, wkt, geometry);
        check_end(it, end, wkt);
    }
};

}} // namespace detail::wkt

namespace literals {

namespace cart2d {

model::point<double, 2, cs::cartesian> operator"" _pt (const char * c_str, unsigned long n)
{
    typedef model::point<double, 2, cs::cartesian> point;

	std::string str(c_str, n);

    point result;

    detail::wkt::unprefixed_geometry_parser<point, detail::wkt::point_parser>::apply(str, result);

	return result;
}

model::box< model::point<double, 2, cs::cartesian> > operator"" _box (const char * c_str, unsigned long n)
{
    typedef model::point<double, 2, cs::cartesian> point;
	typedef model::box<point> box;
	
	std::string str(c_str, n);

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
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
        throw read_wkt_exception("Box should have 2,4 or 5 points", str);
	}

	box result;

	geometry::detail::assign_point_to_index<min_corner>(points.front(), result);
	geometry::detail::assign_point_to_index<max_corner>(points[index], result);

	return result;
}

model::linestring< model::point<double, 2, cs::cartesian> > operator"" _ls (const char * c_str, unsigned long n)
{
    typedef model::point<double, 2, cs::cartesian> point;
    typedef model::linestring<point> linestring;

    std::string str(c_str, n);

    linestring result;

    detail::wkt::unprefixed_geometry_parser<linestring, detail::wkt::linestring_parser>::apply(str, result);

    return result;
}

model::ring< model::point<double, 2, cs::cartesian> > operator"" _ring (const char * c_str, unsigned long n)
{
    typedef model::point<double, 2, cs::cartesian> point;
    typedef model::ring<point> ring;

    std::string str(c_str, n);

    ring result;

    // NOTE! simplified ring representation could be used - in that case linestring_parser could be used
    detail::wkt::unprefixed_geometry_parser<ring, detail::wkt::ring_parser>::apply(str, result);

    return result;
}

model::polygon< model::point<double, 2, cs::cartesian> > operator"" _poly (const char * c_str, unsigned long n)
{
    typedef model::point<double, 2, cs::cartesian> point;
    typedef model::polygon<point> polygon;

    std::string str(c_str, n);

    polygon result;

    detail::wkt::unprefixed_geometry_parser<polygon, detail::wkt::polygon_parser>::apply(str, result);

    return result;
}

} // namespace cart2f

} // namespace literals

}} // namespace boost::geometry

#endif // BOOST_NO_CXX11_USER_DEFINED_LITERALS

#endif // BOOST_GEOEMTRY_LITERALS_HPP
