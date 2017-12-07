#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int removeFD = open("removeThese.txt", O_RDONLY);
	int fileSize = 0;
	struct stat st = {0};
	int lineNum = 0;
	std::string toBeRemoved;
	char transferBuffer[300];
	bool transferReady = false;

	if(removeFD < 0){
		std::cout << "[Error opening remove file]\n";
		close(removeFD);
		return 1;
	}else{
		std::cout<< "[Open Successful]\n";
		stat("removeThese.txt", &st);
		fileSize = st.st_size;
		char buffer[fileSize];
		if(read(removeFD, buffer, fileSize) < 0){
			std::cout<<"[Error Reading To Buffer!]\n";
			close(removeFD);
			return 1;
		}else{
			std::cout<<"[Read Successful!]";
			for(int i=0; i<fileSize; i++){
				if(buffer[i] == '#'){
					lineNum++;
				}
			}
			std::cout<<"\nFile Count: "<<lineNum<<std::endl;
			int x=0;
			for(int i=0; i<fileSize; i++){
				if(transferReady){
					toBeRemoved = transferBuffer;
					std::cout<<"to be removed: "<<toBeRemoved<<std::endl;
					if(remove(toBeRemoved.c_str())){
						std::cout<<"\n[Remove Successful]\n";
					}else{std::cout<<"\n[Remove Failed]\n";}
					x=0;
					for(int g=0; g<300; g++){transferBuffer[g] = '\0';}
					toBeRemoved = '\0';
					transferReady = false;
				}else{
					if(buffer[i] != '#'){
						transferBuffer[x] = buffer[i];
						x++;
					}else{
						transferReady = true;
					}
				}
			}
		}
	}
	return 0;
}
