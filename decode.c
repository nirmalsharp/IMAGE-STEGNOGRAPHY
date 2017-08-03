#include <stdio.h>
#include "skel.h"
#include <string.h>
#include <stdlib.h>

#define GETBIT(x, y)  (x & (1 << y))
#define SETBIT(x, y)  (x | (1 << y)) 
#define CLEAR(x, y)  (x  & (~(1 << y)))

int msu[2000000];
int filesize;

/*this function is about decoding magicstring length*/
int decode (FILE *source)
{
    char magic_str[5];
    char lengthbuffer[8];
    char magicbuffer[16];
    printf("enter the magic string:");
    scanf("%s",magic_str);
    char length;
    length = strlen(magic_str) + 48;

    fseek(source, 54L, SEEK_SET);
    fread(lengthbuffer, 8, 1, source);

    int i, idx;
    int strcheck; 
    char num;
    int a_num;
    int pos;
    char ch = 0;
    char ms[2];

    for( i = 0; i < 8 ; i++)
    {

	lengthbuffer[i] = ((GETBIT(lengthbuffer[i], 0)) + 48);
	pos = 7 - i;
	if (lengthbuffer[i] == 49)
	{
	    ch = SETBIT(ch , pos);

	}
	if(lengthbuffer[i] == 48)
	{
	    ch = CLEAR(ch, pos);
	}

    }


    ch = ch + 48;
    printf("string length is %c\n",ch);

    if(length != ch)
    {
	printf("string length is not equal\n");
	exit(0);

    }
    else
    {
	printf("string length is equal\n");

    }

    //int cursorpos = ftell(source);
    //printf("%d",cursorpos);
    int a;
    a = ch - '0';


    for (idx = 0; idx < a ; idx++)
    {
	fread(magicbuffer, 8,  1, source);
	//int cursorpos = ftell(source);
	//printf("%d",cursorpos);




	for( i = 0; i < 8 ; i++)
	{

	    magicbuffer[i] = ((GETBIT(magicbuffer[i], 0)) + 48);
	    pos = 7 - i;
	    if (magicbuffer[i] == 49)
	    {
		ms[idx] = SETBIT(ms[idx] , pos);


	    }
	    if(magicbuffer[i] == 48)
	    {
		ms[idx] = CLEAR(ms[idx], pos);
		//printf("%c",st);
	    }
	    //printf("%c", magicbuffer[i]);



	}
    }
    ms[idx] = '\0';
    //puts(ms);

    strcheck = strcmp(magic_str, ms);
    if (strcheck == 0)
    {
	printf("magic string accepted\n");
    }
    else
    {
	printf("magic string not accepted\n");
	exit(0);
    }


}


/*this function is about decoding file*/
int decode_file(FILE *source)
{
    char lengthbuffer[64];
    char magicbuffer[64];
    char ms[100000];
    int i; 
    int pos = 0;														
    unsigned long c = 0;

    fread(lengthbuffer, 32, 1, source);



    for( i = 0; i < 32 ; i++)
    {	
	lengthbuffer[i] = ((GETBIT(lengthbuffer[i], 0))+ 48);
	//printf("%c", lengthbuffer[i]);
	pos = 31 - i;
	if (lengthbuffer[i] == '1')
	{
	    c = SETBIT(c , pos);


	}
	if(lengthbuffer[i] == '0')
	{
	    c = CLEAR(c, pos);

	}

	//printf("%c", lengthbuffer[i]);	
    }

    //printf("\nthe value is %lu",c);

    int a, idx;
    filesize = c;
    printf("length of the file is %d\n",filesize);


    for (idx = 0; idx < filesize ; idx++)
    {
	fread(magicbuffer, 32,  1, source);
	//int cursorpos = ftell(source);
	//printf("%d",cursorpos);




	for( i = 0; i < 32 ; i++)
	{

	    magicbuffer[i] = ((GETBIT(magicbuffer[i], 0)) + 48);
	    pos = 31 - i;
	    if (magicbuffer[i] == '1')
	    {
		msu[idx] = SETBIT(msu[idx] , pos);


	    }
	    if(magicbuffer[i] == '0')
	    {
		msu[idx] = CLEAR(msu[idx], pos);
		//printf("%c",st);
	    }
	    //printf("%c", magicbuffer[i]);



	}
    }

    msu[idx] = '\0';

    //printf("inside the file\n");
    //puts(msu);

}

/****decoding the length***********/
int decode_len(FILE *source, char *str)
{
    FILE *des; 

    char lengthbuffer[10];
    char magicbuffer[1000];
    char ms[1000];
    int i, pos, idx;
    char ch;

    fread(lengthbuffer, 8, 1, source);
    for( i = 0; i < 8 ; i++)
    {

	lengthbuffer[i] = ((GETBIT(lengthbuffer[i], 0)) + 48);
	pos = 7 - i;
	if (lengthbuffer[i] == 49)
	{
	    ch = SETBIT(ch , pos);

	}
	if(lengthbuffer[i] == 48)
	{
	    ch = CLEAR(ch, pos);
	}

    }
    ch = ch + 48;
    printf("length of the file extension is %c\n",ch); 


    int a;
    a = ch - '0';


    for (idx = 0; idx < a ; idx++)
    {
	fread(magicbuffer, 8,  1, source);
	//int cursorpos = ftell(source);
	//printf("%d",cursorpos);

	for( i = 0; i < 8 ; i++)
	{

	    magicbuffer[i] = ((GETBIT(magicbuffer[i], 0)) + 48);
	    pos = 7 - i;
	    if (magicbuffer[i] == 49)
	    {
		ms[idx] = SETBIT(ms[idx] , pos);


	    }
	    if(magicbuffer[i] == 48)
	    {
		ms[idx] = CLEAR(ms[idx], pos);
		//printf("%c",st);
	    }
	    //printf("%c", magicbuffer[i]);



	}
    }
    ms[idx] = '\0';
    printf("the format is ");
    puts(ms);

    //printf("%d", filesize);

    int check, check1, check2;
    check = strcmp("txt", ms);
    check1 = strcmp("jpg",ms);
    check2 = strcmp("mp3",ms);

    if (check == 0)
    {
	des = fopen(strcat(str , ".txt"), "w");
	fwrite(msu, 1, filesize, des);
    }

    if (check1 == 0)
    {
	des = fopen(strcat(str , ".jpg"), "w");
	fwrite(msu, 1, filesize, des);
    }

    if (check2 == 0)
    {
	des = fopen(strcat(str , ".mp3"), "w");
	fwrite(msu, 1, filesize, des);
    }


    fclose(des);

}



