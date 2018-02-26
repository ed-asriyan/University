//
// Created by ed on 2/27/18.
//

#ifndef APP_CORE_ROUTESERIALIZER_HPP
#define APP_CORE_ROUTESERIALIZER_HPP

#include <string>

#include "../Route.hpp"

namespace app {
namespace core {
namespace serializers {
/**
 * Base abstract Route serializer.
 */
class RouteSerializer {
public:
	virtual ~RouteSerializer() = default;

	/**
	 * Serializes route to raw data.
	 * @param route Route to serialize.
	 * @return Raw data.
	 */
	virtual std::string serialize(const Route& route) = 0;
};

}
}
}

#endif //APP_CORE_ROUTESERIALIZER_HPP
