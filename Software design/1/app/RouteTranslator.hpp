//
// Created by ed on 2/27/18.
//

#ifndef APP_ROUTETRANSLATOR_HPP
#define APP_ROUTETRANSLATOR_HPP

#include <type_traits>

#include "core/Route.hpp"
#include "core/serializers/RouteSerializer.hpp"
#include "core/deserializer/RouteDeserializer.hpp"

namespace app {
/**
 * Translates route from one format to another using deserializer and serializer.
 * @tparam Deserializer Deserializer class
 * @tparam Serializer Serializer class
 */
template<class Deserializer, class Serializer>
class RouteTranslator {
public:
	constexpr RouteTranslator() {
		static_assert(std::is_base_of<core::serializers::RouteSerializer, Serializer>());
		static_assert(std::is_base_of<core::deserializers::RouteDeserializer, Deserializer>());
	}

	/**
	 * Translates route from one format to another.
	 * @param data input data.
	 * @return translated data.
	 */
	std::string translate(const std::string& data) {
		const auto route = static_cast<Deserializer>(deserializer).deserialize(data);
		return static_cast<Serializer>(serializer).serialize(route);
	}

private:
	Serializer serializer;
	Deserializer deserializer;

};
}

#endif //APP_CORE_ROUTETRANSLATOR_HPP
