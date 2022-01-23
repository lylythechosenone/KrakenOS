#include <KernelUtil.h>
#include <KernelTypes.h>

void memcpy(void *dest, void *src, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        ((UInt8 *)dest)[i] = ((UInt8 *)src)[i];
    }
}

void memset(void *dest, UInt8 value, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        ((UInt8 *)dest)[i] = value;
    }
}