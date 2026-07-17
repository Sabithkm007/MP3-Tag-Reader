#include <stdio.h>
#include<string.h>
#include "mp3.h"
#include "types.h"
#include<stdlib.h>

/*For validating view arguments*/
Status read_and_validate_view_args(char *argv[], MP3 *mp3_reader)
{
     //checking arguments
    if( argv[2]==NULL )
    {
        printf("Error: Argument missing!\n"); //error message
        printf("Expected syntax :\nFor view : ./a.out -v sample.mp3\nFor edit :  ./a.out -e -t/-a/-A/-g/-y/-c  [edit] sample.mp3\n");
        return e_failure;
    }
    //  Validate mp3 file (.mp3)
    if (strstr(argv[2], ".mp3") != NULL)
    {
      //  printf("mp3file is present\n");
        mp3_reader->mp3_fname = argv[2]; // storing to structure 
    }
    else
    {
        printf("mp3file is not present!\n");
        return e_failure;
    }
    return e_success;

}
/* For view of mp3 contents*/
Status view_mp3(MP3 *mp3_reader)
{
    if(open_files(mp3_reader)==e_success) //calling function for opening files
    {
      //  printf("File opened successfully\n");
    }
    else
    {
        printf("Error : File doesnt opened\n");
        return e_failure;
    }
    rewind(mp3_reader->fptr_mp3); //rewinding the cursor to begining 
    fseek(mp3_reader->fptr_mp3,10,SEEK_SET); //seek 10 bytes
    printf("-------Viewing mp3 tags for %s-------\n\n",mp3_reader ->mp3_fname); //printing header for viewing
    for(int i=0;i<6;i++) //till 6 tags
    {
        char tag[5]; //temperory array for storing tag
        fread(tag,4,1,mp3_reader->fptr_mp3); //reading tag
        tag[4] = '\0';
      //  printf("Tag is %s\n",tag);
        long size = 0; //for reading size
        fread(&size,4,1,mp3_reader->fptr_mp3); //reading size
        size = ((size >> 24) & 0x000000FF) | ((size >> 8)  & 0x0000FF00) | ((size << 8)  & 0x00FF0000) | ((size << 24) & 0xFF000000);
                                                            //converting big endiean to littile endiean
        fseek(mp3_reader->fptr_mp3,2,SEEK_CUR); //seek flag bytes
        char data[size+1]; //for collecting data
        fread(data,size,1,mp3_reader->fptr_mp3); //reading data
        data[size] = '\0';
        if(strcmp(tag,"TIT2")==0) 
        printf("    Title    : %s\n",data+1); //checking tag1 and printing data+1 (for skipping 1 byte for null)
        if(strcmp(tag,"TPE1")==0)
        printf("    Artist   : %s\n",data+1);//checking tag2 and printing data+1 (for skipping 1 byte for null)
        if(strcmp(tag,"TALB")==0)
        printf("    Album    : %s\n",data+1);//checking tag3 and printing data+1 (for skipping 1 byte for null)
        if(strcmp(tag,"TYER")==0)
        printf("    Year     : %s\n",data+1);//checking tag4 and printing data+1 (for skipping 1 byte for null)
        if(strcmp(tag,"TCON")==0)
        printf("    Genre    : %s\n",data+1);//checking tag5 and printing data+1 (for skipping 1 byte for null)
        if(strcmp(tag,"COMM")==0)
        printf("    Language : %s\n\n",data+1);//checking tag6 and printing data+1 (for skipping 1 byte for null)
       
        
       
    }
    printf("-----------------------------------------\n");
}
/* Get File pointers for i/p and o/p files */
Status open_files(MP3 *mp3_reader)
{
     mp3_reader -> fptr_mp3 = fopen( mp3_reader ->mp3_fname,"rb"); //opening source file in read binary mode and storing to file pointer
    
    if(  mp3_reader -> fptr_mp3 == NULL) //if file is not present
    {
        printf("Mp3 file is not present\n");
        return e_failure;
    }
    return e_success;
}