#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(){
	DIR *directory;
	struct dirent *entry;
	directory = opendir("D:/Harsha");
	if(directory==NULL){
		perror("opendir");
		exit(1);
	}
	
	while((entry=readdir(directory))){
		printf("%s\n",entry->d_name);
	}
	
	closedir(directory);
	
	return 0;
}


































































































/*int main(){
	DIR *directory;
	struct dirent *entry;
	directory = opendir("D:/Subjects");
	if(directory == NULL){
		perror("opendir");
		exit(1);
	}
	while((entry = readdir(directory))){
		printf("%s\n",entry->d_name);
	}
	closedir(directory);
	return 0;
}*/
