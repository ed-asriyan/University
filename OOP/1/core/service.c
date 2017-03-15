//
// Created by ed on 07.03.17.
//

#include "service.h"

error_t service_initialize(service_t* service, const command_data_t* command_data) {
	error_t error = NONE;
	if (!service->is_initialized) {
		camera_initialize(&service->camera);
		object_initialize(&service->object);
		service->is_initialized = true;
	} else {
		error = ALREADY_INITIALIZED;
	}
	return error;
}

error_t service_load_model(service_t* service, const command_data_t* command_data) {
	error_t error = NONE;
	if (service) {
		const load_model_data_t* data = &command_data->load_model_data;
		error = object_load_model(&service->object, data->file_path);
	} else {
		error = NOT_INITIALIZED;
	}
	return error;
}

error_t service_transform_object(service_t* service, const command_data_t* command_data) {
	error_t error = NONE;
	if (service) {
		const transform_object_data_t* data = &command_data->transform_object_data;
		const matrix_t transformation = matrix_create(&data->transformation);
		error = object_transform(&service->object, &transformation);
	} else {
		error = NOT_INITIALIZED;
	}
	return error;
}

error_t service_transform_camera(service_t* service, const command_data_t* command_data) {
	error_t error = NONE;
	if (service) {
		const transform_camera_data_t* data = &command_data->transform_camera_data;
		const matrix_t transformation = matrix_create(&data->transformation);
		camera_transform(&service->camera, &transformation);
	} else {
		error = NOT_INITIALIZED;
	}
	return error;
}

error_t service_render(const service_t* service, const command_data_t* command_data) {
	error_t error = NONE;
	if (service) {
		error = object_render(&service->object, &service->camera);
	} else {
		error = NOT_INITIALIZED;
	}
	return error;
}

error_t service_shutdown(service_t* service, const command_data_t* command_data) {
	error_t error = NONE;
	if (service->is_initialized) {
		camera_deinitialize(&service->camera);
		object_deinitialize(&service->object);
		service->is_initialized = false;
	} else {
		error = NOT_INITIALIZED;
	}
	return error;
}