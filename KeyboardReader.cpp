#include "CommandReader.h"

/**
 * This implements the CommandReader interface using a USB keyboard
 * that is accessed via the linux Input Event file API.
 */
class KeyboardReader : public CommandReader {

    COMMAND_ID keyToCmd(int keycode) {
        //TODO fill this in as a helper method
        //to map keys to commands (e.g., KEY_UP to CMD_FORWARD)
    }
public:

    KeyboardReader(char* dev) {
        //TODO instantiate a Keyboard and save a pointer to it
    }

    virtual ~KeyboardReader() {
        //TODO de-allocate the Keyboard object created in the constructor
    }

    COMMAND_ID getNextCommand() {
        //TODO implement this according to specification in CommandReader.h
    }

    COMMAND_ID getNextCommand(uint32_t after) {
        //TODO implement this according to specification in CommandReader.h
    }
};
