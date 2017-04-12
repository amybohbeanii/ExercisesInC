
### creating an archive

#### encrypt and checksum are stored in file archive named libhfsecurity
```
ar -rcs libhfsecurity.a encrypt.o checksum.o
```
#### compiling
```
gcc test_code.c -lhfsecurity -o test_code
```
#### if you saved archive somewhere else
```
gcc test_code.c -L/my_lib -lhfsecurity -o test_code
```
#### fixing makefile example. bank vault program uses these include statements
 * #include <encrypt.h>
 * #include <checksum.h>

#### makefile to build archive
```
encrypt.o: encrypt.c
	gcc -c encrypt.c -o encrypt.o
checksum.o: checksum.c
	gcc -c checksum.c -o checksum.o
libhfsecurity.a: encrypt.o checksum.o 
	ar -rcs libhfsecurity.a encrypt.o checksum.o
bank_vault: bank_vault.c libhfsecurity.a
	gcc bank_vault.c -I.-L.-lhfsecurity -o bank_vault
```


#### more examples
 *  -c creates object file doesnt link it
 *  -L tells compiler where library is stored
 *  building program using elliptical.o and the library
 *  run: ./elliptical
```
1) create object file call hfcal.o and hfcal.h header is stored in ./includes
gcc -I./includes -c hfcal.c -o hfcal.o
2) create object file called elliptical.o
gcc -I./includes -c elliptical.c -o elliptical.o
3) create archive
ar -rcs ./libs/libhfcal.a hfcal.o
4) create elliptical executable
gcc elliptical.o -L./libs -lhfcal -o elliptical
```

#### dynamic libraries
 * pg374 -fPIC flag. 
 * -shared option tells gcc to convert .o into dynamic library
```
1) compile hfcal.c into .o file
gcc -I/includes -fPIC -c hfcal.c -o hfcal.o
2) create dynamic library
gcc -shared hfcal.o -o
3) create object file called elliptical.o
gcc -I\include -c elliptical.c -o elliptical.o
4) create elliptical executable
gcc elliptical.o -L/libs -lhfcal -o elliptical
```
#### continued example
 * hfcal_UK.c and header files #include <stdio.h> #include <hfcal.h>
 * compiling into /usr/local/lib directory
```
1) compile hfcal_UK.c into .o file
gcc -c -fPIC hfcal_UK.c -o hfcal_UK.o
2) create dynamic library
gcc -shared hfcal.o -o /usr/local/lib/libhfcal.so
```
#### using libraries
 * -lblah looks for an archive named libblah.a
 #### pros/cons of static and dynamic linking?
  * static linking is done at compile time
  * dynamic linking is done at load time
  * shared libraries reduce size of programs
  * load and run time performance is enhanced
  * con is program is must slower.
  * con is reduction in locality of reference. Libraries may be scattered widely in virtual address space.
  * major conn for dynamically linked programs is the dependency on compatible library. If library is changed, applications have to be reworked to be compatible with  new version of library or if its removed, then programs using that library wont work at all.
