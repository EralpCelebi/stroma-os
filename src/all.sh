arch="i386"
root=$PWD
build=$PWD/build
libs=$build/libs
name="matrix-kernel"

cc="$arch-elf-gcc"
ld="$arch-elf-gcc"
ar="$arch-elf-ar"
as="nasm"

kernel="$root/kernel/$arch"
iso="$build/iso"
ind="independent"

modules="$arch/tty $ind/io $ind/libk $ind/serial $arch/idt $arch/gdt"
includes="../kernel/$arch $modules"

# Reset
reset='\033[0m'       # Text Reset

# Regular Colors
black='\033[0;30m'        # Black
red='\033[0;31m'          # Red
green='\033[0;32m'        # Green
yellow='\033[0;33m'       # Yellow
blue='\033[0;34m'         # Blue
purple='\033[0;35m'       # Purple
cyan='\033[0;36m'         # Cyan
white='\033[0;37m'        # White

libldflags=""
for module in $modules
do
    libldflags+=" -l${module##*/} "
done

ccflags=" -c -fdiagnostics-color=always -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$build/include/"
ldflags=" -ffreestanding -O2 -nostdlib -T$kernel/config/linker.ld -L$libs/ -lgcc $libldflags"
asflags=" -felf32 "

function install_headers() {
    for module in $includes
    do
        echo -e "${blue}Installing headers from: $module ${reset}"
        for file in modules/$module/include/*
        do
            if [ -e $file ]
            then
                cp -r $file $build/include/
            fi

            if [ -d $file ]
            then
                cp -r $file $build/include/
            fi
        done
    done
}

function compile_modules() {
    for module in $modules
    do
        msrc="modules/${module}/src"
        for file in $msrc/*.asm
        do
            if [ -e $file ]
            then
                echo -e "$red Assembling: ${module##*/}:$file $reset"
                $as $asflags $file
                #mv "${file%.*}.o" $local/obj/
            fi
        done

        for file in $msrc/*.c
        do
            if [ -e $file ]
            then
                echo -e "$green Compiling: ${module##*/}:$file $reset"
                $cc $ccflags $file -o "${file%.*}.o"
                #$mv "${file%.*}.o" $local/obj/
            fi
        done

        echo -e "$yellow Packing: lib${module##*/}.a $reset"
        $ar rcs lib${module##*/}.a $msrc/*.o
        mv lib${module##*/}.a $libs
        mv $msrc/*.o $build/obj/
    done        
}

function clean() {
    echo -e "$red Cleaning. $reset"
    rm $build/obj/*.o
    rm $build/libs/*.a
    rm -rf $build/include/*
    rm $iso/boot/*.bin
    rm $iso/boot/grub/grub.cfg
    rm $iso/boot/grub/menu.lst
    rm $iso/boot/grub/eltorito
    rm os.iso
}

function link() {
    echo  -e " ${purple}Linking: $name${reset}"
    echo  -e "$ld $ldflags $build/obj/*.o -o $iso/boot/kernel.bin"
    $ld $build/obj/*.o $ldflags -o $iso/boot/kernel.bin
}

function compile_kernel() {
    for file in $kernel/bootstrap/*.asm
    do
        if [ -e $file ]
        then
            echo -e "$red Assembling: $file $reset"
            $as $asflags $file
            mv "${file%.*}.o" $build/obj/
        fi
    done

    for file in $kernel/src/*.asm
    do
        if [ -e $file ]
        then
            echo -e "$red Assembling: $file $reset"
            $as $asflags $file
            mv "${file%.*}.o" $build/obj/
        fi
    done

    for file in $kernel/src/*.c
    do
        if [ -e $file ]
        then
            echo -e "$green Compiling: $file $reset"
            $cc $ccflags $file -o "${file%.*}.o"
            mv "${file%.*}.o" $build/obj/
        fi
    done
}

function pack() {
    echo -e "$yellow Packing: $name with $modules $reset"
    echo -e "Copying: grub.cfg"
    cp $kernel/config/grub.cfg $iso/boot/grub/grub.cfg
    echo -e "$yellow Packing: os.iso $reset"
    grub-mkrescue -o os.iso $iso 2> /dev/null
}

function pack_fallback() {
    echo -e "$yellow Packing: $name with $modules $reset"
    echo -e "$green Copying: menu.lst $reset"
    cp $kernel/config/menu.lst $iso/boot/grub/menu.lst
    echo -e "$green Copying: Grub binary $reset"
    cp $kernel/config/eltorito $iso/boot/grub/eltorito
    echo -e "$yellow Packing: os.iso $reset"
    genisoimage -R                              \
                -b boot/grub/eltorito           \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A StromaOS                     \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o os.iso                       \
                $iso
}

#clean;
install_headers;
compile_modules;
compile_kernel;
link;
pack;
   
#pack_fallback;