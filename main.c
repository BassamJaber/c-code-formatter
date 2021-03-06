#include "header.h"

int main (int argc, char * argv[]){

  if(argc != 3){
    printf("Usage: ./main.c   inputfile.c  output.c\n");
    exit(0);
   }

  FILE *file=fileOpenOrDie(argv[1]);

   int numOfLines=0;
   char temp[255];
   while(!feof(file)){
      fgets(temp,255,file);
      numOfLines++;
   }

 rewind(file);          /*return to the Begining of the File again*/
 char * code[numOfLines];

 int i=0,j=0;

 /*Read the file Again and Save it in Array Of Strings
  *we Read this array element by element then Mofdify it and print it again inti file
  */

 while(!feof(file)){
   fgets(temp,255,file);
   code[i]=malloc(strlen(temp)+1);
   strcpy(code[i++],temp);
 }

  fclose(file);

   FILE *out;
  out=fileOpenToWrite(argv[2]);

 /*The code now Saved in Array code*/

 /* implementation for case 1 : # include <...>; only keep one space and trim other spaces */

  int LineSize=0 ;
  int StringFlag=0,StructureFlag=0,NewLineFlag=0,OpenBracket=0,IncludeFlag=0,CommentFlag=0,ForLoopFlag=0;   /*flags that indicate occurance of Specific String */
  /*Working Strategy
   *we test each character in the file , and do action when we find special character
   *rules are defined in Project Discription
   */

  for(i=0;i<numOfLines;i++){

   LineSize=strlen(code[i]);
   NewLineFlag=0;
   if(LineSize>1){

   if(isStructure(code[i])){
    fprintf(out,"\n");
   }

    for(j=0;j<LineSize;j++){
      if(strchr("/",code[i][j]) && strchr("*",code[i][j+1]) ){                             
            fprintf(out,"\n%c%c ",code[i][j],code[i][j+1]);
            j++;
            CommentFlag=1;
       }else if(strchr("*",code[i][j]) && strchr("/",code[i][j+1]) ){                                 
            fprintf(out," %c%c\n",code[i][j],code[i][j+1]);
            j++;   
	   CommentFlag=0; 
    }else if(strchr("\"",code[i][j])){
        if(StringFlag==0){
           StringFlag=1;
           fprintf(out,"%c",code[i][j]);
         }else{
		StringFlag=0;
                fprintf(out,"%c",code[i][j]);
              }	 
      
     }else if(StringFlag ==0 && CommentFlag==0) {
        if(strchr("#",code[i][j])){
           fprintf(out,"%c ",code[i][j]);    /*if we have # then we print Space after it then Continue*/
           NewLineFlag=1;
           IncludeFlag=1;
        }else if( (code[i][j]  >= 'a' && code[i][j]<= 'z' )||( code[i][j] >='A' && code[i][j] <='Z')){
                  if(StructureFlag== 1 && NewLineFlag== 0 && OpenBracket == 1){
                     fprintf(out,"  %c",code[i][j]);
                     NewLineFlag=1;
                  }else if(NewLineFlag == 0 && OpenBracket >0){
                        int k=0;
                        for(k=0;k<OpenBracket;k++){
                           fprintf(out," ");
                        }
                        fprintf(out,"%c",code[i][j]);    /*if we Have A Character then we Print it*/
                        NewLineFlag=1;
                       }else{
				fprintf(out,"%c",code[i][j]);
 				NewLineFlag=1;
                            }
        }else if( strchr(";",code[i][j]) ){
                  if(ForLoopFlag==0){ 
                    fprintf(out,"%c\n",code[i][j]);
                    NewLineFlag=0;
                   }else{
			  fprintf(out," %c ",code[i][j]);
                        }
        }else if( strchr(">",code[i][j]) && IncludeFlag==1){
                  fprintf(out,"%c\n",code[i][j]);
   		  NewLineFlag=0;
 	          IncludeFlag=0;
        }else if(strchr("}",code[i][j])){
                  if(StructureFlag==1){
                     int k=0;
                        for(k=0;k<OpenBracket-1;k++){
                           fprintf(out," ");
                        }
		    fprintf(out,"%c\n\n",code[i][j]);
                    StructureFlag=0;             /* closing } indicate end of Structure if flag is equal to 1	*/
                    NewLineFlag=0;
     		    OpenBracket--;
                   }else{
                        int k=0;
                        for(k=0;k<OpenBracket-1;k++){
                           fprintf(out," ");
                        }
		       fprintf(out,"%c\n",code[i][j]);
                       StructureFlag=0;             /* closing } indicate end of Structure if flag is equal to 1	*/
                       NewLineFlag=0;
		       OpenBracket--;
                   }
        }else if(strchr("{",code[i][j])){
                 if(isStructure(code[i])){
                    fprintf(out,"%c\n",code[i][j]);
                    StructureFlag=1;
                    NewLineFlag=0;
 		    OpenBracket++;
                  }else{
                        fprintf(out,"\n");
                        int k=0;
                        for(k=0;k<OpenBracket;k++){
                           fprintf(out," ");
                        }
			 fprintf(out,"%c\n",code[i][j]);
                         NewLineFlag=0;
			 OpenBracket++;
                       }
        }else if(strchr("[].",code[i][j])){
		  fprintf(out,"%c",code[i][j]);
                  NewLineFlag=1;
        }else if(strchr("<",code[i][j]) && IncludeFlag==1){
                fprintf(out,"%c",code[i][j]);
                NewLineFlag==1;
                
        }else if(strchr(" ",code[i][j])){
                 if(strchr(" ",code[i][j+1])){
                     j++;
                 }else{
                       if(NewLineFlag == 1)
                          fprintf(out," ");
                      }
       }else if(strchr("1234567890",code[i][j])){
		fprintf(out,"%c",code[i][j]);
       }else if(strchr("),",code[i][j])){
               if(ForLoopFlag==1 && !strchr(",",code[i][j])){
                  ForLoopFlag=0;
                  fprintf(out,"%c\n",code[i][j]);
               }else {
		if(!strchr(" ",code[i][j+1]))
                  fprintf(out,"%c ",code[i][j]);
                 else
 		  fprintf(out,"%c",code[i][j]);
               }
       }else if(strchr("(",code[i][j])){
              if(strstr(code[i],"for")){
                 ForLoopFlag=1;

              if (strchr(" ",code[i][j-1]))
                 fprintf(out,"%c",code[i][j]);
              else
		 fprintf(out," %c",code[i][j]);
     
             }else {
                    if (strchr(" ",code[i][j-1]))
                         fprintf(out,"%c",code[i][j]);
                     else
		         fprintf(out," %c",code[i][j]);
                   }
       } else if(strchr("<>=+-*/\\",code[i][j])){
               if(strchr(" ",code[i][j-1])){
		 fprintf(out,"%c",code[i][j]);
		 /*if two operation*/
                 if(strchr("<>=+-*/\\",code[i][j+1])){
		    fprintf(out,"%c ",code[i][j+1]);
 		    j++;
                   }else if(!strchr(" ",code[i][j+1])){
			   fprintf(out," ");
                        }
               }else{
                     /*if it have no space before*/
		     fprintf(out," %c",code[i][j]);
                      /*if two operation*/
                      if(strchr("<>=+-*/\\",code[i][j+1])){
		         fprintf(out,"%c ",code[i][j+1]);
 		          j++;
                        }else if(!strchr(" ",code[i][j+1])){
			    fprintf(out," ");
                        }
                    }

           }
       }else{  /*print any thing inside " "*/
	   fprintf(out,"%c",code[i][j]);
         }

     }

    } /*end of if statement empty line */
}

fclose(out);

return 0;
}
