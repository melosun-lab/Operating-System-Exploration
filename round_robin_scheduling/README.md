# You Spin Me Round Robin

The implementation for round robin scheduling for a given workload and quantum length.

## Building

To build this program, simply run "make" command in ~/cs111/lab-02 directory. 
To define the work load, edit the processes.txt file in the same directory with the following format. The first line should specify the total number of processes to be scheduled. Then, each of the remaining line represents a process with its pid, arrival time, and burst time. For example, for a process with pid 1 arrives at t=0 and burst 3 seconds, add a line "1, 0, 3" in the file.

## Running

To run the program after building, run the executable followed by processes.txt and the quantum length.

To define the work load, edit the processes.txt file in the same directory with the following format. The first line should specify the total number of processes to be scheduled. Then, each of the remaining line represents a process with its pid, arrival time, and burst time. For example, for a process with pid 1 arrives at t=0 and burst 3 seconds, add a line "1, 0, 3" in the file.

For example, to run the executable with the defined workload and quantum length 3, run "./rr processes.txt 3". 

## Cleaning up

To clean up, simply run "make clean" in the same directory.

