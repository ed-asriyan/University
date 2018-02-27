#include <iostream>

#include "crow_all.h"

#include "core/deserializer/RouteDeserializerGpx.hpp"
#include "core/serializers/RouteSerializerPolyline.hpp"

#include "RouteTranslator.hpp"

using namespace app;

RouteTranslator<core::deserializers::RouteDeserializerGpx, core::serializers::RouteSerializerPolyline> translator;

crow::response gpx_polyline(const crow::request& req) {
	return crow::response{translator.translate(req.body)};
}

int main() {
	crow::SimpleApp crow;

	CROW_ROUTE(crow, "/gpx/polyline").methods("POST"_method)(&gpx_polyline);
	crow.port(8080).multithreaded().run();
}
