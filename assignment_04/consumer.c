#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BYTE_COUNT 8
#define READER_SYSCALL_NO 448
int main(void){
    char random_str[8];
    // int fd1 = open("/dev/new_device", O_RDWR);
    // if(fd1 < 0){
    //     perror("device open");
    // }
    int result = 0;
    int cnt = 1;
    while(1){
        result = syscall(READER_SYSCALL_NO, random_str, BYTE_COUNT);
        //result = read(fd1, random_str, sizeof(random_str));
        if(result < 0){
            perror("syscall");
            
        }
        if(result >= 0){
            printf("******************************************\n\nstring received: %d %s\n\n", cnt,random_str);
            cnt++;

        }
        sleep(2);
    }
    //close(fd1);
    return 0;
}
//buffer_size=20 device_name=new_device string_char_count=20
