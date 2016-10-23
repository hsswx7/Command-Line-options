#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <sys/time.h>

typedef struct data_struct
{
	struct timespec time;
        //long long unsigned int totaltime; // added seconds and nano seconds
	char *string;
} data_t;

int addmsg(data_t data);
void input_msg(char*);
void clearlog(void);
char *getlog(void);
int savelog(char *filename, char *exeName);

#endif
