//
// Created by ed on 2/27/18.
//

#include <cmath>

#include "RouteSerializerPolyline.hpp"

namespace polyline_encode {
/*
 * Source:
 * https://github.com/lieroz/University/blob/master/Sem_06/PPO/Lab_01/3dparty/polyline/polylineencoder.cpp
 */

static const double s_precision = 100000.0;

static const int32_t s_chunkSize = 5;

static const int32_t s_asciiOffset = 63;

static const int32_t s_5bitMask = 0x1f;

static const int32_t s_6bitMask = 0x20;

inline void encode(std::string& str, double value) {
	auto e5 = static_cast<int32_t>(std::round(value * s_precision));

	e5 <<= 1;

	if (value < 0) {
		e5 = ~e5;
	}

	bool hasNextChunk;
	do {
		int32_t nextChunk = (e5 >> s_chunkSize);
		hasNextChunk = nextChunk > 0;

		int32_t charVar = e5 & s_5bitMask;
		if (hasNextChunk) {
			charVar |= s_6bitMask;
		}
		charVar += s_asciiOffset;
		str += (u_char) charVar;

		e5 = nextChunk;
	} while (hasNextChunk);
}

std::string encode(const app::core::Route& polyline) {
	std::string result;
	result.reserve(polyline.size() * 9 + 1);

	double latPrev = .0;
	double lonPrev = .0;

	for (const auto& point: polyline) {
		const auto lat = point.x;
		const auto lon = point.y;

		encode(result, lat - latPrev);
		encode(result, lon - lonPrev);

		latPrev = lat;
		lonPrev = lon;
	}

	return result;
}
}

std::string app::core::serializers::RouteSerializerPolyline::serialize(const app::core::Route& route) {
	return polyline_encode::encode(route);
}
