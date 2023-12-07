#include "IO.h"

const Config configs[6] = {
    {BUTTONRADIO, INPUT, LOW},
    {BUTTONBOARD, INPUT, LOW},
    {GATEINFRARED, INPUT, LOW},
    {RELEOPEN, OUTPUT, LOW},
    {RELEOPENLEFT, OUTPUT, LOW},
    {RELEOPENRIGHT, OUTPUT, LOW}};

boolean memoryReleOpen = false;
boolean memoryReleOpenLeft = false;
boolean memoryReleOpenRight = false;