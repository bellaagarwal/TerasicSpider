/**
 * Motor.h
 * Defines the abstract Motor class.
 * You will also have to override some of these methods in other files
 * for some of the labs (it will be noted there).
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

#define DEGREE_MIN -90
#define DEGREE_MAX 90
#define SPEED_MAX 100
#define SPEED_MIN 0

class Motor {

private:
	//The current angle (in the range [-90,90]) of the servo motor.
	float m_fAngle;
	//The current effective operating speed.
	uint32_t m_speed;

protected:
	//The ID of the motor, this should correspond to the
	//PWM index (0-17) as specified in the Spider Robot documentation.
	//This is not needed by clients but is needed internally by the implementation.
	int m_nMotorID;

public:

	Motor(int motorId) {
		m_nMotorID = motorId;
		m_fAngle = 180.0;
		m_speed = 0;
	}

	virtual ~Motor(){}

	/**
	 * Puts the motor into the neutral, angle 0 position by
	 * using the specific subclass's Move method.
	 */
	virtual void Reset(void) { 
		Move(0.0);
	}
	
	/**
	 * This must change the current motor's angle position;
	 * the behavior is implementation dependent and should be overridden.
	 */
	virtual void Move(float fAngle) {
		if (fAngle > DEGREE_MAX) {
			fAngle = DEGREE_MAX;
		} else if (fAngle < DEGREE_MIN) {
			fAngle = DEGREE_MIN;
		}
		m_fAngle = fAngle;
	}

	/**
	 * @return true when this motor is prepared to receive
	 * a new SetSpeed or Move method call; otherwise false.
	 * 
	 * The specific behavior of a Motor if IsReady() returns
	 * false and it is issued a SetSpeed() or Move() call
	 * is implementation specific.
	 */
	virtual bool IsReady() = 0;

        virtual float GetfAngle(){ return (m_fAngle == -0.0) ? 0.0f :  m_fAngle; }
  
	virtual uint32_t GetSpeed(){ return m_speed; }

  
	/**
	 * Compute an appropriate delay value based on the given speed.
	 * Then, use the implementation specific UpdateMotorDelay method
	 * to actually update the delay and update the real device.
	 * 
	 * This should be overriden by subclasses to actually update the motor.
	 * 
	 * @param speed - a number between SPEED_MIN and SPEED_MAX,
	 * if an out of bounds value is provided, then it is interpreted
	 * as either the upper or lower bound.
	 */
	virtual void SetSpeed(int speed) {
		if (speed > SPEED_MAX) {
			speed = SPEED_MAX;
		} else if (speed < SPEED_MIN) {
			speed = SPEED_MIN;
		}
		m_speed = speed;
	}

};
#endif
