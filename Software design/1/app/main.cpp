#include <functional>

#include "crow_all.h"

#include "core/deserializer/RouteDeserializerGpx.hpp"
#include "core/deserializer/RouteDeserializerPolyline.hpp"
#include "core/serializers/RouteSerializerPolyline.hpp"
#include "core/serializers/RouteSerializerGpx.hpp"

#include "RouteTranslator.hpp"

using namespace app;

template<class Deserializer, class Serializer>
std::function<crow::response(const crow::request&)> generate_view() {
	RouteTranslator<Deserializer, Serializer> translator;
	return [translator](const crow::request& request) {
		return crow::response(translator.translate(request.body));
	};
};

int main() {
	crow::SimpleApp crow;

	CROW_ROUTE(crow, "/gpx/polyline").methods("POST"_method)(
		generate_view<
			core::deserializers::RouteDeserializerGpx,
			core::serializers::RouteSerializerPolyline
		>());

	CROW_ROUTE(crow, "/polyline/gpx").methods("POST"_method)(
		generate_view<
			core::deserializers::RouteDeserializerPolyline,
			core::serializers::RouteSerializerGpx
		>());

	crow.port(8080).multithreaded().run();
}
