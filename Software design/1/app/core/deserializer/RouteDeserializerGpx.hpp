//
// Created by ed on 2/27/18.
//

#ifndef APP_CORE_ROUTEDESERIALIZERGPX_HPP
#define APP_CORE_ROUTEDESERIALIZERGPX_HPP

#include "RouteDeserializer.hpp"

namespace app {
namespace core {
namespace deserializers {
/**
 * Deserializer from GPX format.
 */
class RouteDeserializerGpx : public RouteDeserializer {
public:
	Route deserialize(const std::string& data) final;
};

}
}
}

#endif //APP_CORE_ROUTEDESERIALIZERGPX_HPP
