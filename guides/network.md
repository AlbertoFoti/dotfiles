# How to fix Network Manager issues

    ping 8.8.8.8

    ip a

    systemctl status NetworkManager

### Correct troubleshooting procedure

Check kernel versions

    hostnamectl

Verify that the adapter is found (if not, it's bad)

    lspci

Wifi module check (hope to receive a NON-empty output)

    modinfo iwlwifi

Check wifi card drivers (hope for some kind of output)

    lsmod | grep iwlwifi

If no output is dislayed, it means that no driver has been loaded.
Try to see the logs to troubleshoot further

    dmesg | grep "no suitable firmware found!"

If something appears, it means you don't have the drivers.
If nothing appears, do

    dmesg

and try to find the error lines where the driver is failing to load.

### Fix

Do a 

    sudo systemctl edit NetworkManager

and then at the top (for the unit drop) add the following line

    ExecStartPre=/usr/bin/sleep 10