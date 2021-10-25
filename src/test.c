/**
 * Test program
 * Note: this is not kernel object, so it is not written with kernel coding rules.
 */

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
//#include <uapi/asm-generic/int-ll64.h> userspace would use kernel includes...
#include "mem-definitions.h"

int main(int argc, char* argv[])
{
	int allocSize = 0;

	if(argc == 1)
	{
		printf("Not enough arguments!\n");
		return 1;
	}
	else if(argc == 2)
	{
		sscanf(argv[1], "%i", &allocSize);
		printf("%i bytes to be allocated\n", allocSize);
	}
	else
	{
		printf("Too many arguments!\n");
		return 2;
	}

	char* ptr = NULL;
	if(allocSize > 0)
	{
		ptr = (char*)calloc(1, allocSize);

		if(NULL == ptr)
		{
			printf("Unable to allocate %i bytes of memory!\n", allocSize);
			return 4;
		}
	}
	else
	{
		printf("Invalid size argument!\n");
		return 3;
	}

	FILE* fp;
    fp = fopen("/dev/mem-kdawid", "wb");
    if(NULL == fp)
    {
        printf("Unable to open 'mem-kdawid' device!\n");
        return 4;
    }
    
	// get physical address of allocated memory (TODO!)
	
	// print results (not working due to earlier step in TODO stage) 
	int items = 0;
    __u64 user = 0;
    __u64 phys = 0;
    
	for(int i = 0; i < items; ++i)
    {
        printf("virt = %" PRIx64 " phys = %" PRIx64 "\n", user, phys);
    }
    
    fclose(fp);
    free(ptr);

	return 0;
}
