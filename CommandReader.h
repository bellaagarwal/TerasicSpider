#ifndef __CMDREADER_H__
#define __CMDREADER_H__

#include "Command.h"
#include "spider_os.h"

class CommandReader {


public:
    CommandReader() {}
    virtual ~CommandReader() {}
    /**
     * Return the next command that has been queued up;
     * this is a blocking implementation, so if no commands have been
     * received, wait for one.
     * @return The next Spider Robot COMMAND_ID to execute
    */
    virtual COMMAND_ID getNextCommand() = 0;

    /**
     * Return the next command that has been queued up;
     * this is a blocking implementation, so if no commands have been
     * received, wait for one.
     * 
     * This implementation should skip any commands that arrived _before_
     * the given OS timestamp.
     * 
     * @param after - the timestamp (in OS ticks) before which we should
     * skip events.
     * @return The next Spider Robot COMMAND_ID to execute which arrived
     * after the timestamp _after_.
    */
    virtual COMMAND_ID getNextCommand(uint32_t after) = 0;
};


#endif
