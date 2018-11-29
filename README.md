# Implementation of Probabilistic Data Structures

## Probabilistic Data Structures Implemented
* HyperLogLog - Abhiram Bellur (01FB16ECS013)

* Count-Min Sketch - Nakul Srivathsa (01FB16ECS219)

* Bloom Filters - Priya S Nayak (01FB16ECS277)

## Files Included
### General
* final_main.cpp - All functions are called here.

* print.cpp - Required to print the beginning of the project.

* make.mk - Make File used for compiling

* dictionary.txt - text file containing around 30k+ words from the English dictionary

* Harry_Potter.txt - text file containing excerpts from the seven Harry Potter books.

* Julius_Caesar.txt - text file containing 5 acts from the Julius Caesar book.

### For HyperLogLog
* hyperLogLog.h - used to define the HyperLogLog Class, add to the HyperLogLog, and calculate the harmonic mean.

* hyperLogLog.cpp - functions to add to the HyperLogLog, to obtain Cardinality, and some helper functions.

### For Count-Min Sketch
* CountMinSketch.hpp - define the CountMinSketch Class and initialize the related functions.

* CountMinSketch.cpp - functions to create the count-min sketch and to count the frequency of a particular word.

### For Bloom-Filters
* bloom.h - define the Bloom Filter Class, set the size of the table, and initialize the related functions.

* bloom.cpp - create bloom filter and maximise quality of distribution.

## Compiling and Executing

Run the make file to compile.
```
make -f make.mk
```

Execute by using the object file created.
```
./project
```
