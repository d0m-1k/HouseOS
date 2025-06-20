#!/usr/bin/fish

nasm -f elf32 src/boot.asm -o build/boot.o

for file in (find src/kernel -type f -name "*.c")
	set f (string replace -a / _ (string split '.' (string replace src/kernel/ '' $file))[1])
	gcc -nostdlib -ffreestanding -m32 --target=x86_64 -c $file -o build/$f.o -Isrc/kernel
end

ld -m elf_i386 -T src/linker.ld -o build/kernel.bin build/*.o

rm build/*.o -f

qemu-system-x86_64 -kernel build/kernel.bin -display vnc=:0
