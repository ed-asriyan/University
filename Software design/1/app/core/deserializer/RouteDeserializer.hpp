//
// Created by ed on 2/27/18.
//

#ifndef APP_CORE_ROUTEDESERIALIZER_HPP
#define APP_CORE_ROUTEDESERIALIZER_HPP

#include <string>

#include "../Route.hpp"

namespace app {
namespace core {
namespace deserializers {
/**
 * Base abstract Route deserializer.
 */
class RouteDeserializer {
public:
	virtual ~RouteDeserializer() = default;

	/**
	 * Creates route from raw data.
	 * @param data Row data to deserialize.
	 * @return Route.
	 */
	virtual Route deserialize(const std::string& data) = 0;
};

}
}
}
#endif //APP_CORE_ROUTEDESERIALIZER_HPP
