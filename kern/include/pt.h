#ifndef _PT_H
#define _PT_H

#define STACKPAGES  18


// Errors
#define ERR_CODE ((paddr_t) -1)

#include "opt-ondemand_manage.h"

#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <spl.h>
#include <cpu.h>
#include <spinlock.h>
#include <proc.h>
#include <current.h>
#include <mips/tlb.h>
#include <addrspace.h>
#include <vm.h>
#include <coremap.h>
#include <proc_syscalls.h>
#include <vm_tlb.h>

#define CLUSTER_SIZE 4

/* macros for accessing the PT entry fields */
#define PT_V_ADDR(entry) ((unsigned int)((entry) & PAGE_FRAME))
#define PT_PID(entry)    ((int)((entry) & (~PAGE_FRAME)))
#define PT_P_ADDR(entry) ((entry) * PAGE_SIZE)

typedef int pt_entry;

/* bootstrap for the page table */
void pt_bootstrap(int first_free);

/* returns the entry corresponding to the page associated to the address v_addr (if that page is not in memory it will be loaded)*/
int pt_get_page(vaddr_t v_addr);

/* delete all pages of this process from page table */
void pt_delete_PID(struct addrspace *as, pid_t pid);

/* allocate clusters for kernel pages*/
void pt_getkpages(uint32_t n);

/* stats for used and unused pages */
int pt_stats(void);

#endif