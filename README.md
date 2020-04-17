# StromaOS
Stroma OS is a monolithic kernel with an aim of providing a cross-platform and uniform operating system.

## Getting Started
___

### · Prerequisites
* A unix enviroment.
* `grub-mkrescue` or `genisoimage`
* A `gcc` cross-compiling toolchain.
* `xorriso`
* `qemu-system-<arch>` for testing purposes.
* `nasm`

### · Enviroment Setup

To compile the project, a working `gcc` toolchain needs to be obtained.
If you do not know how to obtain one, please refer to this [link](https://wiki.osdev.org/GCC_Cross-Compiler). After downloading or compiling the toolchain, `bin,libexec` and the root path of the compiler needs to be appended onto the `$PATH`.
e.g.
```
i386-elf-4.9.1-Linux-x86_64/
├── bin/
└── libexec/
You should add these folder onto the path.
```
After the instalation of prerequisites and the PATH modifications, you should be ready to go.

### · Compiling & Packing

Some variables needs to be changed in the shell scripts.

```bash
#In all.sh
arch="i386" #This needs to be changed to the arch of the downloaded
            #toolchain.
...
```
There are currently two ways of packing a bootable ISO in Stroma OS,

1. Normal, which uses your GRUB instalation.
2. Fallback, which uses the provided second stage eltorito bootloader.
3. (NOT IMPLEMENTED) U-boot, for arm and derivitive architectures.

To use the first option, your GRUB installation needs to be compatible with the arch. you are compiling Stroma OS for.

```
x86_64 HOST (Your OS)-> i386 Stroma OS
                        i686 Stroma OS
                        x86_64 Stroma OS
```

```bash
#clean;
install_headers;
compile_modules;
compile_kernel;
link;
pack; # Normal
   
#pack_fallback; # Fallback

#If you want to use fallback, comment pack; and uncomment pack_fallback;
```
