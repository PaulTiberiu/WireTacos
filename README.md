# WireTacos

## Subject
WireTacos is a project based on Wireshark. WireTacos is a network protocol analyzer and visualizer entirely coded in C. This is a project made for the network course LU3IN033 at Sorbonne Université.

## Protocols
Here is a list of network protocols that we implemented for our project:
  - Link-layer : Ethernet II (no preamble and no trailer)
  - Network-layer : IPv4, ARP, ICMP
  - Transport-layer : TCP
  - Application-layer : HTTP

## File organization
You can find all the headers (.h) in the header file, each protocol having a .h file. The .c files can be seen in the main of this git.

## Filters
We also introduced some filters in order to make an optimized search of the frames. For better understanting of how to use the filters we recommend you to read the HOW_TO.pdf document. The filters that we used are:
  - Ethernet: filter on the mac adress and the protocol used by and Ethernet frame
  - IPv4: filter on the ip adress of an IPv4 frame and the protocol that the IPv4 frame uses
  - ARP: filter on the ARP type of the frame
  - ICMP: filter on the ICMP type of the frame (echo request, echo reply, etc...)
  - TCP: filter on the TCP port number of the frame
  - Filter on the frame number

## How to use it
With the help of a makefile, you just need to write the following command in order to compile our program:
```
make
```
To execute, write:
```
./WireTacos.x
```
Then you will have a menu where, with a file, you can visualize the frames. This is also explained in the  HOW_TO.pdf document

When you are finished, you can quit the program by doing ctrl^C in the terminal and then erase the executable code with the following command:
```
make clean
```
You also have the READ_ME.pdf that explains in detail the most important functions.
We also have 2 files, test.txt which can be used to test the program, and the output.txt file wich is the flow graph of our test program.
