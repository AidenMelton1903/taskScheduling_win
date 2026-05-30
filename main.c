#include <stdio.h>
#include "cooperativeScheduler.h"

void task1(){
	printf("hello from task 0!\n");
}

void task2(){
	printf("hello from task 1!\n");
}

void task3(){
	printf("hello from task 2!\n");
}

void task4(){
	printf("hello from task 3!\n");
}

void task5(){
	printf("hello from task 4!\n");
}

int main(){
	struct taskStruct tasks;
	initTaskStruct(&tasks);
	
	addTask(&tasks,task1,250);
	addTask(&tasks,task2,250);
	addTask(&tasks,task3,250);
	addTask(&tasks,task4,250);
	addTask(&tasks,task5,250);
	removeTask(&tasks,1);
	while(1){
		runTasks(&tasks);
	}
}