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
	//duplicate actual arrays into temp copies
	for(int i = index; i < taskIn->taskIndex-1; i++){
		taskIn->tasks[i] = taskIn->tasks[i+1];
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