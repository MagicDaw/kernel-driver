/**
 * Definitions for mem-kdawid kernel driver and test program.
 */

#include <linux/fs.h>
#include <linux/ioctl.h>

#ifndef __64
	// user includes don't have this
	typedef unsigned long long __u64;
#endif

struct get_phys_address_params{
	__u64 user_mem_address;
	__u64 user_mem_size;
	__u64 physical_address_list;
};

#define MEM_KDAWID_IOCTL_GET_PHYS_ADDRESS\
	_IOW(0, 1, struct get_phys_address_params)
