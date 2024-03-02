A program can be compiled as a shared object, .so or a static object, .o




STATIC OBJECT
 - will increase the ELF, but everythign will be compiled into one ELF
- Doesnt need to create a link, its compiled at runtime to same ELF

Compile process:
	- gcc -o lib.o -c lib.c = Create a file into an intermediary object
	- ar rcs libtee.a lib.o = Create the archive file libtee.a
	- mv libtee/libtee.a .
	- gcc -o main main.c libtee.a -Ilibtee/

SHARED OBJECT
	- A separate ELF and gets loaded AT RUNTIME (but they are in same memory space)
	- Will create a link at runtime
Compile process:
	- gcc -o libtee.so lib.c -shared
	- do file libtee.so to ensure it is a LSB shared object
	- mv libtee/libtee.so .
	- gcc -o main main.c -Ilibtee -ltee -L$(pwd) = -L$(pwd) tells to add current directory for list of header files to search through. Usually just goes to /usr/lib
  - OR gcc -o main main.c -Ilibtee ./libtee.so, but this is not as "dynamic" to link to multiple files etc

  - In order to run it from cd, having the so file still there run command below to set an ENV variable for where libraries should be searched for. Adds the current directory $(pwd)
    -  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd) ./main

Lets add this library to default place it searces for in /usr/lib

  - INSTALL the lib: sudo mv (or cp) libtee.so /usr/lib
  - Now simply run ./main and it doesnt need the env
