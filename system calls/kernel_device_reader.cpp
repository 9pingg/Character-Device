SYSCALL_DEFINE2(kernel_device_reader, char __user *, read_buffer, int, len_buffer)
{	
    struct file *fp;     // File pointer to the device file
    loff_t pos;          // File position for read operation (not used in this case)

    // Open the device file in read/write mode with the given permissions (0777)
    fp = filp_open("/dev/new_device", O_RDWR, 0777);
    if (IS_ERR(fp)) {
        printk("file error\n");
        return -EFAULT; // Return an error code if opening the device file fails
    }

    pos = 0; // Initialize the file position to 0 (not used in this case)

    // Use vfs_read to read data from the device file into the read_buffer
    ssize_t result = vfs_read(fp, read_buffer, sizeof(read_buffer), &pos);

    // Check if the read operation was successful (result should be the number of bytes read)
    if (result < 0) {
        printk("read error");
        filp_close(fp, NULL); // Close the device file in case of an error
        return -EFAULT; // Return an error code to the user-space application
    }

    filp_close(fp, NULL); // Close the device file
    return 0; // Return 0 to indicate a successful read operation
}
