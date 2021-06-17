# A Kernel Seedling

A kernel module that shows the current number of running processes.

## Building

To build this kernel module, simply run "make" command in ~/cs111/lab-00. Then, insert this kernel module by running "sudo insmod proc_count.ko"

## Running

To run it after succeful build and insertion, run "cat proc/count". The expected result should be an integer string and it should be showed on terminal.

## Cleaning Up

To remove this kernel module, simply run "sudo rmmod proc_count.ko".

## Testing

The kernel version I tested this module on is Linux 5.11.9-arch1-1 x86_64. To test this module, simply compare the result of running this module to that of running "ps -e | wc -l". Notice that there will be an offset of value 2 between those two results. In other words, the result of this kernel module should be 2 less than the result of running "ps -e | wc -l".
