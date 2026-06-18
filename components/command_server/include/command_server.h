#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void command_server_start(void);
void command_server_task(void *pvParameters);

#ifdef __cplusplus
}
#endif
