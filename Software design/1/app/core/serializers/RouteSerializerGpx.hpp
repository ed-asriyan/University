//
// Created by ed on 2/27/18.
//

#ifndef APP_CORE_ROUTESERIALIZERGPX_HPP
#define APP_CORE_ROUTESERIALIZERGPX_HPP

#include "RouteSerializer.hpp"

namespace app {
namespace core {
namespace serializers {
class RouteSerializerGpx : public RouteSerializer {
public:
	std::string serialize(const Route& route) final;
};

}
}
}

#endif //APP_CORE_ROUTESERIALIZERGPX_HPP
