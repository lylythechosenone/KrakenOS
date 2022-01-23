#include <stivale2.h>
#include <KernelTypes.h>
#include <KernelUtil.h>
#include <Memory.h>

static UInt8 stack[8192];

static stivale2_header_tag_terminal terminal_hdr_tag = {
        .tag = {
                .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
                .next = 0
        },
        .flags = 0
};

static stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
        .tag = {
                .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
                .next = (UInt64)&terminal_hdr_tag
        },
        .framebuffer_width  = 0,
        .framebuffer_height = 0,
        .framebuffer_bpp    = 0
};

__attribute__((section(".stivale2hdr"), used))
static stivale2_header stivale_hdr = {
        .entry_point = 0,
        .stack = (uintptr_t)stack + sizeof(stack),
        // Bit 1, if set, causes the bootloader to return to us pointers in the
        // higher half, which we likely want since this is a higher half kernel.
        // Bit 2, if set, tells the bootloader to enable protected memory ranges,
        // that is, to respect the ELF PHDR mandated permissions for the executable's
        // segments.
        // Bit 3, if set, enables fully virtual kernel mappings, which we want as
        // they allow the bootloader to pick whichever *physical* memory address is
        // available to load the kernel, rather than relying on us telling it where
        // to load it.
        // Bit 4 disables a deprecated feature and should always be set.
        .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
        .tags = (uintptr_t)&framebuffer_hdr_tag
};

void *StivaleGetTag(stivale2_struct *stivale2_struct, UInt64 id) {
    auto *current_tag = (stivale2_tag *)stivale2_struct->tags;
    while (current_tag != nullptr) {
        if (current_tag->identifier == id) {
            return current_tag;
        }
        current_tag = (stivale2_tag *)current_tag->next;
    }
    return nullptr;
}

extern "C" [[noreturn]] void Start(stivale2_struct *stivale2_struct);

void Start(stivale2_struct *stivale2_struct) {
    auto term_str_tag = (stivale2_struct_tag_terminal *) StivaleGetTag(stivale2_struct,
                                                                       STIVALE2_STRUCT_TAG_TERMINAL_ID);

    if (term_str_tag == nullptr) {
        while (true) {
            asm("hlt");
        }
    }

    auto term_write = (void (*)(const char *, size_t))term_str_tag->term_write;

    term_write("KrakenOS " VERSION "\n", 15);
    term_write("Kernel loaded.\n", 15);
    term_write("Initializing page table...", 26);
    Memory::Pages::Init();
    term_write("done.\n", 6);

    term_write("Initializing memory map...", 26);

    while (true) {
        asm("hlt");
    }
}