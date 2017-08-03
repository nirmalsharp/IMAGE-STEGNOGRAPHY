#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "skel.h"

char length;

int main(int argc, char *argv[])
{
    FILE *source, *des , *secret;
    int condition;
    int second_condition;
    char magic_pattern[2] = "@!";



    condition = strcmp("-e", argv[1]);

    /******************check condition****************/
    if (condition == 0) 
    {
	if (argc < 5)
	{
	    printf("arguments passing error\n");
	    exit(0);
	}

	source = fopen(argv[2], "r");

	des = fopen(argv[3], "w");

	secret = fopen(argv[4], "r");

	length = strlen(magic_pattern);

	char magicstr[length];

	strcpy(magicstr, magic_pattern);

	//puts(magicstr);
	//printf("length is %d\n", length);

	if (source == NULL)
	{
	    printf("read file error\n");
	    return 0;
	}

	if (des == NULL)
	{
	    printf("write file error\n");
	    return 0;
	}

	if (secret == NULL)
	{
	    printf("secret file error\n");
	    return 0;
	}

	flag1 = sizecheck(secret, source);

	if (flag1 == SUCCESS)
	{
	    printf("space available\n");
	}
	else
	{
	    printf("no space available\n");
	    return 0;

	}

	flag = header_copy(source, des);

	if (flag == SUCCESS)
	{
	    printf("image file copied\n");
	    magicpattern_length(des, length);
	    magicpattern(des, magicstr, length);
	    encode_file_size(des, secret);
	    encodefile(des, secret);
	    encode_file_fmtsize(des);
	    encode_extension(des);
	    //encode_remain_data(source, des);


	}
	else
	{
	    printf("not copied\n");
	}    


	fclose(source);
	fclose(des);
	fclose(secret);

    }



     
    /**********check second condition********/
    second_condition = strcmp("-d", argv[1]);

    if (second_condition == 0)
    {
	source = fopen(argv[2], "r");

	char des[100];
	strcpy(des, argv[3]);

	decode(source);

	decode_file(source);

	decode_len(source, des);

	fclose(source);

    }

}



