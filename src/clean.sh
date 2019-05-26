root=$PWD
build="$root/build"
kernel="$root/kernel/$arch"
iso="$root/build/iso"

rm $build/obj/*.o
rm $build/libs/*.a
rm $iso/boot/*.bin
rm os.iso