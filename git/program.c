#include<stdio.h>
#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#define MAX 2000

int main()
{ 

 
  
  char sourcepath[MAX];
  char destpath[MAX];

  printf("Enter the source path\n");
  scanf("%s", sourcepath);
  printf("Enter the Destination path\n");
  scanf("%s", destpath);
 	
  		  
  struct dirent* folder;			          //file directory as folder 

  DIR* oopendir = NULL ;
  DIR* rreaddir = NULL ;

  oopendir = opendir(sourcepath);			//opening the source path folder 
  
  if (!oopendir)
  printf("\error cannot open the folder");
  
  else {						// if the folder consists of files then
						
	int noerror = 0;
	while ( folder = readdir(oopendir))
	{
		if(noerror == 0)
		noerror = errno;
		//printf("\n%s", folder->d_name);
		//printf("\n%s %s", destpath, folder->d_name);
		

		struct stat st_buf;			// creating a buffer class to access the file pointer of f1 nd f2
		stat(folder->d_name, &st_buf);		// storing temp files of the folder in a buffer class.
		if (S_ISDIR (st_buf.st_mode)){		//returns non zero if the file is directory
			continue;
		}
		else if (S_ISREG (st_buf.st_mode))        //returns non zero if its a regular file
		{
		  FILE* readfile = fopen(folder->d_name,"r");

		  if (readfile){                                  //creating a new folder temp in using buffer to perform read and write 
			//printf("reading %s\n", folder->d_name);
			char strDest[MAX] = { 0 };
			sprintf(strDest, "%s/%s", destpath, folder->d_name);
			//printf("dest %s\n", strDest);


			FILE* writefile = fopen(strDest,"w");
			if(writefile){
				char buffer[MAX] = { 0 };		
				while(fgets(buffer,MAX, readfile))
				{
				 fputs(buffer,writefile);		//calling the temp into main dest folder.
				}
				 fclose(writefile);
		    }
		    else 
		    {
			printf("cannot open the file %s", strDest);
		    }
		fclose(readfile);
		    }
		  }
		}
}
closedir(oopendir);
return 0;
}



			
		
  
  
