#ifndef HW_TEST_ROM_H
#define HW_TEST_ROM_H

#include "hw/sysbus.h"
#include "qom/object.h"

#define TYPE_TEST_ROM "TEST_ROM"

typedef struct brState brState;
DECLARE_INSTANCE_CHECKER(brState, TEST_ROM, TYPE_TEST_ROM)

struct brState
{
    MemoryRegion mmio;
    unsigned char Reg[6]; //{'N','T','H','U','C','S'};
};

brState *br_create(MemoryRegion *address_space, hwaddr base);

#endif //HW_TEST_ROM_H

