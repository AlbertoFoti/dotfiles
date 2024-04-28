## install windows ISO
## install virtio-win-pkg-scripts
https://github.com/virtio-win/virtio-win-pkg-scripts/blob/master/README.md

## install Virt-Manager
paru -S virt-manager
sudo systemctl enable libvirtd.service
sudo systemctl start libvirtd.service
sudo systemctl enable virtlogd.service
sudo systemctl start virtlogd.service

/etc/libvirt/libvirtd.conf
...
unix_sock_group = 'libvirt'
...
unix_sock_rw_perms = '0770'
...

sudo usermod -a -G libvirt albertofots
sudo pacman -S qemu virt-manager virt-viewer dnsmasq vde2 bridge-utils openbsd-netcat
sudo pacman -S ebtables iptables
sudo pacman -S libguestfs

virsh net-define /usr/share/libvirt/networks/default.xml

<network>
  <name>default</name>
  <uuid>9a05da11-e96b-47f3-8253-a3a482e445f5</uuid>
  <forward mode='nat'/>
  <bridge name='virbr0' stp='on' delay='0'/>
  <mac address='52:54:00:0a:cd:21'/>
  <ip address='192.168.122.1' netmask='255.255.255.0'>
    <dhcp>
      <range start='192.168.122.2' end='192.168.122.254'/>
    </dhcp>
  </ip>
</network>


virsh net-autostart default

virsh net-start default