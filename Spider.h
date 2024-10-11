/*
 * Spider.h
 * An object representing the control and
 * status of a Hexapod spider robot.
 */

#ifndef SPIDER_H_
#define SPIDER_H_

#include <stdint.h>
#include <stdio.h>
#include "spider_os.h"
#include "SpiderLeg.h"

class Spider {

private:
	//You can use these enums anywhere inside the Spider class to make
	//specifying legs or tripods simpler; these identifiers shouldn't be
	//needed by clients of Spider and so they are marked as 'private' members
	//(this means they should only appear in the type signatures or bodies of
	//'private' methods)
	//
	//Hint: Enums are always implemented in C++ as integers, so you can use them to
	//define or index into arrays.
	MMap* mmio;
	typedef enum {
		LEG_RF,
		LEG_RM,
		LEG_RB,
		LEG_LF,
		LEG_LM,
		LEG_LB,
		LEG_NUM //This will equal the # of other kinds of LEGS (so 6)
	} LEG_ID;

	typedef enum {
		TRIPOD1,    //RF LM RB
		TRIPOD2,	//LF RM LB
		TRIPOD_NUM //This will equal the # of other kinds of TRIPODS (so 2)
	} TRIPOD_ID;

	//TODO deine the necessary members of the Spider class.
	//If some members are user-defined objects, remember to store a 'pointer' to them
	//instead of just storing the objects whole (e.g., MyObj* my_member;)
	//
	//Hint: You may want to use fixed-size array to store the references to the leg objects
	//to make accessing a given leg much simpler.
 SpiderLeg* legs[LEG_NUM];

 
public:
	//Constructor/Destructor - these must be public
	Spider();
	virtual ~Spider();
  int lastStep;
        /**
	 * Initialize each of the spider's legs via the initialization procedure described in SpiderLeg.h
	 *
	 * No other Spider methods should be called _before_ this one is called.
	 * @return true if this method completes successfully, false if an error is encountered
	 */
   
	bool Init();
 
        /**
	 * Move the Spider's legs to the 'neutral' position:
	   - Raise a leg by moving its knee, move it to its neutral hip position (see below) and neutral ankle position
	   - Wait for the above movement to complete
	   - Lower the leg by moving its knee
	   - Repeat for all other legs
	   -Neutral Hip Positions:
	   - Front legs facing 20 degrees back from 0 (they will still point forwards)
	   - Mid legs facing 0 degrees (sideways)
	   - Back legs facing 20 degrees forwards from 0 (they will still point backwards)
         */  
         
	void Reset();
 

 
        /**
	 * Safely stand the spider up from the ground so that the chassis is elevated.	 
         */
	void Standup();
 
        /**
	 * It is IMPERATIVE that the spider's motors do not receive conflicting
	 * commands while it is still in motion; the PWM motor control circuit
	 * has an interface for querying whether or not the motor is ready for a new command.
	 *
	 * This method should not return until _all_ of its motors are ready
	 * to receive a new command.
         */
	void WaitReady();
        //TODO add more methods that will be necessary to control the spider
        //to implement the commands described in Command.h
  void ForwardRTripod();
  void ForwardLTripod();
  void Forward();
  
  
  void Back();   
  void Stop();
  void turnRight();
  void turnLeft();
  void speedUp();
  void slowDown();
  void Idle();
  
  void RotateClockwise();
  void RotateCounter();


//The following are internal methods you should implement since their
//functionality will be useful for implementing the above functionality.
private:
        /**
	 * Determines if _all_ of the spider's servos are prepared to receive
	 * a new angle (i.e., they have completed their previous movement).
	 * @param bool - true if ready for a new command, else false
	 */
	bool IsReady(void);
        /**
	 * An internal method that moves a given joint (ankle/knee/hip) on all 3 legs
	 * of 1 tripod to the given 3 angle positions. This should not be exposed to clients
	 * but should be used by this object's other methods to implement higher-level movement abstractions.
	 * @param Tripod - which set of 3 legs to move
	 * @param Joint - which of the 3 joints to move (same joint is moved on all 3 legs)
	 * @AngleF - the destination angle for the front leg in the tripod
	 * @AngleM - the destination angle for the middle leg in the tripod
	 * @AngleB - the destination angle for the back leg in the tripod	 
         */
        void MoveTripod(TRIPOD_ID Tripod, SpiderLeg::JOINT_ID Joint,float AngleF,float AngleM,float AngleB);
};

#endif /* SPIDER_H_ */
