# Cache-Memory-Implementation
This project simulates a cache memory system using C programming, featuring dynamic memory allocation, file handling for configuration and access patterns, and implementation of different cache replacement policies.

    Setup and Initialization: The program reads cache parameters (cache_size, block_size, ass, rep_pol, wrt_pol) from cache.config to configure the cache size, block size, associativity, replacement policy, and write policy.

    Cache Structure: It dynamically allocates memory for a 2D array cache representing the cache sets and associativity. Each entry (struct set) in the cache includes fields for tag, validity, and access time.

    Access Simulation: The program reads memory access patterns (mode, line) from cache.access, computes set index and tag based on cache parameters, and simulates cache search operations (cachesearch). It tracks cache hits and misses and implements specified replacement policies (LRU, FIFO, RANDOM) when handling cache misses.

    Replacement Policies: Implemented replacement policies ensure efficient cache management:
        LRU (Least Recently Used): Replaces the least recently accessed cache line.
        FIFO (First In, First Out): Replaces the oldest cache line.
        RANDOM: Replaces a random cache line.

    Output: For each memory access, the program outputs whether it resulted in a cache hit or miss, along with the accessed address, set index, and tag. At the end of simulation, it prints total hits and misses.
