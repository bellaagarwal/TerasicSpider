/*
 * SpiderLeg.cpp
 *
 */

#include "spider_os.h"
#include "SpiderLeg.h"
#include "ServoMotor.cpp"
#include "MMap.h"
using namespace std;

SpiderLeg::SpiderLeg(MMap* mmio, int first, int second, int third) {
  //TODO implement the constructor
  //that initializes the members
  //of this object to the correct values

  motors[Hip] = new ServoMotor(mmio, first);
  motors[Knee] = new ServoMotor(mmio, second);
  motors[Ankle] = new ServoMotor(mmio, third);
  //Also you SHOULD modify the signature of the constructor to
  //take any arguments you need to do this
}


SpiderLeg::~SpiderLeg() {
  //TODO implement the destructor
  //Destroy any heap-allocated objects
  //that this object has references to
  for(int i = 0; i < JOINT_NUM; i++){
    delete motors[i];
  }
   
}


void SpiderLeg::Init() {
  //TODO implement initialization
  for(int i = 0; i < JOINT_NUM; i++) {
  motors[i]->Reset();

  }
  
    for(int i = 0; i < JOINT_NUM; i++) {
    motors[i]->SetSpeed(50);

  }

}

 

bool SpiderLeg::IsReady() {
  //TODO implement isready check
  for(int i = 0; i < JOINT_NUM; i++){
    if(motors[i]->IsReady() == false) {
      return false;
      }}
      
  return true;
}


void SpiderLeg::MoveJoint(int JointID, float fAngle) {
  //TODO implement moving a given joint's motor to a given angle
  motors[JointID]->Move(fAngle);
  cout << "moved joint " << JointID << endl;
  
}

