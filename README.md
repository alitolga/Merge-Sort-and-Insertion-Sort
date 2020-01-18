# Merge Sort and Insertion Sort

This code contains a merge sort and insertion sort example, which I wrote for my Analysis of Algorithms class in my 3rd year in ITU CE.

The code reads the file **log_inf.csv** and writes the sorted list to **sorted.csv** file. It also writes execution details such as the execution time into the **calcTimes.csv** file.

The code takes 6 parameters as such 

**-feature** : Sorting criterion (for timestamp ‘t’ or for last_price ‘p’). Sort the data in ascending order considering the criterion.

**-size** : Total number of items to be sorted (1000, 10000, 100000, 1000000). You can simply read first N line from the file and sort them.

**-algo** : Algorithm to be used to solve the problem (for Insertion Sort ‘i’ or for Merge Sort ‘m’)
An example execution command is given as follows:

`./myExecutable -algo m -feature p -size 100000`
