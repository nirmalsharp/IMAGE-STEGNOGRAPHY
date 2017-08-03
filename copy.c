#include <stdio.h>
#include <stdlib.h>
#include "skel.h"

#define GETBIT(x, y)  (x & (1 << y))
#define SETBIT(x, y)  (x | (1 << y)) 
#define CLEAR(x, y)  (x  & (~(1 << y)))




//char output[10000];
int sizfile, sizimage;


/*************copy file to file**************/
int header_copy(FILE *source, FILE *des)
{
    int size;
    char ch;

    fseek(source, 0L, SEEK_SET);
    while(!feof(source))

    {
	ch =getc(source);
	if (!feof(source))

	{
	    putc(ch, des);
	}
    }

    return SUCCESS;
}

/***********************************************/

/****************checking size*****************/
int sizecheck(FILE *secret, FILE *source)
{
    fseek(secret, 0L, SEEK_END);
    sizfile = ftell(secret);
    //printf("%d\n",sizfile);

    fseek(source, 0L, SEEK_END);
    sizimage = ftell(source);
    sizimage = sizimage - 54;
    //printf("%d\n", sizimage);

    if (sizfile < sizimage)
    {
	return SUCCESS;
    }

}

/***************magic pattern length*****************/
int magicpattern_length(FILE *des, char size)
{
    int i, cursorpos;
    char ch;
    fseek(des, 54L, SEEK_SET);



    for(i=sizeof(size)*8 -1;i >= 0; i--)
    {
	if(size & (1 << i))
	{

	    ch = fgetc(des);
	    ch = SETBIT(ch , 0);
	    //fseek(des, -1L, SEEK_CUR);
	    fputc(ch, des);

	    //fseek(des, -1L, SEEK_CUR);

	    // cursorpos = ftell(des);
	    //printf("%d", cursorpos);
	    //printf("%hhx\n", ch);

	}
	else
	{
	    ch = fgetc(des);
	    ch = CLEAR(ch , 0);
	    //fseek(des, -1L, SEEK_CUR);
	    fputc(ch , des);
	    //fseek(des, -1L, SEEK_CUR);

	    //cursorpos = ftell(des);
	    //printf("%d", cursorpos);

	    //printf("%hhx\n", ch);


	}
    }

}

/***********************store magicpattern********************/

int magicpattern(FILE *des, char *ms, char siz)
{
    int idx, i, cursorpos;
    char ch;

    //printf("size is %d", sizeof(ms[0]));

    for(idx = 0; idx < siz; idx++)
    {

	for(i = sizeof(ms[idx]) *8 - 1; i >= 0; i--)
	{	
	    if(ms[idx] & (1 << i))
	    {

		ch = fgetc(des);
		ch = SETBIT(ch , 0);
		//fseek(des, -1L, SEEK_CUR);
		fputc(ch, des);
		// cursorpos = ftell(des);
		//printf("%d", cursorpos);
		//printf("%hhx\n", ch);

	    }
	    else
	    {
		ch = fgetc(des);
		ch = CLEAR(ch , 0);
		//fseek(des, -1L, SEEK_CUR);
		fputc(ch , des);
		///cursorpos = ftell(des);
		//printf("%d", cursorpos);

		// printf("%hhx\n", ch);

	    }
	}
   }
}


/***************store file size**************/

int encode_file_size (FILE *des, FILE *secret)
{
    int i, cursorpos, j = 0;
    long size;
    long ch;
    unsigned char msb, srcImageByte;
    fseek(secret, 0L, SEEK_END);
    size = ftell(secret);
    printf("size is %lu", size);


    for(i=sizeof(size)*8 -1;i >= 0; i--)
    {
	if(size & (1 << i))
	{

	    ch = fgetc(des);
	    ch = SETBIT(ch , 0);
	    //fseek(des, -1L, SEEK_CUR);
	    fputc(ch, des);
	    //cursorpos = ftell(des);
	    //printf("%d", cursorpos);
	    //printf("%lx\n", ch);
	}
	else
	{
	    ch = fgetc(des);
	    ch = CLEAR(ch , 0);
	    //fseek(des, -1L, SEEK_CUR);
	    fputc(ch , des);
	    //cursorpos = ftell(des);
	    //rintf("%d", cursorpos);

	    //printf("%lx\n", ch);


	}
    }

}  

/***********************file**************************/
int encodefile(FILE *des, FILE *secret)
{
    fseek(secret, 0L, SEEK_END);
    int size = ftell(secret);  
    int buff[100000], idx, i, ch;
    fseek(secret, 0L, SEEK_SET);
    fread(buff, size, 1, secret);   
    //puts(buff);


    for (idx = 0; idx < size; idx++)
    {
	for (i = sizeof(buff[idx])*8 -1;i >= 0; i--)
	{
	    if (buff[idx] & (1 << i))
	    {

		ch = fgetc(des);
		ch = SETBIT(ch , 0);
		//fseek(des, -1L, SEEK_CUR);
		fputc(ch, des);
		//cursorpos = ftell(des);
		//printf("%d", cursorpos);
		//printf("%lx\n", ch);

	    }
	    else
	    {
		ch = fgetc(des);
		ch = CLEAR(ch , 0);
		//fseek(des, -1L, SEEK_CUR);
		fputc(ch , des);
		//cursorpos = ftell(des);
		//rintf("%d", cursorpos);

		//printf("%lx\n", ch);

	    }
	}
    }

}
/**************file format size*************/
int encode_file_fmtsize(FILE *des)
{
    char size = 3, ch;

    int i, cursorpos;
    //cursorpos =  ftell(des);
    //printf("%d\n", cursorpos);
    for (i = sizeof(size) * 8 -1; i >= 0; i--)
    {
	if (size & (1 << i))
	{

	    ch = fgetc(des);
	    ch = SETBIT(ch , 0);
	    //fseek(des, -1L, SEEK_CUR);
	    fputc(ch, des);
	    //cursorpos = ftell(des);
	    //printf("%d", cursorpos);
	    //printf("%hhx\n", ch);

	}
	else
	{
	    ch = fgetc(des);
	    ch = CLEAR(ch , 0);
	    //fseek(des, -1L, SEEK_CUR);
	    fputc(ch , des);
	    //cursorpos = ftell(des);
	    //printf("%d", cursorpos);

	    //printf("%hhx\n", ch);


	}
    }

}

/***************file extension**************/  
int encode_extension(FILE *des)
{
    int idx, cursorpos, i;
    char ext[3] = "jpg";
    char ch;
    for(idx = 0; idx < 3; idx++)
    {

	for(i = sizeof(ext[idx]) *8 - 1; i >= 0; i--)
	{	
	    if(ext[idx] & (1 << i))
	    {

		ch = fgetc(des);
		ch = SETBIT(ch , 0);
		//fseek(des, -1L, SEEK_CUR);
		fputc(ch, des);
		//cursorpos = ftell(des);
		//printf("%d", cursorpos);
		//printf("%hhx\n", ch);

	    }
	    else
	    {
		ch = fgetc(des);
		ch = CLEAR(ch , 0);
		//fseek(des, -1L, SEEK_CUR);
		fputc(ch , des);
		// cursorpos = ftell(des);
		// printf("%d", cursorpos);

		//printf("%hhx\n", ch);


	    }
	}
    }



}
 




