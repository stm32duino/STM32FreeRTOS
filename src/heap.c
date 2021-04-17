/*
 * @file    heap.c
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Provide Memory allocation implementations included in the FreeRTOS source
 * heap_useNewlib_ST - thread-safe memory manager using C runtime (Newlib)
 * heap_1 - the very simplest, does not permit memory to be freed
 * heap_2 - permits memory to be freed, but not does coalescence adjacent free blocks.
 * heap_3 - simply wraps the standard malloc() and free() for thread safety
 * heap_4 - coalescences adjacent free blocks to avoid fragmentation. Includes absolute address placement option
 * heap_5 - as per heap_4, with the ability to span the heap across multiple non-adjacent memory areas
 */
#include "FreeRTOS.h"

#ifndef configMEMMANG_HEAP_NB
#define configMEMMANG_HEAP_NB      -1
#endif

#if configMEMMANG_HEAP_NB != -1
/* Need to be redefined as a value as it used in some heap_*.c as array size */
#undef configTOTAL_HEAP_SIZE
#define configTOTAL_HEAP_SIZE             ((size_t)(15 * 1024))
#endif

#if (configMEMMANG_HEAP_NB == -1)
#include "../portable/MemMang/heap_useNewlib_ST.c"
#elif (configMEMMANG_HEAP_NB == 1)
#include "../portable/MemMang/heap_1.c"
#elif (configMEMMANG_HEAP_NB == 2)
#include "../portable/MemMang/heap_2.c"
#elif (configMEMMANG_HEAP_NB == 3)
#include "../portable/MemMang/heap_3.c"
#elif (configMEMMANG_HEAP_NB == 4)
#include "../portable/MemMang/heap_4.c"
#elif (configMEMMANG_HEAP_NB == 5)
#include "../portable/MemMang/heap_5.c"
#else
#error "Wrong Memory allocation implementations defined"
#endif
