#include<iostream> 
#include<unistd.h> 
#include<dirent.h> 
#include<signal.h> 
#include<sys/syscall.h>
int main(){ 
DIR* fd=opendir("/proc");
char buffer[4096]; 
syscall(217, fd, buffer, sizeof(buffer)); 
}
