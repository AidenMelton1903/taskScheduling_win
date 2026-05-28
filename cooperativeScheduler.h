#include <stdint.h>
#ifndef COOP_SCHEDULER_H
#define COOP_SCHEDULER_H

//the maximum time in ms that you are allowed to schedule a task for.
#define maxTime_ms 86400000

typedef void (*taskFunc)(void);

struct task_t{
	uint64_t time_ms;
	uint64_t lastRun_ms;
};

struct taskStruct{
	struct task_t tasks[256];
	taskFunc taskFDT[256];
	uint32_t taskIndex;
};

void initTaskStruct(struct taskStruct *taskIn);
int addTask(struct taskStruct *taskIn, taskFunc newFunc, uint32_t time);
void removeTask(struct taskStruct *taskIn, uint32_t index);
void runTasks(struct taskStruct *taskIn);

#endif