#ifndef MP3_H
#define MP3_H

#include "types.h"

typedef struct _MP3
{
    /* Mp3 file info */
    char *mp3_fname;
    FILE *fptr_mp3;
    
    /*Duplicate file info*/
    char *mp3_dupe;
    FILE *duplicate;

} MP3;

/*  Function prototype */
/* Check operation type */
OperationType check_operation_type(char *argv[]);

/* Read and validate view args from argv */
Status read_and_validate_view_args(char *argv[], MP3 *mp3_reader); //check the file is there in command line

/* Get File pointers for i/p and o/p files */
Status open_files(MP3 *mp3_reader);

/* For view of mp3 contents*/
Status view_mp3(MP3 *mp3_reader);

/* Read and validate edit args from argv */
Status read_and_validate_edit_args(char *argv[], MP3 *mp3_reader); //check the file is there in command line

/* Edit mp3 contents */
Status edit_mp3(char *data,MP3 *mp3_reader,char *argv[]) ;

/* Get File pointers for i/p and o/p files */
Status open_edit_files(MP3 *mp3_reader,char *argv[]);

Status copy_remaining_data(FILE *fptr_mp3, FILE *duplicate);
#endif 