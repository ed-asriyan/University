#include <iostream>
#include <string>

#include "RouteTranslator.hpp"

#include "core/deserializer/RouteDeserializerGpx.hpp"
#include "core/serializers/RouteSerializerPolyline.hpp"

using namespace app;

int main() {
	RouteTranslator<core::deserializers::RouteDeserializerGpx, core::serializers::RouteSerializerPolyline> translator;

	std::string input;
	std::cin >> input;
	std::cout << translator.translate(input);

	return 0;
}
