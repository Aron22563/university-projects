#include<iostream> 
#include<unistd.h> 
#include<dirent.h> 
#include<signal.h> 
#include<fcntl.h>
#include<cstdio>
#include<sys/syscall.h>

#define BUF_SIZE 4096
#define NAME_MAX_LEN 255
struct linux_dirent {
    unsigned long  d_ino;     /* Inode number */
    unsigned long  d_off;     /* Offset to next linux_dirent */
    unsigned short d_reclen;  /* Length of this linux_dirent */
    char           d_name[];  /* Filename (null-terminated) */
                        /* length is actually (d_reclen - 2 -
                           offsetof(struct linux_dirent, d_name) */
    /*
    char           pad;       // Zero padding byte
    char           d_type;    // File type (only since Linux 2.6.4;
                              // offset is (d_reclen - 1))
    */

};
int main(){ 
int fd; 
char buffer[BUF_SIZE]; 
size_t BytesRead;
struct linux_dirent* CurrentStruct;
fd=openat(AT_FDCWD,"/proc",O_DIRECTORY);
if(fd==-1)
throw std::runtime_error("Folder access threw an error"); 

while((BytesRead=syscall(SYS_getdents64, fd, buffer, BUF_SIZE))>0){
 for(size_t offset=0; offset<BytesRead;){
  CurrentStruct=reinterpret_cast<struct linux_dirent*>(buffer+offset);
  std::cout << "Name: " <<  CurrentStruct->d_name << std::endl; 
  offset+=CurrentStruct->d_reclen; 
 }
 if(BytesRead==-1)
    throw std::runtime_error("Directory entry access error"); 	   
}
  close(fd); 
}
