The first group assignment required that you implement a basic CPU scheduler; this assignment requires that you implement a basic page replacement simulator.

The name of the executable will be pager and it will take the following command line arguments:

--type: FIFO | LRU | MFU | RANDOM
--frames: number of physical frames available
--pages:  number of virtual pages available 
--framesize: the size of the frame in decimal number of bytes
a file name

As with all good command line arguments, there will be defaults for all of these

type should default to FIFO
frames should default to 3
pages should default to 8
framesize should be 512
filename is pager.in
The output should be to standard out and should indicate (at minimum) the number of page faults which occurred.

The format for the input file is simple:

process ID 
memory location 
memory location
memory location
memory location
...
memory location

 

A change from the inclass discussion---there is ONLY one process in an input file!
