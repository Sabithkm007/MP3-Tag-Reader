/*
NAME : MUHAMMED SABITH KM

PROJECT 2 : MP3 TAG READER AND EDITOR

DESCRIPTION : The MP3 Tag Reader and Editor is a C-based project that reads and modifies metadata (ID3v2 tags) from MP3 files.
These tags store information like Title, Artist, Album, Year, and Genre etc.
The Tag Reader part opens the MP3 file, reads each tag frame, converts size from big-endian to little-endian, and displays the text data.
The Tag Editor allows changing any specific tag (e.g., Title or Artist) by updating its frame data and writing it into a new duplicate MP3 file.
Command line arguments:
For viewing =  ./a.out -v mp3_filename
For decoding =  ./a.out -e -t/-a/-A/-m/-y/-c [edit_name] mp3_filename

DATE :1/11/2025
*/

#include <stdio.h>
#include<string.h>
#include"mp3.h"
#include "types.h"
#include<stdlib.h>

int main(int argc,char **argv)
{

    if(argc<=1)//  Check argument count first
    {
        printf("Error: Invalid arguments!\n"); //printing error message
        printf("Expected syntax :\nFor View please pass like : ./a.out -v mp3_filename\nFor Edit please pass like :  ./a.out -e -t/-a/-A/-g/-y/-c [edit_name] mp3_filename\n");
        return e_failure; //returning 1 as error
    }
    
    if(check_operation_type(argv)==v_view)  //calling check operation function to check is it equal to view
    {
       // printf("Choosen view option\n");
        MP3 mp3_reader; 
        if(argc>3)
          {
             printf("Warning: more input arguments!\n"); //printing warning message
          }
        if(read_and_validate_view_args(argv,&mp3_reader) == e_success) //calling function which is to validate command line arguments
        {
           // printf("Read and validate is Successfull\n");

        }
        else
        {
             printf("Read and validate is Unsuccessfull\n");
             return e_failure;
        }

        view_mp3(&mp3_reader);
    }
    else if(check_operation_type(argv)==e_edit)//calling check operation function to check is it equal to edit
    {
       // printf("You have choosen edit\n");
        if(argc>6)
        {
           printf("Warning: more input arguments!\n"); //printing warning message
        }
        MP3 mp3_reader;
        if (read_and_validate_edit_args(argv, &mp3_reader) == e_success)//calling function which is to validate command line arguments
        {
            printf("-----------Edited Successfully-----------\n");
        }
        else
        {
             printf("Read and validate is Unsuccessfull\n");
             return e_failure;
        }
    }
    else if(check_operation_type(argv)==h_help)
    {
        printf("------------HELP------------\n\n");
        printf("-t\tModifies a title tag\n-a\tModifies an artist tag\n-A\tModifies an Album tag\n-y\tModifies a year tag\n-c\tModifies a comment tag\n-g\tModifies a genre tag\n-h\tDisplays this help info\n");

    }
    else //if it is not -e or -d it is unsupported
    {
        printf("It is unsupported\n");
        return e_failure;
    }
    return e_success;
}

/* Check operation type */
OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1],"-v")==0) //checking command line argument wheather it is -e
    {
        return v_view;
    }
    else if(strcmp(argv[1],"-e")==0) //checking command line argument wheather it is -d
    {
        return e_edit;
    }
    else if(strcmp(argv[1],"-h")==0) //checking command line argument wheather it is -d
    {
        return h_help;
    }
    else //if it is not -v or -e it is unsupported
    return e_unsupported;
}