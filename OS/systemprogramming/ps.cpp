#include<iostream> 
#include<unistd.h> 
#include<dirent.h> 
#include<signal.h> 
#include<fcntl.h>
#include<cstdio>
#include<sys/syscall.h>

#define BUF_SIZE 4096
#define EXE_BUF_SIZE 4095
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

std::string get_exe(std::string pid){ 
   char buffer[EXE_BUF_SIZE];   
   std::string path="/proc/" + pid + "/exe";   
   size_t length=readlink(path.c_str(), buffer, EXE_BUF_SIZE-1);  
   //std::cout << "Path: " <<  path; 
   if(length==-1)    
	   return "";         
   buffer[length]='\0';  
   return std::string(buffer);   
}
std::string get_cwd(std::string pid){
	return ""; 
}
std::string get_base_adress(std::string pid){
	return ""; 
}
std::string get_stat(std::string pid){
	return ""; 
}
std::string get_cmd(std::string pid){
	return ""; 
}


int main(){ 
char buffer[BUF_SIZE]; 
size_t BytesRead;
//Current object and attributes
struct linux_dirent* CurrentStruct;
std::string CurrentPID; 

//Opening of the proc directory
int fd; 
fd=openat(AT_FDCWD,"/proc",O_DIRECTORY);
if(fd==-1)
throw std::runtime_error("Folder access threw an error");

while((BytesRead=syscall(SYS_getdents64, fd, buffer, BUF_SIZE))>0){
 for(size_t offset=0; offset<BytesRead;){
  CurrentStruct=reinterpret_cast<struct linux_dirent*>(buffer+offset);
  if(std::isdigit(CurrentStruct->d_name[1])){
  CurrentPID=CurrentStruct->d_name;
  CurrentPID=CurrentPID.substr(1);   
  try{
	  std::stoi(CurrentPID)==getpid();
  }
  catch (std::exception& e){
	  std::cout << "CurrentPID: " << CurrentPID << " with Length: " << sizeof(CurrentPID) ; 
	  }
  
 //Output generation
  std::string exe_path=get_exe(CurrentPID); 
  std::string cwd_path=get_cwd(CurrentPID); 
  std::string base_adress_path=get_base_adress(CurrentPID); 
  std::string stat_path=get_stat(CurrentPID); 
  std::string cmd_path=get_cmd(CurrentPID); 

 //Output
  if(exe_path==""/*||cwd_path==""||base_adress_path==""||stat_path==""||cmd_path==""*/){
  }
  else{
  std::cout << "PID: " <<  CurrentPID; 
  std::cout << "Exe: " << exe_path << std::endl; 
  } 
  }
  offset+=CurrentStruct->d_reclen; 
  
 }
 if(BytesRead==-1)
    throw std::runtime_error("Directory entry access error"); 	   
}
  close(fd); 
}

