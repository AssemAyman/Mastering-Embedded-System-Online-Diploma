# Project Structure
The project is organized into the following directories:

### Inc
- **CortexMx_OS_porting.h**: Contains necessary definitions and configurations specific to the target platform. Used for porting the RTOS to different processors.
- **MY_RTOS_FIFO.h**: Contains necessary definitions and configurations for implementing the Ready Queue data structure, which is used by the RTOS.
- **Scheduler.h**: Contains type definitions and supported APIs in the RTOS.

 ### Src 
- **CortexMx_OS_porting.c**: Contains fault handlers, exceptional handlers, and hardware initialization.
- **MY_RTOS_FIFO.c**: Contains functions to handle Ready Queue.
- **Scheduler.c**: Contains the functions that manage the scheduling, dispatching, and intertask communication of the kernel.
  
![image](https://github.com/user-attachments/assets/471bd95f-6306-4536-84aa-6012b48e920d)
![image](https://github.com/user-attachments/assets/245fe92e-3ee0-4eb4-a3ee-d8a98ab8f679)
![image](https://github.com/user-attachments/assets/a61ec285-dd11-46b7-933d-67ce33ae8103)
![image](https://github.com/user-attachments/assets/b1c46fcf-f09b-4327-a96f-26911a5fdac2)
# Project Scheduling
![image](https://github.com/user-attachments/assets/02c2d4db-1816-485a-b94f-b6b8a801079f)
![image](https://github.com/user-attachments/assets/94049d06-fdcf-468b-aff0-6a164191326a)
### Function Description

- **MY_RTOS_Init()**: Initializes the OS control and buffers.
- **MY_RTOS_Start()**: Starts the OS scheduler to begin running tasks.
- **createTask()**: Creates the task object in the OS and initializes the task's stack area.
- **activateTask()**: Sends a task to the ready queue to be scheduled.
- **terminateTask()**: Sends a task to the suspended state.
- **Task_Wait**: Sends a task to the waiting state for a specific amount of Ticks.
- **AcquireMutex**: Tries to acquire a mutex if available.
- **ReleaseMutex**: Releases a mutex and starts the next task that is in the queue (if found).

