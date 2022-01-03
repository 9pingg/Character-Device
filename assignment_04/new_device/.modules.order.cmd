cmd_/home/kern/os/new_device/modules.order := {   echo /home/kern/os/new_device/new_device.ko; :; } | awk '!x[$$0]++' - > /home/kern/os/new_device/modules.order
