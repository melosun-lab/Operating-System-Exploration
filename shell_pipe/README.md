# Pipe Up

Pipe Up is the low level implementation of the pipe (|) operator in shell, executing each command line arguments, which are executables, in a new process.

## Running

To run this program after build, run the executable follow by the names of executables to pipe up. For example, to pipe ls, cat, and wc like ls | cat | wc in shell, run "./pipe ls cat wc". If only one execatable name is passed, no need to pipe up, simply execuate it. 

## Cleaning up

To clean up, simply run "make clean".
