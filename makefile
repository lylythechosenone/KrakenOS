LIMINE_VERSION=2.74.5
KRAKENOS_VERSION=0.1.0
CC=x86_64-elf-gcc
LD=x86_64-elf-ld

default: all

all: iso qemu-run

qemu-run: clean
	qemu-system-x86_64 KrakenOS-$(KRAKENOS_VERSION).iso

iso: limine kernel
	mkdir iso
	mkdir iso/boot
	mv limine-$(LIMINE_VERSION)-binary/limine-cd.bin iso/boot/
	mv limine-$(LIMINE_VERSION)-binary/limine-eltorito-efi.bin iso/boot/
	mv limine-$(LIMINE_VERSION)-binary/limine.sys iso/boot/
	cp limine.cfg iso/boot/
	mv kernel iso/boot/
	xorriso -as mkisofs -b boot/limine-cd.bin \
	-no-emul-boot -boot-load-size 4 -boot-info-table \
	--efi-boot boot/limine-eltorito-efi.bin \
	-efi-boot-part --efi-boot-image --protective-msdos-label \
	iso/ -o KrakenOS-$(KRAKENOS_VERSION).iso
	limine-install KrakenOS-$(KRAKENOS_VERSION).iso
	make clean

limine:
	curl -L -o limine-binary.zip https://github.com/limine-bootloader/limine/archive/refs/tags/v$(LIMINE_VERSION)-binary.zip
	unzip -o limine-binary.zip > /dev/null
ifeq ("$(SUDO_PASSWORD)","")
	cd limine-$(LIMINE_VERSION)-binary && \
	sudo -S make install
else
	cd limine-$(LIMINE_VERSION)-binary && \
	echo $(SUDO_PASSWORD) | sudo -S make install
endif

kernel:
	$(CC) -I./ -std=c++2a -ffreestanding -mcmodel=kernel -c kernel.cpp Port.cpp KernelUtil.cpp Memory.cpp Container.cpp
		-DVERSION="\"$(KRAKENOS_VERSION)\""
	$(LD) -Tlinker.ld -o kernel *.o

clean:
	rm -rf limine-* kernel *.o iso