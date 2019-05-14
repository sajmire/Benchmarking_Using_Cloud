BENCHMARKING
This project aims at Benchmarking AWS t2.micro instance for its CPU, MEMORY, DISK and NETWORK.

CPU Benchmarking
This program calculates the Integer and Floating point operations, in terms of GIOPS and GFLOPS. The main aim is to utilize the complete CPU cycles by executing different arithmetic instructions. Utilizing the CPU’s Floating point unit (FPU) completely so that it gives us the maximum FLOPS.

DISK Benchmarking
The design includes implementation for 3 different block sizes i.e. 1B, 1KB and 1MB each for Sequential and Random operations. It implements 4 methods, sequential read & write and random read & write. The sequential access is done using a file, and data is read from the file and written into it, in a sequential manner. For random access, a random number is generated which lies within the file size, and is seeked to that location onto that file and read and write operations are performed.

MEMORY Benchmarking
For different block sizes i.e. 1 Byte, 1 KB and 1 MB, sequential and random access to the memory is made. The disk access are made using memcpy() function which is used to perform read and write operation onto the memory.

NETWORK Benchmarking
The benchmarking is done for both TCP as well as UDP protocol. The code is written to be executed on two different instances of AWS. This code does the basic packets transmission from Client to Server and back again, while implementing this we find the RTT of the transmission. The packets transmitted are of various sizes i.e. 1 Byte, 1KB and 1MB. The TCP being reliable and connection oriented requires pre connection setup and accepting of connection between client and server. On the other hand UDP being connection less, the packets are sent and received without and pre established connection.
