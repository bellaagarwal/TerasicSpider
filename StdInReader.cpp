#include "StdInReader.h"

COMMAND_ID StdInReader::getNextCommand()
{
  char cmd_chr;
  std::cout << "Enter Next Command: ";
  std::cin >> cmd_chr;
  switch (cmd_chr)
    {
    case 'f':
      return CMD_FORDWARD;
    case 'b':
      return CMD_BACKWARD;
    case 'l':
      return CMD_TURN_LEFT;
    case 'r':
      return CMD_TURN_RIGHT;
    case 's':
      return CMD_STOP;
    case '8':
      return CMD_SPDUP;
    case '2':
      return CMD_SPDDWN;
    default:
      return CMD_IDLE;
    }
}
COMMAND_ID StdInReader::getNextCommand(uint32_t after)
{
  uint32_t curTime = OS_GetTickCount();
  if (curTime < after) {
    OS_SleepTicks(after - curTime);
  }
  return StdInReader::getNextCommand();
}
