#ifndef __CMD_H__
#define __CMD_H__
typedef enum {
        CMD_FORDWARD,  //Take one step forwards
	CMD_BACKWARD,  //Take one step backwards
	CMD_TURN_RIGHT,//Reset the spider's position and then rotate clockwise
	CMD_TURN_LEFT, //Reset the spider's position and then rotate counterclockwise
	CMD_SPDUP,  //Increment the spider's speed by 10
	CMD_SPDDWN, //Decrement the spider's speed by 10
	CMD_STOP,   //Terminate the spider application
	CMD_IDLE //Do nothing, ignore the command
} COMMAND_ID;
#endif
