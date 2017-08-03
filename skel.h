#include <stdio.h>
#define SUCCESS 1
#define FAILURE 0

char buff[400000];
int size;
int flag;
int flag1;


/***********header prototype************/
int header_copy(FILE *source, FILE *des);
int encode(FILE *des, FILE *secret);
int sizecheck(FILE *secret, FILE *des);
int magicpattern_length(FILE *des, char size);
int magicpattern(FILE *des, char *ms, char size);
int encode_file_size(FILE *des, FILE *secret);
int encodefile(FILE *des, FILE *secret);
int encode_file_fmtsize(FILE *des);
int encode_extension(FILE *des);
int encode_remain_data(FILE *source, FILE *des);
int decode(FILE *source);
int decode_file(FILE *source);    
int decode_len(FILE *source, char *des);
