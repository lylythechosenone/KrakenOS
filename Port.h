#ifndef KRAKENOS_PORT_H
#define KRAKENOS_PORT_H

#include <KernelTypes.h>

namespace Port {
    void write(Word address, Byte data);
    Byte read(Word address);

    //void write(Word address, String data);
};

#endif //KRAKENOS_PORT_H
