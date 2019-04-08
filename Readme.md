# Cache Simulator - CO262 Course Project

The simulator is a cpp program which can simulate algorithms like :

1. **SRRIP** : Static Re-Referencce Interval Prediction
2. **LRU** : Least recently used
3. **NRU** : Not recently used
4. **LFU** : Least frequently used
5. **FIFO** : First in first out
6. **PLRU** : Pseudo Least recently used
7. **ARC** : Adaptive replacement cache


Download the traces from here (Click on Link to download):

[Trace - Row Major Matrix Multiplication](https://drive.google.com/file/d/1viGRAZkzUvzrNrUiYOA42nElUwS1nFUn/view?usp=sharing)

[Trace - Tile](https://drive.google.com/file/d/1J49hOVCSa9gYWp6RfiMak3rpQK4eO4rV/view?usp=sharing)

[Trace - Regular Matrix Multiplication](https://drive.google.com/file/d/1y1uNGA7qtNni4sdb7fW5AME5Qyo_1gva/view?usp=sharing)

To compile and run the simulator on traces:

Step 1 : 
```
g++ simulator.cpp
```
Step 2:
```
gzip -dc (trace_name.gz) | ./a.out (replacement_algorithm in small) (no_of_ways) (block_size)
```
Step 3: 
```
Wait for 15 - 20 minutes for each simulation. 
```

### Example
```
g++ simulator.cpp
gzip -dc trace_tilz.gz | ./a.out srrip 2 32

Now wait for some time.....
```
The result will appear something like this:
```
103284902 is number of hits 103745282 is total input
```

We then calculate the Hit Percentage by dividing the number of hits by total input and multiplying it with 100.

```
That'a all folks!!!
```
