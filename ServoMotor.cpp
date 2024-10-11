#ifndef Servo_H
#define Servo_H
/*
 * ServoMotor.cpp
 *
 * An implementation of the abstract class Motor
 * that uses MMIO to control a specific servo motor.
 * 
 */
#include "Motor.h"
#include "MMap.h"
//This file contains the base offsets for each PWM_BASE circuit defined as macros
//E.g., PWM0_BASE is defined as 0x110, PWM17_BASE is defined as 0x0
#include "hps_0.h"
using namespace std;

class ServoMotor : public Motor {

private:
	//Stores a pointer to the memory map object that can communicate with the servo.
	MMap* _mmio;
	int motorOffset;
public:
	/**
	 * Save the given object for interfacing with MMIO and call the default contsructor.
	 * This method should also set the PWM signals to initial, default values using MMIO.
	 */

	int bases[18] = {PWM0_BASE, PWM1_BASE, PWM2_BASE,
					 PWM3_BASE, PWM4_BASE, PWM5_BASE,
					 PWM6_BASE, PWM7_BASE, PWM8_BASE,
					 PWM9_BASE, PWM10_BASE, PWM11_BASE,
					 PWM12_BASE, PWM13_BASE, PWM14_BASE,
					 PWM15_BASE, PWM16_BASE, PWM17_BASE};
	ServoMotor(MMap* mmio, int motorId): Motor(motorId) {
		_mmio = mmio;
		
		motorOffset = bases[motorId];
		_mmio->Reg32_Write(bases[motorId], 0, 1000000); //period, 20 ms
		_mmio->Reg32_Write(bases[motorId], 1, 0);  //duty cycle, 0 ms
		_mmio->Reg32_Write(bases[motorId], 2, 892.5); //delay, 50 (allowed speed)
		_mmio->Reg32_Write(bases[motorId], 3, 0);  //abort, 0
		
		//TODO use MMIO to set:
		//The PWM period, PWM duty cycle, and delay (using the current m_delay value)
		//Also set the Abort field to 0
		
	}

	/**
	 * Nothing to do on destruction.
	 */
	~ServoMotor() {
	}

	/**
	 * Calls the parent implementation to update the m_fangle member
	 * and makes sure it is in the bounds [-90, 90].
	 * Then, this must use MMIO to update the servo's duty cycle.
	 */
	void Move(float fAngle) {
		Motor::Move(fAngle);
		//TODO compute the correct duty cycle from the current angle
		//and use MMIO to update the correct register

		//m_fAngle = fAngle;
		uint32_t new_dc = 555.56 * GetfAngle() + 75000;
		cout << "Moved address " << motorOffset << "to dc " << new_dc << endl;
		_mmio->Reg32_Write(motorOffset, 1, new_dc);
		
	}

	/**
	 * See the documentation in Motor.h for this method.
	 * Must be implemented here.
	 */

	bool IsReady() {
       uint32_t isRed = _mmio->Reg32_Read(motorOffset, 2);
	   isRed = isRed & 1;
	   if (isRed){
		   return true;
	   }else{
			return false;
	   }
	   
	}

	/**
	 * See the documentation in Motor.h for this method.
	 * The parent implementation updates the m_speed member and makes
	 * sure that it is set in bounds [0, 100].
	 * Use the GetSpeed() method to access this value.
	 * 
	 * This method must compute the delay based on the current
	 * speed and then must modifying the PWM registers using MMIO.
	 */
	void SetSpeed(int speed) {
		Motor::SetSpeed(speed);
		uint32_t new_delay = -7.655 * GetSpeed() + 1275;
		_mmio->Reg32_Write(motorOffset, 2, new_delay); //delay, 50
		
	}

};
#endif
