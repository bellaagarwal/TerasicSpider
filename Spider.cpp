/*
 * Spider.cpp
 *
 *
 */

#include "spider_os.h"
#include <stdint.h>
#include <stdio.h>
#include "Spider.h"
#include<iostream>
#include "SpiderLeg.h"

using namespace std;

//Use these angles to implement basic movements
//And to return to the neutral  position
#define Knee_Up_Base 60   //Raised legs knee position
#define Knee_Down_Base 45 //Lowered legs knee position (neutral once standing up)
#define HipF_Base -20     //Neutral hip position for front legs
#define HipM_Base 0       //Neutral hip position for mid legs
#define HipB_Base 20      //Neutral hip position for back legs
#define Ankle_Base 45     //Neutral ankle position
#define Stand_Up_Knee_Start 90 //High angle to begin slowly standing up
#define Stand_Up_Knee_End 45 //Final angle after standup completed
//The following should be added to the appropriate 'Hipx_Base' angle to get final
//positions after walking or turning
#define Walk_Hip_Change 20 //Degrees to move hip forwards or backwards from neutral when walking
#define Rotate_Hip_Change 30 //Degrees to rotate hips from neutral when turning

Spider::Spider()
{
  mmio = new MMap;
  //TODO implement the constructor
  //that initializes the members
  //of this object to the correct values  
  legs[LEG_RF] = new SpiderLeg(mmio, 0, 1, 2);
  legs[LEG_RM] = new SpiderLeg(mmio, 3, 4, 5);
  legs[LEG_RB] = new SpiderLeg(mmio, 6, 7, 8);
  legs[LEG_LF] = new SpiderLeg(mmio, 9, 10, 11);
  legs[LEG_LM] = new SpiderLeg(mmio, 12, 13, 14);
  legs[LEG_LB] = new SpiderLeg(mmio, 15, 16, 17);
  int lastStep = 0;
  
  Init();
}

Spider::~Spider()
{
  //TODO implement the destructor
  //Destroy any heap-allocated objects
  //that this object has references to
  delete legs[LEG_RF];
  delete legs[LEG_RM];
  delete legs[LEG_RB];
  delete legs[LEG_LF];
  delete legs[LEG_LM];
  delete legs[LEG_LB];
  delete mmio;
}

bool Spider::Init()
{
  //TODO initialize all of the joint servos to 0.0 degrees.
  //For a smoother initialization, wait an extra 100ms between
  //each two motor initializations.

  /** Example code for how to wait 100ms:
   *  uint32_t Start_Time;
   *  Start_Time = OS_GetTickCount() + 100;
   *  while (OS_GetTickCount() < Start_Time) {}
   */
   
   for(int i = 0; i < 6; i++){
     legs[i]->Init();
   uint32_t Start_Time;
   Start_Time = OS_GetTickCount() + 100;
   while (OS_GetTickCount() < Start_Time) {}
   }
   Standup();

  

  return false;
}

void Spider::WaitReady()
{
  //TODO complete this!
  while(true){
  if(!IsReady()){
    continue;
  }else{
    break;
  }}
  return;
}

bool Spider::IsReady()
{
  bool ready = true;
  //TODO complete this!
  for(int i = 0; i < LEG_NUM; i++) {
    if(legs[i]->IsReady() == false) {
      ready = false;
    }
  }
  return ready;
}

void Spider::turnRight() {}

void Spider::turnLeft() {
}

void Spider::Forward(){
  if(lastStep == 1){
      ForwardLTripod();
  }else if(lastStep == 0){
      ForwardRTripod();
  }
    }

void Spider::RotateClockwise() {
  WaitReady();
  MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
  WaitReady();
  MoveTripod(TRIPOD1, SpiderLeg::Hip, -1 * Rotate_Hip_Change, Rotate_Hip_Change, -1 * Rotate_Hip_Change);
  WaitReady();
  MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base);
  WaitReady();
  MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
  WaitReady();
    MoveTripod(TRIPOD2, SpiderLeg::Hip, Rotate_Hip_Change, -1 * Rotate_Hip_Change, Rotate_Hip_Change);
    WaitReady();
    MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base);
    WaitReady();
    
}

void Spider::RotateCounter() {
  WaitReady();
  MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
  WaitReady();
  MoveTripod(TRIPOD1, SpiderLeg::Hip, Rotate_Hip_Change, -1 * Rotate_Hip_Change, Rotate_Hip_Change);
  WaitReady();
  MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base);
  WaitReady();
  MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
  WaitReady();
    MoveTripod(TRIPOD2, SpiderLeg::Hip, -1 * Rotate_Hip_Change, Rotate_Hip_Change, -1 * Rotate_Hip_Change);
    WaitReady();
    MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base);
    WaitReady();

}

void Spider::ForwardRTripod() {
//call move tripod
WaitReady();
MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
WaitReady();
MoveTripod(TRIPOD1, SpiderLeg::Hip, Walk_Hip_Change, Walk_Hip_Change, Walk_Hip_Change);
WaitReady();
MoveTripod(TRIPOD2, SpiderLeg::Hip, -1 * Walk_Hip_Change, -1 * Walk_Hip_Change, -1 * Walk_Hip_Change);
WaitReady();
MoveTripod(TRIPOD1, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base);
lastStep = 1;


}

void Spider::ForwardLTripod() {
WaitReady();
MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Up_Base, Knee_Up_Base, Knee_Up_Base);
WaitReady();
MoveTripod(TRIPOD2, SpiderLeg::Hip, Walk_Hip_Change, Walk_Hip_Change, Walk_Hip_Change);
WaitReady();
MoveTripod(TRIPOD1, SpiderLeg::Hip, -1 * Walk_Hip_Change, -1 * Walk_Hip_Change, -1 * Walk_Hip_Change);
WaitReady();
MoveTripod(TRIPOD2, SpiderLeg::Knee, Knee_Down_Base, Knee_Down_Base, Knee_Down_Base);
lastStep = 0;
}

void Spider::Back() {
//call move tripod
}


  void Spider::Stop(){
  return;
  }

  void Spider::speedUp() {
  }
  void Spider::slowDown() {
  }
  void Spider::Idle() {
  }
  
  

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
void Spider::MoveTripod(TRIPOD_ID Tripod, SpiderLeg::JOINT_ID Joint, float AngleF, float AngleM, float AngleB)
{

cout << "Tripod" << endl;

  
  if(Tripod == TRIPOD1) {
    if(Joint == SpiderLeg::Hip) {
        legs[LEG_RF]->MoveJoint(0, -1 * AngleF);
        legs[LEG_LM]->MoveJoint(0, AngleM);
        legs[LEG_RB]->MoveJoint(0, -1 * AngleB);
    }
    if(Joint == SpiderLeg::Knee) {
        legs[LEG_RF]->MoveJoint(1, -1 * AngleF);
        legs[LEG_LM]->MoveJoint(1, AngleM);
        legs[LEG_RB]->MoveJoint(1, -1 * AngleB);
    }
    if(Joint == SpiderLeg::Ankle) {
        legs[LEG_RF]->MoveJoint(2, -1 * AngleF);
        legs[LEG_LM]->MoveJoint(2, AngleM);
        legs[LEG_RB]->MoveJoint(2, -1 * AngleB);
    }
  //RF LM RB
  }
  if(Tripod == TRIPOD2) {
      if(Joint == SpiderLeg::Hip) {
        legs[LEG_LF]->MoveJoint(0, AngleF);
        legs[LEG_RM]->MoveJoint(0, -1 * AngleM);
        legs[LEG_LB]->MoveJoint(0, AngleB);
    }
    if(Joint == SpiderLeg::Knee) {
        legs[LEG_LF]->MoveJoint(1, AngleF);
        legs[LEG_RM]->MoveJoint(1, -1 * AngleM);
        legs[LEG_LB]->MoveJoint(1, AngleB);
    }
    if(Joint == SpiderLeg::Ankle) {
        legs[LEG_LF]->MoveJoint(2, AngleF);
        legs[LEG_RM]->MoveJoint(2, -1 * AngleM);
        legs[LEG_LB]->MoveJoint(2, AngleB);
    }
  //LF RM LB
  }
  //TODO complete this method.
}



//This one has been provided for you!
void Spider::Standup()
{
  cout << "Spider Standup" << endl;
	int i;
	////////////////////////
	//// Stand up  -- Adjust Hip
WaitReady();
	  //TODO set Leg i's Hip joint to the neutral angle
	  //(HipF_Base for front leg, HipM_Base for mid leg, HipB_Lbase for back leg)
    // legs[i]->MoveJoint(Hip, HipM_Base);
	//}
 legs[LEG_RF]->MoveJoint(0, -1 * HipF_Base);
 legs[LEG_RM]->MoveJoint(0, -1 * HipM_Base);
 legs[LEG_RB]->MoveJoint(0, -1 * HipB_Base);
 legs[LEG_LF]->MoveJoint(0, HipF_Base);
 legs[LEG_LM]->MoveJoint(0, HipM_Base);
 legs[LEG_LB]->MoveJoint(0, HipB_Base);
 
	WaitReady();
	//// Stand up -- Adjust Ankle
	for (i = 0; i < LEG_NUM; i++) {
	  //TODO set Leg i's Ankle to Ankle_Base
     if(i<3){
       legs[i]->MoveJoint(2, -1 * Ankle_Base);
       }else{
          legs[i]->MoveJoint(2, Ankle_Base); 
          } 
	}
	WaitReady();       
	////////////////////////
	//// Stand up  -- Bring all knees up and then slowly bring them down
	float KneeAngle = Stand_Up_Knee_Start;
	while (KneeAngle >= Stand_Up_Knee_End)
	{
		for (i = 0; i < LEG_NUM; i++)
		{
       if(i<3){
           legs[i]->MoveJoint(1, -1 * KneeAngle);
         }
		  //TODO set Leg i's Knee to KneeAngle
        else {
        legs[i]->MoveJoint(1, KneeAngle);
        }
		}
		WaitReady();
		KneeAngle -= 5.0;
	//This outer loop ensures that all of the legs stand up simultaneously(ish)		
	}
}

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
         
void Spider::Reset()
{
WaitReady();
  //TODO implement moving the spider into its neutral leg position;
  //Should only be called _after_ standing the spider up,
  //otherwise, the spider may not stand up _safely_
  //Spider.Standup();

	  //TODO set Leg i's Hip joint to the neutral angle
	  //(HipF_Base for front leg, HipM_Base for mid leg, HipB_Lbase for back leg)
     cout << "Spider Reset" << endl;
 legs[LEG_RF]->MoveJoint(0, -1 * HipF_Base);
 legs[LEG_RM]->MoveJoint(0, -1 * HipM_Base);
 legs[LEG_RB]->MoveJoint(0, -1 * HipB_Base);
 legs[LEG_LF]->MoveJoint(0, HipF_Base);
 legs[LEG_LM]->MoveJoint(0, HipM_Base);
 legs[LEG_LB]->MoveJoint(0, HipB_Base);
     
	WaitReady();
	//// Stand up -- Adjust Ankle
	for (int i = 0; i < LEG_NUM; i++) {
	  //TODO set Leg i's Ankle to Ankle_Base	  
     legs[i]->MoveJoint(2, Ankle_Base);  
	}
	WaitReady();       
}


//TODO put implementations of other methods you define for the Spider class here!
