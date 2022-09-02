
Task: a thread of execution


Kernel Goals
Abstracting away timing information
The kernel is responsible for execution timing and provides a time-related API to the application. This allows the structure of the application code to be simpler, and the overall code size to be smaller.
 Maintainability/Extensibility
Abstracting away timing details results in fewer interdependencies between modules, and allows the software to evolve in a controlled and predictable way. Also, the kernel is responsible for timing, so application performance is less susceptible to changes in the underlying hardware.
 Modularity
Tasks are independent modules, each of which should have a well-defined purpose.
 Team development
Tasks should also have well-defined interfaces, allowing easier development by teams.
 Easier testing
If tasks are well-defined independent modules with clean interfaces, they can be tested in isolation.
 Code reuse
Greater modularity and fewer interdependencies results in code that can be reused with less effort.
 Improved efficiency
Using a kernel allows software to be completely event-driven, so no processing time is wasted by polling for events that have not occurred. Code executes only when there is something that must be done.
Counter to the efficiency saving is the need to process the RTOS tick interrupt, and to switch execution from one task to another. However, applications that don’t make use of an RTOS normally include some form of tick interrupt anyway.
 Idle time
The Idle task is created automatically when the scheduler is started. It executes whenever there are no application tasks wishing to execute. The idle task can be used to measure spare processing capacity, to perform background checks, or simply to place the processor into a low-power mode.
 Power Management
The efficiency gains that are obtained by using an RTOS allow the processor to spend more time in a low power mode.
Power consumption can be decreased significantly by placing the processor into a low power state each time the Idle task runs. FreeRTOS also has a special tick-less mode. Using the tick-less mode allows the processor to enter a lower power mode than would otherwise be possible, and remain in the low power mode for longer.
 Flexible interrupt handling
Interrupt handlers can be kept very short by deferring processing to either a task created by the application writer, or the FreeRTOS daemon task.
 Mixed processing requirements
Simple design patterns can achieve a mix of periodic, continuous and event-driven processing within an application. In addition, hard and soft real-time requirements can be met by selecting appropriate task and interrupt priorities.


Desired Features
Pre-emptive or co-operative operation
 Very flexible task priority assignment
 Flexible, fast and light weight task notification mechanism
 Queues
 Binary semaphores
 Counting semaphores
 Mutexes
 Recursive Mutexes
 Software timers
 Event groups
 Tick hook functions
 Idle hook functions
 Stack overflow checking
 Trace recording
 Task run-time statistics gathering
Full interrupt nesting model (for some architectures)
 A tick-less capability for extreme low power applications
 Software managed interrupt stack when appropriate (this can help save RAM)


Functions are prefixed with both the type they return, and the file they are defined within. For example:

FreeRTOS configures a periodic interrupt called the tick interrupt.
The number of tick interrupts that have occurred since the FreeRTOS application started is called the tick count. The tick count is used as a measure of time.
The time between two tick interrupts is called the tick period. Times are specified as multiples of tick periods.
TickType_t is the data type used to hold the tick count value, and to specify times.

Macro Value
pdTRUE
1
pdFALSE
0
pdPASS
1
pdFAIL
0





size_t xPortGetFreeHeapSize( void );
Returned value
The number of bytes that remain unallocated in the heap at the time xPortGetFreeHeapSize() is called.


size_t xPortGetMinimumEverFreeHeapSize( void );
Returned value
The minimum number of unallocated bytes that have existed in the heap since the FreeRTOS application started executing.


Just like the standard library malloc() function, if pvPortMalloc() cannot return a block of RAM because a block of the requested size does not exist, then it will return NULL. If pvPortMalloc() is executed because the application writer is creating a kernel object, and the call to pvPortMalloc() returns NULL, then the kernel object will not be created.






typedef int8_t myint;
BaseType_t





enum restartReason_t {
  RR_POWER_ON  = REASON_DEFAULT_RST,         /* = 0, normal startup by power on */
  RR_HARD_WDT  = REASON_WDT_RST,            /* = 1, hardware watch dog reset */
  RR_EXCEPTION = REASON_EXCEPTION_RST,      /* = 2, exception reset, GPIO status won’t change */
  RR_SOFT_WDT = REASON_SOFT_WDT_RST,        /* = 3, software watch dog reset, GPIO status won’t change */
  RR_SOFT_RESTART = REASON_SOFT_RESTART,    /* = 4, software restart ,system_restart , GPIO status won’t change */
  RR_DEEP_SLEEP = REASON_DEEP_SLEEP_AWAKE,  /* = 5, wake up from deep-sleep */
  RR_RESET = REASON_EXT_SYS_RST,            /* = 6, external system reset */  
  RR_LOOP_WDT                               /* loop watchdog reset */ 
};




params

soft_margin //WDT Value
timeout //soft_margin alias
nowayout //prevents timer from being restarted or disabled
pre_timeout //will trigger a syslog event before timeout occurs to save useful info

GetTimeLeft() //get time until timeout




//Basic WDT//

unsigned long WDTime = 0;
unsigned long WDTimeout = TIMEOUT_Period;

void WD_Interrupt_Check(void) {
	if( ( (mills() - WDTime) > TIMEOUT_Period) || (WDTimeout - WDTime) != TIMEOUT_Period) {
		WDT_Bite()
	}
	
}

void WD_Feed(void) {
	WDTime = millis();
	WDTimeout = WDTime + TIMEOUT_Period; //By adding a second check, the chances of a memfail correctly disrupting SOFTWD is limited
}







/* I N C L U D E S **********************************************************/
#include    "esos.h"

/* S T R U C T U R E S ******************************************************/

/* D E F I N E S ************************************************************/

/* M A C R O S ************************************************************/

/* E X T E R N S ************************************************************/
extern uint32_t       __esos_u32FNVHash;

/* P U B L I C  P R O T O T Y P E S *****************************************/
// ESOS-provided pseudo-random number generator
uint32_t    esos_GetRandomUint32();
// ESOS-provided hash functions
uint16_t 	esos_hash_u32_to_u16(uint32_t u32_hash);
uint32_t 	esos_string_hash_u32(char *psz_str);
uint32_t 	esos_buffer_hash_u32(void *buf, uint16_t len);
// ESOS-provided CRC functions go here

/* P R I V A T E    P R O T O T Y P E S ***********************************/
void 		__esos_set_PRNG_U32Seed(uint32_t u32_seed);
uint32_t    __esos_get_PRNG_RandomUint32(void);

/** @} */



