#
# Boot script for BeagleBone Black using zImage (modern kernel)
#
# Compile: mkimage -C none -A arm -T script -d boot_zimage.cmd boot.scr.uimg
#

echo "Booting BeagleBone Black (zImage)..."

# Configuration
setenv root_dev "/dev/mmcblk0p5"
setenv fdtfile "am335x-boneblack.dtb"

# Load zImage kernel
echo "Loading zImage..."
load mmc 0:2 0x82000000 zImage

# Load device tree
echo "Loading ${fdtfile}..."
load mmc 0:2 0x88000000 ${fdtfile}

# Set boot arguments
setenv bootargs "console=ttyO0,115200n8 root=${root_dev} rw rootfstype=ext4 rootwait"

# Boot with bootz (for zImage)
echo "Starting kernel..."
bootz 0x82000000 - 0x88000000
