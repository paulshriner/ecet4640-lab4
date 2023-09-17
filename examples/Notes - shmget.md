Note to professor:

[This](https://stackoverflow.com/questions/25514599/deallocating-shared-memory-segment) stackOverflow answer claims:

> If you're on Linux, you should consider using the POSIX shared memory system (shm_open, shm_unlink), which mostly uses the standard POSIX file API (mmap, ftruncate, etc.) to interact with shared memory regions. It's also noted as being more modern as the old SYSV interface that you're using.


# shmget

[Link to man page](https://man7.org/linux/man-pages/man2/shmget.2.html)

`shmget` is part of the standard C library. It allocates a System 5 shared memory segment.

Note: System V was first developed in 1983. "System V" is virtually synonymous with 'core linux/unix feature' at this point.

This command can:
- Get the identifier of a previously created shared memory segment
- Or, create a new one.

```c
int shmget(key_t key, size_t size, int shmflag)
```

## Getting an existing

To get:
- the parameter `shmflag` must be 0.
- the parameter `key` must not be `IPC_PRIVATE`

```c
int key = 0x1234;
int shm_id = shmget(key, 0, 0);
if (shm_id == -1) {
    printf("%i", errno);
    perror("shmget()");
}
```

## Creating

This will allocate a segment of shared memory equal to `size` bytes in size, rounded up to the nearest multiple of `PAGE_SIZE`.


```c
int key = 0x1234;
int pointer = shmget(key, sizeof(int), IPC_CREAT | 0666);
if(shm_id == -1) {
    printf("%i", errno);
    perror("shmget()");
}
```
