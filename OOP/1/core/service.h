//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_SERVICE_H
#define INC_3DVIEW_SERVICE_H

#include <stdlib.h>

#include "camera.h"
#include "object.h"
#include "errors.h"
#include "commands.h"

typedef struct {
	camera_t camera;
	object_t object;
} service_t;

error_t service_startup(service_t** service, const command_data_t* command_data);
error_t service_load_model(service_t* service, const command_data_t* command_data);
error_t service_transform_object(service_t* service, const command_data_t* command_data);
error_t service_transform_camera(service_t* service, const command_data_t* command_data);
error_t service_render(const service_t* service, const command_data_t* command_data);
error_t service_shutdown(service_t** service, const command_data_t* command_data);

#endif //INC_3DVIEW_SERVICE_H
