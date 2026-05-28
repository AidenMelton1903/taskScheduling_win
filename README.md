# forward

a simple cooperative task scheduler written in C for the Windows operating system. I don't have access to my arduino right now but I wanted to do a warmup for when I would. below are some explanations of this repo's contents.

## struct task_t
contains information about a task, namely when it was last run and how frequently it should be run

## struct taskStruct
stores all task_t structs, the functions they correspond to (stored in a function dispatch table), and the index of the next empty location. please do not interact with this struct or any other outside of the exposed methods.

## void initTaskStruct(struct taskStruct *)
when provided with a pointer to a taskStruct, it initializes it.

## int addTask(struct taskStruct *, void function *, uint32_t time_ms)
when provided with a pointer to a taskStruct, a pointer to a function (requires it to be of type void and have no input parameters) and a uint32 representing delay time in ms, this function creates a new task inside the taskStruct. Presently, the maximum possible delay for a task is roughly 24 hours, times beyond this will likely not run at all and attempting to add one will cause the program to exit with error code 2. addTask() will return the index of the created task, if successful.

## void removeTask(struct taskStruct *, uint32_t index)
removes task from provided taskStruct at index. To do this it copies the rest of the tasks array and shifts it leftwards, overwriting and removing the task in the process. This may be changed in the future, however at present the intent was to minimize the number of tasks that would be iterated over within the main loop. This may not be valid reasoning. In any case, this scheduler isn't really meant to switch tasks that often.

## void runTasks(struct taskStruct *)
when provided with a taskStruct, it checks if any tasks have been scheduled to run and runs them if so. Ideally this function should be contained within an infinite loop.
