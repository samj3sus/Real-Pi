# uCOS-II on Raspberry Pi

This is a very basic port of uCOS-II to Raspberry Pi. The version of uCOS-II used is V2.52.  

## Contents of each fold

bsp：Board support package. Handle interrupt,uart and timer
build：Store obj files generated during compilation
h：Head files
init：Startup code
lib：Library for standard c and libc 
port：Porting code 
ucos：Source code of uCOS-II.Here we don't proive the source code, and you can get the code from http://www.micrium.com
usrApp： Contains main functions and where to place the examples provided by Jean Labrosse. 


## How to make
First, you should put the source code of uCOS-II in the fold "ucos". Place the uCOS header files in he uCOS subfolder in the main h directory

For Windows: Download the yagarto toolchain. Then you can make directly.
For Linux: Get the toolchain, You maybe need to rewrite the makefile according to the toolchain used.