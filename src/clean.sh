root=$PWD
build="$root/build"
kernel="$root/kernel/$arch"
include="$build/include"
iso="$root/build/iso"

rm $build/obj/*.o
rm $build/libs/*.a
rm -rf $include/*
rm $iso/boot/*.bin
rm os.iso