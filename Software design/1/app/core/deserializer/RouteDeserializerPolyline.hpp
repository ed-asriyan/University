//
// Created by ed on 2/27/18.
//

#ifndef APP_CORE_ROUTEDESERIALIZERPOLYLINE_HPP
#define APP_CORE_ROUTEDESERIALIZERPOLYLINE_HPP

#include "RouteDeserializer.hpp"

namespace app {
namespace core {
namespace deserializers {
/**
 * Deserializer from Polyline format.
 *
 * The stub for scalability demonstration.
 */
class RouteDeserializerPolyline : public RouteDeserializer {
public:
	Route deserialize(const std::string& data) final;
};

}
}
}

#endif //APP_CORE_ROUTEDESERIALIZERPOLYLINE_HPP
