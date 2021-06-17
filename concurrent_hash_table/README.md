# Hash Hash Hash

Three versions of making a hash table implementation safe to use concurrently.

## First Implementation

For the first implementation, we put a mutex in the hash_table_v1 struct. In other words, we have a single mutex for the entire hash table. The mutex will be initialized when we are creating the hash table. Then each thread will acquire the lock immediately after it is in the hash_table_v1_add_entry function. It will unlock after the new node is inserted if the input value does not already exist. Otherwise, it will unlock after the value is updated. This strategy is correct because there is always only one single thread that runs the critical section, which is the body part of the hash_table_v1_add_entry function since it is making write operation. Therefore, they will not be any data racing, and the hash table will not have any missing values. 

### Performance

We run "./hash-table-tester -t 8 -s 50000" such that the base hash table completes in 1-2 seconds. Now, hash table v1 runs 29% slower than the base hash table. Hash table v1 only uses one single mutex to solve the data races. Since there is always only one thread that performs the read/write operation and handles threads take time, it is slower than the base hash table. For a low number of threads, we run "./hash-table-tester -t 2 -s 200000" and it takes 1,434,672 usec. For a high number of threads, we run "./hash-table-tester -t 16, 25000" and it takes 1,445,780 usec. There is no significant difference between the two since there is always only one thread adding new elements to the hash table at a time.

## Second Implementation

We use multiple mutexes for the second implementation, so we put a mutex in the hash_table_entry struct. In other words, we have a mutex for each of the entries in the hash table. Mutexes will be initialized when we are creating their corresponding entries. In the hash_table_v2_add_entry function, we first get the hash table entry where the key is located. Then we have access to the mutex corresponding to this entry. The thread that runs the current function will acquire the lock immediately and unlock it after the new node is inserted if the input value does not already exist. Otherwise, it will unlock after the value is updated. This strategy is correct because the read/write operations on different hash table entries are mutually exclusive. Therefore, running multiple threads simultaneously will not cause any data races as long as they work on different hash table entries.

### Performance

We run "./hash-table-tester -t 8 -s 50000" such that the base hash table completes in 1,354,516 usec. We are using four cores here. Hash table v2 takes 511,415 usec in this case, 62% faster than the base one. For a low number of threads, we run "./hash-table-tester -t 2 -s 200000" and hash table v2 takes 852,500 usec, 42% faster than hash table v1  and 31% faster than the base. For a high number of threads, we run "./hash-table-tester -t 16, 25000" and it takes 570,537 usec, 69% faster than hash table v1 and 51% faster than the base. The speed of hash table v1 is significantly higher than the base hash table and hash table v1. The main reason for this increase in performance is that multiple threads(depending on the number of cores) could work simultaneously as long as the elements they add to the hash table do not belong to the same hash table entries. Since we put mutexes on hash table entry and operations on different entries are mutually exclusive, this implementation is correct and threads safe. 

## Cleaning up

To clean up, simply run "make clean" in the same directory.
