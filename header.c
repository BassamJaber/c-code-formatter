#include "header.h"

FILE * fileOpenOrDie(char * fileName){

 FILE *file;
 file=fopen(fileName,"r");
 if(file==NULL){
   printf("File Does not exist \n");
   exit(0);
 }else {
	return file;
       }
}

FILE *fileOpenToWrite(char *fileName){
 
 FILE * file;
 file=fopen(fileName,"w");
 if(file==NULL){
   printf("Can't Open file \n");
   exit(0);
  }else{
	 return file;
       }
}

int isStructure(char * string){

 char * temp;
 char * type="typedef";
 char * structure="struct";
 temp=strstr(string,type);
 if(temp!= NULL){
    temp=strstr(string,structure);
    if(temp!=NULL){
	return 1;
    }else {
		return 0;
          }
 }else{
	return 0;
      }
}

int isLetter(char c){
 return ( (c >= 'a' && c <= 'z' )||( c >='A' && c <='Z'))?1:0;
}

int isEmptyLine(char * string){

 if(strcmp(string,"")==0){
  printf("hshsh");
  return 1;
  }else {
           int i;
 	   for(i=0;i<strlen(string);i++){
	      if(!strchr(" ",string[i])){
		return 0;
              }
	   }
        return 1;
        }
}
int containInclude(char * string){
 int i ;
 for(i=0;i<strlen(string);i++){
  if(strchr("#",string[i]))
    return 1;
 }
 return 0;
}

void removeSpaces(char *string){
  char * temp = (char*)malloc(sizeof(char)*strlen(string)+1);
  int i;
  int j=0;
  char c;
  for(i=0;i<strlen(string);){
    c=string[i];
     if(strchr(" ",c)){
        i++;
      }else{
 	       temp[j++]=string[i++];
   	    }
  }
  temp[j]='\0';
  strcpy(string,temp);
}
