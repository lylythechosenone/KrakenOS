#ifndef KRAKENOS_MEMORY_H
#define KRAKENOS_MEMORY_H

#include <KernelTypes.h>
#include <Container.h>

namespace Memory {
    enum class MemoryMapEntryType {
        KERNEL,
        BOOTLOADER,
        USER,
        AVAILABLE
    };

    struct MemoryMapEntry {
        size_t Base;
        size_t Length;
        MemoryMapEntryType Type;
        bool Present;
    } __attribute__((__packed__));

    class MemoryMapT {
        Container<MemoryMapEntry> Entries;

        MemoryMapEntry operator[](size_t) const;
    };

    MemoryMapT MemoryMap;

    namespace Pages {
        struct PTEntry {
            bool ExecuteDisable: 1;
            Byte ProtectionKey: 4;
            Byte Available: 7;
            size_t Address: 40;
            Byte Available2: 3;
            bool Global: 1;
            bool PageAttributeTable: 1;
            bool Dirty: 1;
            bool Accessed: 1;
            bool CacheDisable: 1;
            bool WriteThrough: 1;
            bool Supervisor: 1;
            bool WriteEnable: 1;
            bool Present: 1;

            operator QWord() const {
                QWord tmp = 0;
                tmp |= ((size_t)ExecuteDisable << 63);
                tmp |= ((size_t)ProtectionKey << 59);
                tmp |= ((size_t)Available << 55);
                tmp |= ((size_t)Address << 12);
                tmp |= ((size_t)Available2 << 9);
                tmp |= ((size_t)Global << 8);
                tmp |= ((size_t)PageAttributeTable << 7);
                tmp |= ((size_t)Dirty << 6);
                tmp |= ((size_t)Accessed << 5);
                tmp |= ((size_t)CacheDisable << 4);
                tmp |= ((size_t)WriteThrough << 3);
                tmp |= ((size_t)Supervisor << 2);
                tmp |= ((size_t)WriteEnable << 1);
                return tmp;
            }

            PTEntry(size_t data) {
                ExecuteDisable = (data & (1 << 63)) > 0;
                ProtectionKey = (data & (0b1111 << 59)) >> 59;
                Available = (data & (0b111 << 55)) >> 55;
                Address = (data & (0b111111111111 << 12)) >> 12;
                Available2 = (data & (0b111 << 9)) >> 9;
                Global = (data & (1 << 8)) != 0;
                PageAttributeTable = (data & (1 << 7)) != 0;
                Dirty = (data & (1 << 6)) != 0;
                Accessed = (data & (1 << 5)) != 0;
                CacheDisable = (data & (1 << 4)) != 0;
                WriteThrough = (data & (1 << 3)) != 0;
                Supervisor = (data & (1 << 2)) != 0;
                WriteEnable = (data & (1 << 1)) != 0;
                Present = (data & (1 << 0)) != 0;
            }
        } __attribute((__packed__));

        static QWord ****PageTable;

        constexpr UInt64 Pml4BitShift = 39;
        constexpr UInt64 Pml3BitShift = 30;
        constexpr UInt64 Pml2BitShift = 21;
        constexpr UInt64 Pml1BitShift = 12;

        constexpr UInt64 PmBitMask = 0x1FF;
        constexpr UInt64 OffsetBitMask = 0xFFF;

        constexpr UInt64 PageTableAddressBitShift = 3;
        constexpr UInt64 PageTableAddressBitMask = 0xFFFFFFFFFF;

        void Init();
        void Map(size_t virtualAddr, PTEntry data);
        size_t GetPhysicalAddress(size_t virtualAddr);
    }
}

#endif //KRAKENOS_MEMORY_H
