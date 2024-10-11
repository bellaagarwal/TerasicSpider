#include "CommandReader.h"
#include "spider_os.h"
#include <iostream>

/**
 * A blocking implementation of a command reader
 * that waits for a text-based user input coming from
 * the standard input (typically the terminal).
 * See CommandReader.h for descriptions on the methods.
 */
class StdInReader : public CommandReader
{

public:
    StdInReader(){};
    virtual ~StdInReader(){};  
    COMMAND_ID getNextCommand();
    COMMAND_ID getNextCommand(uint32_t after);
};
