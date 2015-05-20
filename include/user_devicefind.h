#ifndef __USER_DEVICEFIND_H__
#define __USER_DEVICEFIND_H__

void user_devicefind_init(void);

typedef struct device_status {
	char name[25];
	int status;
};

#endif
