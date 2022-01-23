#include <Memory.h>
#include <KernelUtil.h>

size_t Memory::Pages::GetPhysicalAddress(size_t virtualAddr) {
    UInt16 pml4Index = (virtualAddr >> Pml4BitShift) & PmBitMask;
    UInt16 pml3Index = (virtualAddr >> Pml3BitShift) & PmBitMask;
    UInt16 pml2Index = (virtualAddr >> Pml2BitShift) & PmBitMask;
    UInt16 pml1Index = (virtualAddr >> Pml1BitShift) & PmBitMask;

    QWord ***pml3 = PageTable[pml4Index];
    if (pml3 == nullptr) return 0;

    QWord **pml2 = pml3[pml3Index];
    if (pml2 == nullptr) return 0;

    QWord *pml1 = pml2[pml2Index];
    if (pml1 == nullptr) return 0;

    return PTEntry(pml1[pml1Index]).Address + (virtualAddr & OffsetBitMask);
}

void Memory::Pages::Map(size_t virtualAddr, PTEntry data) {
    if (data.Address % 4096 != 0) return;
    if (virtualAddr % 4096 != 0) return;

    UInt16 pml4Index = (virtualAddr >> Pml4BitShift) & PmBitMask;
    UInt16 pml3Index = (virtualAddr >> Pml3BitShift) & PmBitMask;
    UInt16 pml2Index = (virtualAddr >> Pml2BitShift) & PmBitMask;
    UInt16 pml1Index = (virtualAddr >> Pml1BitShift) & PmBitMask;

    QWord ***pml3 = PageTable[pml4Index];
    if (pml3 == nullptr) return;

    QWord **pml2 = pml3[pml3Index];
    if (pml2 == nullptr) return;

    QWord *pml1 = pml2[pml2Index];
    if (pml1 == nullptr) return;

    pml1[pml1Index] = data;
}

void Memory::Pages::Init() {
    asm volatile("mov %%cr3, %0" : "=r" (PageTable));
    PageTable = (size_t ****)(((size_t)PageTable << PageTableAddressBitShift) & PageTableAddressBitMask);
}

Memory::MemoryMapEntry Memory::MemoryMapT::operator[](size_t) const {

}
