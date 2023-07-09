# Character Device

- Developed a kernel-level miscellaneous character device using Linux kernel functions such as miscdevice, semaphore, kmalloc, copy_to_user and copy_from_user. The device utilizes a thread-safe FIFO queue to store a configurable number of data blocks, allowing for efficient and safe data transfer. Implemented custom read and write system calls using vfs_read and vfs_write functions along with filp_open/filp_close to manage the file operations. Utilized the open and release functions to handle the number of open devices.
