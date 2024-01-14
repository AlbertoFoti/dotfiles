## Boot from USB

## Connect to internet

iwctl
device list
station <interface> scan
station <interface> scan
station <interface> connect

ping archlinux.org

## Partition the drive

cfdisk

lsblk

## Update system clock 

timedatectl

## Format partitions

mkfs.ext4 /dev/root_partition
mkfs.fat -F 32 /dev/efi_system_partition
mkswap /dev/swap_partition

mount /dev/root_partition /mnt
mount --mkdir /dev/efi_system_partition /mnt/boot
swapon /dev/swap_partition

## Packages

pacstrap -K /mnt base linux linux-firmware sof-firmware base-devel grub efibootmgr vim networkmanager git

## System config

    genfstab -U /mnt >> /mnt/etc/fstab
    arch-chroot /mnt

    ln -sf /usr/share/zoneinfo/Region/City /etc/localtime
    hwclock --systohc

Edit /etc/locale.gen
    locale-gen

/etc/locale.conf
LANG=en_US.UTF-8

## Hostname, User and sudo 

/etc/hostname
yourhostname

passwd

useradd -m -G wheel -s /bin/bash bob
passwd bob

EDITOR=vim visudo
remove comment on sudo in group wheel

su bob
sudo pacman -Syu

exit
sudo systemctl enable NetworkManager

## Grub setup

grub-install /dev/sda
grub-mkconfig -o /boot/grub/grub.cfg

## Reboot

umount -a
reboot

## Activate wifi

nmtui
sudo pacman -S neofetch
neofetch

[ around 180/200 packages at the end of installation ]





