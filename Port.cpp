#include "Port.h"

Byte Port::read(Word address) {
    Byte toReturn;
    asm volatile("inb %1, %0" : "=a"(toReturn) : "Nd"(address));
    return toReturn;
}

void Port::write(Word address, Byte data) {
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(address));
}

/*void Port::write(Word address, String data) {
    for (int i = 0; i < data.length(); i++) {
        write(address, data[i]);
    }
}*/