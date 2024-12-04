#include<iostream>
#include<string> 
#include<vector> 
#include<unistd.h>
#include<dirent.h> 
#include<signal.h> 
#include<cstring> 
//Methode zur Ueberpruefung ob es sich bei einem String um eine Zahl handelt
	bool isNumber(const std::string& a){
	 for(auto& x: a){
	         if(!std::isdigit(x)){
	         return false; 
		 }
	 }
	 return true; 
	}
//Methode fuer Command-Name
	std::string CommandName(pid_t pid){
		std::string file_path= "/proc/" +std::to_string(pid)+ "/comm"; 
		FILE *file= fopen(file_path.c_str(), "r"); 
		char buffer[256]; 
			if(!fgets(buffer,sizeof(buffer), file)){
				fclose(file); 
				return ""; 
			}
		buffer[strcspn(buffer, "\n")]=0;
	        fclose(file); 
	return std::string(buffer); 	
	}
//Main Methode
	int main([[maybe_unused]]int argc, char* argv[]){
		std::string keyword=argv[1]; 
		DIR* dir=opendir("/proc"); 
		struct dirent* entry; 
		while((entry=readdir(dir))!=NULL){
				if(entry->d_type==DT_DIR && isNumber(entry->d_name)){
				pid_t pid =static_cast<pid_t>(std::stoi(entry->d_name));
				std::string processname=CommandName(pid);
				if(processname.find(keyword)!=std::string::npos){
					if(kill(pid,SIGKILL)==-1)
						std::cout << "Something went wrong!" << std::endl;
				}
				}
		}
	return 0; 
	}
	
