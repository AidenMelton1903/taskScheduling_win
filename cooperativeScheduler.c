#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include "cooperativeScheduler.h"

void initTaskStruct(struct taskStruct *taskIn){
	taskIn->taskIndex=0;
}

int addTask(struct taskStruct *taskIn, taskFunc newFunc, uint32_t time){
	if(time > maxTime_ms){
		fprintf(stderr, "error when adding task. time \"%d\" is not valid. above allowed threshold.\n");
		exit(2);
	}
	
	taskIn->taskFDT[taskIn->taskIndex] = newFunc;
	taskIn->tasks[taskIn->taskIndex].time_ms = time;
	taskIn->tasks[taskIn->taskIndex].lastRun_ms = 0;
	
	taskIn->taskIndex+=1;
	return taskIn->taskIndex-1;
}

void removeTask(struct taskStruct *taskIn, uint32_t index){
	
	uint32_t tempSize = taskIn->taskIndex - index;
	struct task_t tempTasks[tempSize];
	taskFunc tempFDT[tempSize];
	
	//duplicate actual arrays into temp copies
	printf("start of copy: %d, end: %d\n",index+1,taskIn->taskIndex-1);
	for(int i = 0; i < tempSize; i++){
		tempTasks[i] = taskIn->tasks[index+i+1];
		tempFDT[i] = taskIn->taskFDT[index+i+1];
	}
	//insert it back into the main arrays
	printf("start of reload: %d, end: %d\n",index,taskIn->taskIndex-2);
	for(int i = 0; i < tempSize; i++){
		taskIn->tasks[index+i] = tempTasks[i];
		taskIn->taskFDT[index+i] = tempFDT[i];
	}
	taskIn->taskIndex--;
}


void runTasks(struct taskStruct *taskIn){
	SYSTEMTIME st;
	GetSystemTime(&st);
	
	uint64_t timeUnified = 
	(st.wHour * 60 * 60 * 1000)
	+(st.wMinute * 60 * 1000)
	+(st.wSecond * 1000)
	+st.wMilliseconds;
	
	for(int i = 0; i < taskIn->taskIndex; i++){
		if(taskIn->tasks[i].time_ms < (timeUnified - taskIn->tasks[i].lastRun_ms)){
			taskIn->taskFDT[i]();
			taskIn->tasks[i].lastRun_ms=timeUnified;
		}
	}
}