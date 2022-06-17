echo "Compiling Minister..."

export PATH=$PATH:/usr/local/i686elfgcc/bin

echo "Compiling Misc Assembly Files..."

nasm asm/bootload.asm -f bin -o bin/asm/bootload.bin
nasm asm/sectrfix.asm -f bin -o bin/asm/sectrfix.bin
nasm asm/krnlentr.asm -f elf -o bin/asm/krnlentr.bin

echo "Compiling Kernel..."

i686-elf-g++ -ffreestanding -m32 -g -c kernel/base/base.cpp -o bin/kernel/base.o
i686-elf-g++ -ffreestanding -m32 -g -c kernel/base/hardwarecom.cpp -o bin/kernel/hardwarecom.o
i686-elf-g++ -ffreestanding -m32 -g -c kernel/base/hardwareinfo.cpp -o bin/kernel/hardwareinfo.o

i686-elf-g++ -ffreestanding -m32 -g -c kernel/time/datetime.cpp -o bin/kernel/datetime.o


i686-elf-g++ -ffreestanding -m32 -g -c kernel/io/out.cpp -o bin/kernel/out.o

i686-elf-g++ -ffreestanding -m32 -g -c kernel/main.cpp -o bin/kernel/main.o

echo "Compilng the rest of the OS..."

echo "Linking Kernel..."

i686-elf-ld -o bin/kernel/krnl.bin -Ttext 0x1000 bin/asm/krnlentr.bin bin/kernel/base.o bin/kernel/hardwarecom.o bin/kernel/datetime.o bin/kernel/hardwareinfo.o bin/kernel/out.o bin/kernel/main.o --oformat binary

echo "Linking the rest of the OS..."

echo "Linking Assembly Files..."

cat bin/asm/bootload.bin bin/kernel/krnl.bin bin/asm/sectrfix.bin  > bin/mnstros.bin

echo "Creating Floppy Disk Image"

dd if=/dev/zero of=bin/mnstros.img bs=512 count=2880
dd if=bin/mnstros.bin of=bin/mnstros.img seek=0 conv=notrunc

echo "Creating ISO"

cd bin

mkdir cdiso
cp mnstros.img cdiso

mkisofs -no-emul-boot -o mnstros.iso -V Minister -b mnstros.img cdiso

cd ..

echo "Cleaning up..."

cd bin
cd cdiso

rm mnstros.img

cd ..

rmdir cdiso

cd asm

rm bootload.bin krnlentr.bin sectrfix.bin

cd ..
cd kernel

rm  krnl.bin base.o hardwarecom.o datetime.o hardwareinfo.o out.o main.o

cd ..


cd ..

echo "Done, running..."

qemu-system-x86_64 -drive format=raw,file=bin/mnstros.bin,index=0 -m 32M
