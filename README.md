# IMAGE-STEGNOGRAPHY
this project is about hiding the information inside the image using c 

project is developed in ubuntu
the project having main file and sub files 
compile the files using gcc command
gcc main.c cpoy.c decode.c skel.h

SAMPLE INPUT:
./a.out -e nirmal.bmp steg.bmp Low.jpg
now the Low.jpg file is encoded inside steg.bmp

./a.out -d steg.bmp hidden
now the image file inside steg.bmp is decoded as hidden.jpg

the magic string password is @!
