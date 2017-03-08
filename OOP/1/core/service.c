//
// Created by ed on 07.03.17.
//

#include "service.h"

error_t service_startup(service_t** service, const command_data_t* data) {
	if (*service) {
		return ALREADY_INITIALIZED;
	}
	if (!(*service = (service_t*) malloc(sizeof(service_t)))) {
		return OUT_OF_MEMORY;
	}
	camera_initialize(&(*service)->camera);
	object_initialize(&(*service)->object);
	return NONE;
}

error_t service_load_model(service_t* service, const command_data_t* command_data) {
	if (!service) {
		return NOT_INITIALIZED;
	}
	const load_model_data_t* data = &command_data->load_model_data;
	return object_load_model(&service->object, data->file_path);
}

error_t service_transform_object(service_t* service, const command_data_t* command_data) {
	if (!service) {
		return NOT_INITIALIZED;
	}
	const transform_object_data_t* data = &command_data->transform_object_data;
	const matrix_t transformation = matrix_create(&data->transformation);
	return object_transform(&service->object, &transformation);
}

error_t service_transform_camera(service_t* service, const command_data_t* command_data) {
	if (!service) {
		return NOT_INITIALIZED;
	}
	const transform_camera_data_t* data = &command_data->transform_camera_data;
	const matrix_t transformation = matrix_create(&data->transformation);
	camera_transform(&service->camera, &transformation);
	return NONE;
}

error_t service_render(const service_t* service, const command_data_t* command_data) {
	if (!service) {
		return NOT_INITIALIZED;
	}
	const render_data_t* data = &command_data->render_data;
	return object_render(&service->object, &service->camera, data->canvas);
}

error_t service_shutdown(service_t** service, const command_data_t* data) {
	if (!service) {
		return NOT_INITIALIZED;
	}
	camera_deinitialize(&(*service)->camera);
	object_deinitialize(&(*service)->object);
	free(service);
	service = NULL;
	return NONE;
}