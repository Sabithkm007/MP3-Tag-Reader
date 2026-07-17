#include <stdio.h>
#include<string.h>
#include "mp3.h"
#include "types.h"
#include<stdlib.h>

/* Read and validate edit args from argv */
Status read_and_validate_edit_args(char *argv[], MP3 *mp3_reader)
{
    
    if( argv[2]==NULL || argv[3]==NULL || argv[4]==NULL) //checking arguments
    {
        printf("Error: Argument missing!\n"); //error message
        printf("Expected syntax :\nFor view : ./a.out -v sample.mp3\nFor edit :  ./a.out -e -t/-a/-A/-g/-y/-c [edit_name] sample.mp3\n");
        return e_failure;
    }
    if (strstr(argv[4], ".mp3") == NULL)   //  Validate mp3 file (.mp3)
    {
        printf("mp3file is not present!\n");
        return e_failure;
    }
    if(strcmp(argv[2],"-t")==0)    //checking command line argument wheather it is -t
    {
        //printf("Read and validated successfull\n");
       if(edit_mp3("TIT2",mp3_reader,argv)!=e_success)    //calling edit function for edit titile
       {
            return e_failure;
       }


    }
    else if(strcmp(argv[2],"-a")==0)    //checking command line argument wheather it is -a
    {
        //printf("Read and validated successfull\n");
       if(edit_mp3("TPE1",mp3_reader,argv)!=e_success)   //calling edit function for edit artist
       {
            return e_failure;
       }
    }
    else if(strcmp(argv[2],"-A")==0)    //checking command line argument wheather it is -A
    {
        // printf("Read and validated successfull\n");
        if(edit_mp3("TALB",mp3_reader,argv)!=e_success)   //calling edit function for edit album
       {
            return e_failure;
       }
    }
    else if(strcmp(argv[2],"-g")==0)    //checking command line argument wheather it is -g
    {
        // printf("Read and validated successfull\n");
        if(edit_mp3("TCON",mp3_reader,argv)!=e_success)    //calling edit function for edit genre
       {
            return e_failure;
       }
    }
    else if(strcmp(argv[2],"-y")==0)    //checking command line argument wheather it is -y
    {
        // printf("Read and validated successfull\n");
        if(edit_mp3("TYER",mp3_reader,argv)!=e_success)   //calling edit function for edit year
       {
            return e_failure;
       }
    }
    else if(strcmp(argv[2],"-c")==0)    //checking command line argument wheather it is -c
    {
        // printf("Read and validated successfull\n");
        if(edit_mp3("COMM",mp3_reader,argv)!=e_success)   //calling edit function for edit language
       {
            return e_failure;
       }
    }
    else 
    return e_unsupported;   //unsupported argument

    return e_success;
}
/* Edit mp3 contents */
Status edit_mp3(char *data,MP3 *mp3_reader,char *argv[])
{
    open_edit_files(mp3_reader,argv);    //opening edit files from arguments
    //printf("Opening edit files successfull\n");

    
    rewind(mp3_reader->fptr_mp3);   //rewinding the cursor to begining
    char mp3header[10];    //temperory array for 10 bytes mp3 header
    fread(mp3header, 10, 1, mp3_reader->fptr_mp3);   //reading from orginal
    fwrite(mp3header, 10, 1, mp3_reader->duplicate);  //write to duplicate

    for (int i = 0; i < 6; i++)   //till 6 tags
    {
        char arr[5];   //temp array for storing tag
        fread(arr, 4, 1, mp3_reader->fptr_mp3);
        arr[4] = '\0';

        long size_old = 0; //to store old size
        fread(&size_old, 4, 1, mp3_reader->fptr_mp3);   //reading old size
        size_old = ((size_old >> 24) & 0x000000FF) |
                   ((size_old >> 8)  & 0x0000FF00) |
                   ((size_old << 8)  & 0x00FF0000) |
                   ((size_old << 24) & 0xFF000000);   //convert big endiean to little
 
        char flag[2]; //for storing flag
        fread(flag, 2, 1, mp3_reader->fptr_mp3);   //reading flag

        if (strcmp(data, arr) == e_success)   //comparing with temp tag to tag
        {
           // printf("Editing frame: %s\n", arr);
            fwrite(arr, 4, 1, mp3_reader->duplicate);   //writing tag to duplicate

            long size_new = strlen(argv[3])+1;   //collecting editing data size (+1 for the null after flag)
            long size_conv = ((size_new >> 24) & 0x000000FF) |
                           ((size_new >> 8)  & 0x0000FF00) |
                           ((size_new << 8)  & 0x00FF0000) |
                           ((size_new << 24) & 0xFF000000);  //converted the size littile endiean to big 

            fwrite(&size_conv, 4, 1, mp3_reader->duplicate);  //writing converted new size
            fwrite(flag, 2, 1, mp3_reader->duplicate);  //writing flag
            unsigned char encoding = 0x00;  // 1 byte for encoding/null 
            fwrite(&encoding, 1, 1, mp3_reader->duplicate);  //writing null
            printf("Edited by : %s\n",argv[3]);
            fwrite(argv[3],strlen(argv[3]) , 1, mp3_reader->duplicate);   //writing editing data
            fseek(mp3_reader->fptr_mp3, size_old, SEEK_CUR); //skipping old size from the orginal file
        }
        else
        {
            fwrite(arr, 4, 1, mp3_reader->duplicate); //writing tag to duplicate
            long size_conv = ((size_old >> 24) & 0x000000FF) |
                           ((size_old >> 8)  & 0x0000FF00) |
                           ((size_old << 8)  & 0x00FF0000) |
                           ((size_old << 24) & 0xFF000000); //converted the size littile endiean to big
            fwrite(&size_conv, 4, 1, mp3_reader->duplicate);  //writing converted  size
            fwrite(flag, 2, 1, mp3_reader->duplicate); //writing flag

            char *old_data = malloc(size_old); //allocating memory for old data
            if (!old_data)
            {
                return e_failure;
            }
            fread(old_data, size_old, 1, mp3_reader->fptr_mp3); //reading old data
            fwrite(old_data, size_old, 1, mp3_reader->duplicate);//writing old data to duplicate file
            free(old_data); //free allocated memory
        }
    }
    copy_remaining_data(mp3_reader->fptr_mp3, mp3_reader->duplicate); //calling function to copy remaining data

    fclose(mp3_reader->fptr_mp3); //closing files
    fclose(mp3_reader->duplicate);

    remove(mp3_reader->mp3_fname); //remove orginal file
    rename( mp3_reader->mp3_dupe, mp3_reader->mp3_fname); //renaming duplicate file name to orginal file name
    
    view_mp3(mp3_reader); //calling view function
    return e_success;

}
/*For opening edit files*/
Status open_edit_files(MP3 *mp3_reader,char *argv[])
{
    //validating arguments
     if( argv[4]==NULL )
    {
        printf("Error: mp3file is missing!\n");
        
        return e_failure;
    }
    if (strstr(argv[4], ".mp3") != NULL)//  Validate mp3 file (.mp3)
    {
       // printf("mp3file is present\n");
        mp3_reader->mp3_fname = argv[4]; // storing to structure 
        open_files(mp3_reader);//for open the mp3 file
    }
    else
    {
        printf("mp3file is not present!\n");
        return e_failure;
    }
    
    mp3_reader ->mp3_dupe ="duplicate.mp3"; 
    mp3_reader->duplicate = fopen(mp3_reader ->mp3_dupe,"wb"); //creating duplicate file and opening in write mode
    if(mp3_reader->duplicate  == NULL)
    {
        printf("Error opening duplicate mp3 file\n");
        return e_failure;
    }
}
/*For copying remaining data*/
Status copy_remaining_data(FILE *fptr_mp3, FILE *duplicate)
{
    char ch;
    while(fread(&ch,1,1,fptr_mp3) >0) 
    {
      fwrite(&ch,1,1,duplicate); //copying remaining data character by character
    }
     return e_success;
}