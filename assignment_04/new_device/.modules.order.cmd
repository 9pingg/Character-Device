cmd_/home/kern/project_os/assignment_04/new_device/modules.order := {   echo /home/kern/project_os/assignment_04/new_device/new_device.ko; :; } | awk '!x[$$0]++' - > /home/kern/project_os/assignment_04/new_device/modules.order
