//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_EXECUTE_H
#define INC_3DVIEW_EXECUTE_H

#include "errors.h"
#include "commands.h"
#include "service.h"

error_t execute(command_t command, const command_data_t* command_data);

#endif //INC_3DVIEW_EXECUTE_H
