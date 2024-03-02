



This is a good setup for a proejct where

- /include includes al header files
- / src contain all code / functionaloity
- /bin will contain the binary

To compile each and every individual file before they are lniked together

- gcc -o file.o -I$(pwd)/include src/file.c -c
- gcc -o parse.o -I$(pwd)/include src/parse.c -c
- gcc -o main.o -I$(pwd)/include src/main.c -c

The -c flag here tells that it shouldnt link yet, only compile

We now have 3 object file, each for every file

 - move them: mv *.o obj/
 - compile them to one binary: gcc bin/*.o -o bin/newout

On investigating the new outputfile you can see its linked

file bin/newout

file bin/newout                                                                                                    ✔  11:20:09  
bin/newout: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=05495bc293fbefc4c6777f4da1c2fb520fec2749, for GNU/Linux 3.2.0, not stripped



---MAKEFILE----

To automate the tidy process above make a file with no extension

The $(TAREGT) rule references the object rule

The $< means the input file
$@ means the output file

- make clean
- make (or make default to compile)


./bin/final mydb.db
