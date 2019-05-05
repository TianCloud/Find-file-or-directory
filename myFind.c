//created by Ruotian Liu, all rights reserved.
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>
#include <libgen.h>
#include <stdint.h>

char *name; //to save file or directory name for latering comparsion
int check=0; //flag

//nftw function call
static int processEntry(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){

//uncommon the following code to get file or directory type for extra info
/*	printf("%-3s ", 
		(tflag == FTW_D) ? "d" : (tflag == FTW_DNR) ? "dnr" :
		(tflag == FTW_DP) ? "dp" : (tflag == FTW_F) ? "f" : 
		(tflag == FTW_NS) ? "ns" : (tflag == FTW_SL) ? "sl" :
		(tflag == FTW_SLN) ? "sln" : "???",
		ftwbuf->level);
*/

	//compare if the given name has a match in the folder or given address
	if(strcmp(fpath + ftwbuf->base, name)==0){
		printf("found: %s\n", fpath);
		check = 1; //change flag to 1 if found
	}

	return 0;
}


//main function
int main(int argc, char *argv[]){

	//setting various flag type
	int flags = FTW_CHDIR | FTW_DEPTH | FTW_MOUNT | FTW_PHYS;
		
	//if there is only one command line argument, 
	//it means that the user did not input anything to find
	//so, a warning
	if(argc == 1){
		printf("Warning: File/directory name is missing, please check your input!\n");
		exit(1);
	}

	//set name = the second command line argument which is a file or directory name
	name = argv[1];

	//using nftw function call
	if(nftw((argc <= 2)? "./" : argv[2], processEntry, 25, flags ) == -1){
		perror("nftw");
		exit(EXIT_FAILURE);

	}

	//check if the file or directory was found during nftw function call
	//and give warning if not found
	if(argc==2 && check == 0){
		printf("Warning: Cannot locate file or directory!\n");
	}else if(argc == 3 && check == 0){
		printf("Warning: Cannot locate file or directory under the given address!\n");
	}

	//exit
	exit(EXIT_SUCCESS);
}
