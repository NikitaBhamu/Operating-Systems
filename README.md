# OperatingSystems

## Adding Syscall in Linux :
Understanding the build process of a modern kernel, walkthrough the procedure of adding a system call and the Software Engineering discipline required in Kernel coding.

## Printing Prime using Parallel Programming :
A multi threaded program implemented using a Use Level thread package (pthreads) that outputs all prime numbers upto N (10^10) using t threads, where N and t are command line (input) arguments. 
Two approaches are used to parallelise the program  :
1) Naive approach :
   In this approach the domain [2...N] is divided into t partitiones in which first t-1 partitions have size (N-1/t) and the last one has size (N-1/t + extra numbers) , where t is the number of thread. The first (t-1) threads gets exactly (N-1/t) number to look at whether they are prime or not.
2) Load balanced :
   In this approach the threads take a number dynamically from the number array and check it whether it is prime or not and update the corresponding result in the array which contains the booleans(0,1) which denote whether the number is prime or not.

## Page Replacement Algorithms :
The following page replacement algorithms are implemented in this assignment :-
1) FIFO
2) LFU
3) LRU 
4) Clock
5) N Chance
