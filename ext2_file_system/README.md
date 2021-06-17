# Hey! I'm Filing Here

This program is a 1MB ext2 file system with 2 directories, 1 regular file, and 1 symbolic link.

## Building

To build this program, simply run `make` in the current working directory.

## Running

After successful build, run `./ext2-create` to construct the cs111-base.img file. Then, run `mkdir mnt` to make a directory and mount the file system with `sudo mount -o loop cs111-base.img mnt`. One example output of 'ls -ain' the mounted file system is:

total 7
     2 drwxr-xr-x 3    0    0 1024 Jun  4 13:51 .
145577 drwxr-xr-x 3 1000 1000 4096 Jun  4 13:56 ..
    13 lrw-r--r-- 1 1000 1000   11 Jun  4 13:51 hello -> hello-world
    12 -rw-r--r-- 1 1000 1000   12 Jun  4 13:51 hello-world
    11 drwxr-xr-x 2    0    0 1024 Jun  4 13:51 lost+found

## Cleaning up

To unmount the file system, run `sudo umount mnt` in the parent directory of mnt. Then run `rmdir mnt` to remove the mount directory. Finally, run `make clean` to clean up all binary files.
