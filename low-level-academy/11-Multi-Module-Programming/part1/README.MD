



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

On investigating the new outputfile you can see its a linked file

file bin/newout

---MAKEFILE----

To automate the tidy process above make a file with no extension

The $(TAREGT) rule references the object rule

$? represents a list of all input files given as a target
$< represents a single file given as a target
$@ represents the target of the rule

- make clean
- make (or make default to compile)


./bin/final mydb.db
