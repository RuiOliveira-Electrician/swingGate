#ifndef IO_GLOBALS
#define IO_GLOBALS

struct Config
{
    uint8_t pin;
    uint8_t type;
    uint8_t initialState;
};

enum Output
{
    releOpen = RELEOPEN,
    releOpenLeft = RELEOPENLEFT,
    releOpenRight = RELEOPENRIGHT
};

extern const Config configs[6];

extern boolean memoryReleOpen, memoryReleOpenLeft, memoryReleOpenRight;

#endif