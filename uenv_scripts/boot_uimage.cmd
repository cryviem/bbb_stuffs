#
# Simple Boot script for BeagleBone Black
# Minimal version - direct translation of sd_uEnv.txt
#
# Compile: mkimage -C none -A arm -T script -d boot_simple.cmd boot.scr.uimg
#

echo "Booting from microSD..."

# Load uImage kernel
echo "Loading uImage..."
load mmc 0:1 0x82000000 uImage

# Load device tree (uses fdtfile set by findfdt or default)
if test -z "${fdtfile}"; then
    setenv fdtfile "am335x-boneblack.dtb"
fi
echo "Loading ${fdtfile}..."
load mmc 0:1 0x88000000 ${fdtfile}

# Set boot arguments
setenv bootargs "console=ttyO0,115200n8 root=/dev/mmcblk0p2 rw rootfstype=ext4 rootwait"

# Boot
echo "Starting kernel..."
bootm 0x82000000 - 0x88000000
