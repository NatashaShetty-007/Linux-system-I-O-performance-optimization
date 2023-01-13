*OS Final Project*

*Goal:*

The goal of this final project to understand and optimize disk I/O performance by experimenting with different file sizes, block sizes, and system calls. The project is divided into three main parts:

1. Writing a program that can read and write a file from disk using the standard C/C++ library's *open*, *read*, *write*, and *close* functions, with parameters for the file name, file size, and block size.
2. Finding a file size that can be read in a "reasonable" time (between 5 and 15 seconds) by starting with a small file size and doubling it until the desired time range is reached.
3. Measuring and reporting performance in MiB/s (megabytes per second) and creating a graph that shows performance as various parameters are changed. Extra credit may be earned for trying to make the program work on xv6, but the largest file size that xv6 can handle is 70KB, so it will not be suitable for the full project requirements.

*Requirements:*

The environment for this project is real Linux (we recommend using a recent Ubuntu distribution, but any recent distribution should work).

*Part 1: Basics*

In this part, you will write a program that can read and write a file from disk using the standard C/C++ library's *open*, *read*, *write*, and *close* functions. The program should have the following parameters:

- The file name
- The size of the file (for writing)
- The block size (for reading)

You can run the program using the following command:

*./run \<filename\> [-r|-w] \<block\_size\> \<block\_count\>*

- The -r flag is used for reading the file, and the -w flag is used for writing the file.
- The block\_size parameter specifies the size of each block to be read or written.
- The block\_count parameter specifies the number of blocks to be read or written.

The program should output the performance of the read or write operation in MiB/s or bytes/sec.

*Part 2: Measurement*

In this part, you will write a program to find a file size that can be read in a "reasonable" time (between 5 and 15 seconds). The program should take the following inputs:

- The file name
- The block size

You can run the program using the following command:

*./run2 \<filename\> \<block\_size\>*

The program should output the block count for which the time taken is between 5 and 15 seconds, along with the XOR value of the content read, the file size, and the performance of reading the file in MiB/s or bytes/sec.

*Part 3: Raw Performance*

In this part, you will make your program output the performance it achieved in MiB/s and create a graph that shows its performance as you change different parameters.

*Additional instructions:*

- Before running the program, make sure to specify the appropriate file name, block size and block count as per your requirement.
- If you want to run the program on xv6, you will need to make some changes to the code as xv6 has some limitations and can only handle file sizes up to 70KB.

Enjoy experimenting and optimizing disk I/O performance!

*How to run*

*./buld.sh*

Please make sure that the build file has executable permission in the running OS.
