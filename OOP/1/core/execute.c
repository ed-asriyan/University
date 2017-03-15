//
// Created by ed on 07.03.17.
//

#include "execute.h"

error_t execute(command_t command, const command_data_t* command_data) {
	static service_t service;
	error_t error = NONE;
	switch (command) {
		case STARTUP:
			error = service_initialize(&service, command_data);
			break;
		case LOAD_MODEL:
			error = service_load_model(&service, command_data);
			break;
		case TRANSFORM_OBJECT:
			error = service_transform_object(&service, command_data);
			break;
		case TRANSFORM_CAMERA:
			error = service_transform_camera(&service, command_data);
			break;
		case RENDER:
			error = service_render(&service, command_data);
			break;
		case SHUTDOWN:
			error = service_shutdown(&service, command_data);
			break;
		default:
			error = UNKNOWN_COMMAND;
			break;
	}
	return error;
}