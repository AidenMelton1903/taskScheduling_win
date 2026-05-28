# forward

a simple cooperative task scheduler written in C for the Windows operating system. I don't have access to my arduino right now but I wanted to do a warmup for when I would. below are some explanations of this repo's contents.

## struct task_t
contains information about the struct, namely when it was last run and how frequently it should be run

## struct taskStruct
stores all task_t structs, the functions they correspond to (stored in a function dispatch table), and the index of the next empty location. please do not interact with this struct or any other outside of the exposed methods.

## void initTaskStruct(struct taskStruct *)
when provided with a pointer to a taskStruct, it initializes it.

## void addTask(struct taskStruct *, void function *, uint32_t time_ms)
when provided with a pointer to a taskStruct, a pointer to a function (requires it to be of type void and have no input parameters) and a uint32 representing delay time in ms, this function creates a new task inside the taskStruct.

## void runTasks(struct taskStruct *)
when provided with a taskStruct, it checks if any tasks have been scheduled to run and runs them if so. Ideally this function should be contained within an infinite loop.
