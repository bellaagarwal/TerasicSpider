#ifndef MMAP_H_
#define MMAP_H_

#include "spider_os.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/**
 * This object represents a memory mapped IO interface for a single device. 
 * It manages the internal state of the memory mapping, and
 * exposes 32-bit register read and write methods to clients.
 */
class MMap {

protected:
	//Stores the file descriptor returned by mmap
	int m_fd;
	//Stores the virtual base pointer returned by mmap (translation of physical base addr)
	void *m_virtual_base;
	//Stores the size of 
	uint32_t m_addr_span;

protected:
	bool map(uint32_t addr_base, uint32_t addr_span);
	void unmap();
	uint32_t* getDeviceStart(int motor_offset);

public:
	MMap();
	virtual ~MMap();
	bool isMapped();
	bool Reg32_Write(uint32_t Addr, uint32_t Index, uint32_t Value);
	uint32_t Reg32_Read(uint32_t Addr, uint32_t Index);
};

#endif /* MMAP_H_ */
