#include "MMap.h"

#define H2F_LW_REGS_BASE ( 0xfc000000 )
#define H2F_LW_REGS_SPAN ( 0x04000000 )
#define PWM_PHYS_START   ( 0xff200000 )
using namespace std;
//Your Reg32_Write and Reg32_Read methods
//should print out useful debug messages
//whenever this boolean is set to true.
const bool m_debug = true;

MMap::MMap() {
	m_fd = -1;
	m_virtual_base = MAP_FAILED;
	map(H2F_LW_REGS_BASE, H2F_LW_REGS_SPAN);
}

MMap::~MMap(){
	unmap();
}

/**
 * An internal method that uses mmap to establish a device memory mapping.
 * If an error occurs is prints a message to stderr and returns false.
 * @param addr_base - The base physical address of the device to map
 * @param addr_span - The number of bytes to map, from addr_base
 * @return true if mapping created successfully, else false
 */
bool MMap::map(uint32_t addr_base, uint32_t addr_span) {
	
	bool bSuccess = false;
	int fd;
	void *virtual_base;
	m_addr_span = addr_span;

	unmap();

	if ( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		fprintf(stderr, "ERROR: could not open \"/dev/mem\"...\n");
	} else {
		virtual_base = mmap( NULL, addr_span, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, addr_base );
		if ( virtual_base == MAP_FAILED ) {
			fprintf(stderr, "ERROR: mmap() failed...\n");
			close( fd );
		} else {
			bSuccess = true;
			m_fd = fd;
			m_virtual_base = virtual_base;
		}
	}
	return bSuccess;
}

/**
 * An internal method that is used to remove an existing mapping;
 * this is also be used during initialization to ensure the physical
 * addresses are not already mapped.
 */
void MMap::unmap() {
	
	if (m_virtual_base != MAP_FAILED){
		if( munmap( m_virtual_base, m_addr_span ) != 0 ) 
			fprintf(stderr, "ERROR: munmap() failed...\n" );
		m_virtual_base = MAP_FAILED;	
		close( m_fd );
		m_fd = -1;
	}	
}

/**
 * @return true if the mapping has been established succesfully, else false
 */
bool MMap::isMapped() {
	return (m_virtual_base != MAP_FAILED) && (m_fd != -1);
}

/**
 * @return a virtual pointer to the first device register address,
 * which is (PWM_PHYS_START - H2F_LW_REGS_BASE) bytes above m_virtual_base.
 */
uint32_t* MMap::getDeviceStart(int motor_offset) {
	//TODO add the correct offset to this as described in Pre-lab Assignment 1

	uint32_t* val = (uint32_t*)((char *)m_virtual_base + 0x3200000 + motor_offset);
	return val;
}

/**
 * Writes a 32-bit value into a memory mapped device register.
 * 
 * This should take a relative device offset
 * (see hps_0.h for definitions of device offsets
 *  - e.g., PWM_17 has offset 0x0, PWM_0 hasoffset 0x110),
 * an index into that devices list of registers, and a value to set the register to.
 * @param offset - The offset from getDeviceStart() to the beginning
 *  of a specific device's address range in bytes.
 * @param index - Which 32-bit register in a device's address range you want to write.
 * @param value - The 32-bit unsigned value to write to the register.
 * @return bool - true if the mapping currently exists and can be used, else false.
 */
bool MMap::Reg32_Write(uint32_t offset, uint32_t index, uint32_t value) {
	if (m_virtual_base == MAP_FAILED)
		return false;
	//TODO fill this out
	if (m_debug){
		cout << "Reg write " << offset << " " << index << endl;
	}
	*(getDeviceStart(offset)+index) = value;
	
	
	return true;
	
}

/**
 * See MMap::Reg32_Write for documentation on how offset and index
 * should be interpreted. This performs a read operation of a register
 * and returns the value as an unsigned 32-bit integer.
 * @param offset - The offset from getDeviceStart() to the beginning
 *  of a specific device's address range in bytes.
 * @param index - Which 32-bit register in a device's address range you want to write.
 * @return uint32_t - the value returned by the device register, zero extended as necessary to 32 bits.
 * returns 0 if the mapping does not exist.
 */
uint32_t MMap::Reg32_Read(uint32_t offset, uint32_t index) {
	
	if (m_virtual_base == MAP_FAILED)
		return 0;
	//TODO fill this out
	
	return  *(getDeviceStart(offset)+index);
}
