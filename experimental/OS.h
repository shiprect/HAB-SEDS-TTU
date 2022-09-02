#ifndef HAB_SEDS_TTU_OS_H
#define HAB_SEDS_TTU_OS_H




/// Priority used for thread control.
/// \note MUST REMAIN UNCHANGED: \b osPriority shall be consistent in every CMSIS-RTOS.
typedef enum  {
	osPriorityIdle          = -3,          ///< priority: idle (lowest)
	osPriorityLow           = -2,          ///< priority: low
	osPriorityBelowNormal   = -1,          ///< priority: below normal
	osPriorityNormal        =  0,          ///< priority: normal (default)
	osPriorityAboveNormal   = +1,          ///< priority: above normal
	osPriorityHigh          = +2,          ///< priority: high
	osPriorityRealtime      = +3,          ///< priority: realtime (highest)
	osPriorityError         =  0x84        ///< system cannot determine priority or thread has illegal priority
} osPriority;



/// Status code values returned by CMSIS-RTOS functions.
/// \note MUST REMAIN UNCHANGED: \b osStatus shall be consistent in every CMSIS-RTOS.
typedef enum  {
	osOK                    =     0,       ///< function completed; no error or event occurred.
	osEventSignal           =  0x08,       ///< function completed; signal event occurred.
	osEventMessage          =  0x10,       ///< function completed; message event occurred.
	osEventMail             =  0x20,       ///< function completed; mail event occurred.
	osEventTimeout          =  0x40,       ///< function completed; timeout occurred.
	osErrorParameter        =  0x80,       ///< parameter error: a mandatory parameter was missing or specified an incorrect object.
	osErrorResource         =  0x81,       ///< resource not available: a specified resource was not available.
	osErrorTimeoutResource  =  0xC1,       ///< resource not available within given time: a specified resource was not available within the timeout period.
	osErrorISR              =  0x82,       ///< not allowed in ISR context: the function cannot be called from interrupt service routines.
	osErrorISRRecursive     =  0x83,       ///< function called multiple times from ISR with same object.
	osErrorPriority         =  0x84,       ///< system cannot determine priority or thread has illegal priority.
	osErrorNoMemory         =  0x85,       ///< system is out of memory: it was impossible to allocate or reserve memory for the operation.
	osErrorValue            =  0x86,       ///< value of a parameter is out of range.
	osErrorOS               =  0xFF,       ///< unspecified RTOS error: run-time error but no other error message fits.
	os_status_reserved      =  0x7FFFFFFF  ///< prevent from enum down-size compiler optimization.
} osStatus;







/// Entry point of a thread.
/// \note MUST REMAIN UNCHANGED: \b os_pthread shall be consistent in every CMSIS-RTOS.
typedef void (*os_pthread) (void const *argument);

/// Entry point of a timer call back function.
/// \note MUST REMAIN UNCHANGED: \b os_ptimer shall be consistent in every CMSIS-RTOS.
typedef void (*os_ptimer) (void const *argument);

// >>> the following data type definitions may shall adapted towards a specific RTOS

/// Thread ID identifies the thread (pointer to a thread control block).
/// \note CAN BE CHANGED: \b os_thread_cb is implementation specific in every CMSIS-RTOS.
typedef struct os_thread_cb *osThreadId;

/// Timer ID identifies the timer (pointer to a timer control block).
/// \note CAN BE CHANGED: \b os_timer_cb is implementation specific in every CMSIS-RTOS.
typedef struct os_timer_cb *osTimerId;

/// Mutex ID identifies the mutex (pointer to a mutex control block).
/// \note CAN BE CHANGED: \b os_mutex_cb is implementation specific in every CMSIS-RTOS.
typedef struct os_mutex_cb *osMutexId;

/// Semaphore ID identifies the semaphore (pointer to a semaphore control block).
/// \note CAN BE CHANGED: \b os_semaphore_cb is implementation specific in every CMSIS-RTOS.
typedef struct os_semaphore_cb *osSemaphoreId;

/// Pool ID identifies the memory pool (pointer to a memory pool control block).
/// \note CAN BE CHANGED: \b os_pool_cb is implementation specific in every CMSIS-RTOS.
typedef struct os_pool_cb *osPoolId;

/// Message ID identifies the message queue (pointer to a message queue control block).
/// \note CAN BE CHANGED: \b os_messageQ_cb is implementation specific in every CMSIS-RTOS.
typedef struct os_messageQ_cb *osMessageQId;

/// Mail ID identifies the mail queue (pointer to a mail queue control block).
/// \note CAN BE CHANGED: \b os_mailQ_cb is implementation specific in every CMSIS-RTOS.
typedef struct os_mailQ_cb *osMailQId;



#endif //HAB_SEDS_TTU_OS_H