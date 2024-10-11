/*
 * SpiderLeg.h
 *
 */

#ifndef SPIDERLEG_H_
#define SPIDERLEG_H_

#include "Motor.h"
#include "ServoMotor.cpp"
#include "spider_os.h"

class SpiderLeg {
public:
        //You can use this enumeration to refer to specific joints by 'name' in your code.
        //These are public so they can be referenced via the type: SpiderLeg::JOINT_ID in other files.
        //(See Spider.h for an example of this)
	//
	//Hint: Enums are always implemented in C++ as integers, so you can use them to
	//define or index into arrays.  
	typedef enum {
		Hip=0,
		Knee,
		Ankle,
		JOINT_NUM //This will equal the # of other kinds of JOINTS (so 3)
	} JOINT_ID;
 
// MMap* mmio = new MMap;

        //TODO deine the necessary members of the SpiderLeg class.
	//If some members are user-defined objects, remember to store a 'pointer' to them
	//instead of just storing the objects whole (e.g., MyObj* my_member;)
  //Motor* motors[JOINT_NUM]; 
  ServoMotor* motors[JOINT_NUM];

        //TODO modify the constructor to take any arguments you need to initialize a spider leg
        SpiderLeg(MMap* mmio, int first, int second, int third);
	virtual ~SpiderLeg();

        /**
	 * Initialize a leg by setting the duty cycle of each motor to 0.0 degrees.
	 *
	 * Additionally, set the speed of each motor to 50%.
	 */
  void Init();
    
    
    
        /**
	 * Move a specific joint to a specific angle.
	 * @param JointId - which joint in this leg to move
	 * @param fAngle - the angle (between -90 and 90) to move the motor to
	 */
	void MoveJoint(int JointID, float fAngle);
 
 
 
        /**
	 * Returns true when _all_ of the motors in this leg
	 * are ready for another angle setting (i.e., they have completed their last movement)
	 */

	bool IsReady();
 
 
 
 
 
  //TODO add any other methods (public or private) that you
  //need/wish to implement this class' functionality
};

#endif /* SPIDERLEG_H_ */
