#!/bin/bash
gcc run.c -o run
gcc run2.c -o run2
gcc lseek.c -o lseek
gcc -pthread fast.c -o fast