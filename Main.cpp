#include "spider_os.h"
#include <iostream>
#include <stdint.h>
#include <string.h>
#include "Spider.h"
#include "Command.h"
#include "CommandReader.h"
#include "StdInReader.h"

#include <time.h>
using namespace std;
int main(int argc, char *argv[])
{
        Spider spider;
		spider.Standup();
	//TODO initialize the spider and then have it stand up
	CommandReader* inputReader;
	inputReader = new StdInReader();
	std::cerr << "Initializing Spider Speed to 50" << std::endl;
	
	std::cerr << "Waiting for Command..." << std::endl;
	//TODO receive commands and carry them out using the spider
	//repeatedly until a STOP command is received
	int command;
	//while (true){
		cin >> command;
		if (command == 1){
			spider.Forward();
		}
	//}
	delete inputReader;
	return 0;
}
