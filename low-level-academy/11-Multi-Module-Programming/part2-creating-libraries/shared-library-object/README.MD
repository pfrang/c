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
