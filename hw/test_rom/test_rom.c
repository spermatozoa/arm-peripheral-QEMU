
#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/log.h"
#include "hw/sysbus.h"
#include "chardev/char.h"
#include "hw/hw.h"
#include "hw/irq.h"
#include "hw/test_rom/test_rom.h"

static uint64_t br_read(void *opaque, hwaddr addr, unsigned int size)
{
    brState *s = opaque;
    qemu_log_mask(LOG_GUEST_ERROR, "%s: read: addr=0x%x size=%d\n",
                  __func__, (int)addr,size);
    return s->Reg[addr];
}

static void br_write(void *opaque, hwaddr addr, uint64_t val64, unsigned int size)
{
    /*dummy code for future development*/
    brState *s = opaque;
    uint32_t value = val64;
    unsigned char ch = value;
    // (void)s;
    // (void)ch;
    qemu_log_mask(LOG_GUEST_ERROR, "%s: write: addr=0x%x v=0x%x\n",
                  __func__, (int)addr, (int)value);
    s->Reg[addr] = ch;
}

static void br_init(brState *s){
    s->Reg[0]='N';
    s->Reg[1]='T';
    s->Reg[2]='H';
    s->Reg[3]='U';
    s->Reg[4]='C';
    s->Reg[5]='S';
}

static const MemoryRegionOps br_ops = {
    .read = br_read,
    .write = br_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 1,
        .max_access_size = 6}
};

brState *br_create(MemoryRegion *address_space, hwaddr base)
{
    brState *s = g_malloc0(sizeof(brState));
    br_init(s);
    memory_region_init_io(&s->mmio, NULL, &br_ops, s, TYPE_TEST_ROM, 32);
    memory_region_add_subregion(address_space, base, &s->mmio);
    return s;
}