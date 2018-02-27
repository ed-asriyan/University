//
// Created by ed on 2/27/18.
//

#include "RouteDeserializerGpx.hpp"

#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

void parseGpx(const std::string& data, app::core::Route& route) {
	std::stringstream ss;
	ss << data;

	boost::property_tree::ptree pt;
	boost::property_tree::xml_parser::read_xml(ss, pt);

	boost::property_tree::ptree gpx = pt.get_child("gpx");
	boost::property_tree::ptree trk = gpx.get_child("trk");
	boost::property_tree::ptree trkseg = trk.get_child("trkseg");

	for (const boost::property_tree::ptree::value_type& f: trkseg) {
		if (f.first == "trkpt") {
			boost::property_tree::ptree attrs = f.second.get_child("<xmlattr>");
			auto lat = attrs.get<double>("lat");
			auto lon = attrs.get<double>("lon");
			route.push_back({lat, lon});
		}
	}
}

app::core::Route app::core::deserializers::RouteDeserializerGpx::deserialize(const std::string& data) {
	Route route;
	parseGpx(data, route);
	return route;
}
