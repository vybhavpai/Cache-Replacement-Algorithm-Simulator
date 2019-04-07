The simulator is a cpp program which can simulate algorithms like :
1.SRRIP : Static Re-Referencce Interval Prediction
2.LRU : Least recently used
3.NRU : Not recently used
4.LFU : Least frequently used
5.FIFO : First in first out
6.PLRU : Pseudo Least recently used
7.ARC : Adaptive replacement cache


Download the traces from here:
https://drive.google.com/file/d/1viGRAZkzUvzrNrUiYOA42nElUwS1nFUn/view?usp=sharing
https://drive.google.com/file/d/1J49hOVCSa9gYWp6RfiMak3rpQK4eO4rV/view?usp=sharing
https://drive.google.com/file/d/1y1uNGA7qtNni4sdb7fW5AME5Qyo_1gva/view?usp=sharing
To compile and run the simulator on traces:
1. g++ simulator.cpp
2. gzip -dc (trace_name.gz) | ./a.out (replacement_algorithm in small) (no_of_ways) (block_size)

