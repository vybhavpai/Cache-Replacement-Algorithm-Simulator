# Cache Simulator - CO262 Course Project

This project is a Cache Simulator designed specifically to analyze the performance of Advanced Cache Replacement Algorithms.
The simulator is a cpp program which can simulate cache replacement algorithms like :

1. **SRRIP** : Static Re-Reference Interval Prediction
2. **LRU** : Least recently used
3. **NRU** : Not recently used
4. **LFU** : Least frequently used
5. **FIFO** : First in first out
6. **PLRU** : Pseudo Least recently used
7. **ARC** : Adaptive replacement cache

## Getting Started

Make sure you have the latest g++ compiler installed on your system. 

Clone this github repository
```
git clone https://github.com/vybhavpai/Cache-Replacement-Algorithm-Simulator
```

Download the traces from here (Click on Link to download):

[Trace - Row Major Matrix Multiplication](https://drive.google.com/file/d/1viGRAZkzUvzrNrUiYOA42nElUwS1nFUn/view?usp=sharing)

[Trace - Tile](https://drive.google.com/file/d/1J49hOVCSa9gYWp6RfiMak3rpQK4eO4rV/view?usp=sharing)

[Trace - Regular Matrix Multiplication](https://drive.google.com/file/d/1y1uNGA7qtNni4sdb7fW5AME5Qyo_1gva/view?usp=sharing)

After downloading the traces move them into the repository.


### Simulate Cache Replacement Algorithm

To compile and run the simulator on traces:

Step 1 : 
```
$ g++ simulator.cpp
```
Step 2:
```
$ gzip -dc (trace_name.gz) | ./a.out (replacement_algorithm in small) (no_of_ways) (block_size)
```
Step 3: 
```
Wait for 15 - 20 minutes for each simulation. 
```

### Example
```
$ g++ simulator.cpp
$ gzip -dc trace_tile.gz | ./a.out srrip 2 32

Now wait for some time.....
```
The result will appear something like this:
```
103284902 is number of hits 103745282 is total input
0.995562 is hit ratio
73678224 is number of reads 
30067058 number of writes 
456979487 is total number of clock cycles
```


```
That's all folks!!!
```

## Authors

* **Vybhav Pai**   - *171CO252* 
* **Avakash Bhat** - *171CO110* 
* **Shrinidhi Varna**   - *171CO145*
* **Ankit Jain**   - *171CO208*
* **Abhinav P Y**   - *171CO103*
* **Arqum Shaikh**   - *171CO241* 
* **Chaitany Pandiya**   - *171CO112* 

## Acknowledgments

* Thanks to **Dr. Basavaraj Talwar** our course instructor for CO262 - Systems Programming for giving us a chance to do this project. 
* Thanks to **Leslie Monis** and **Aditya Kamath** for helping out with problems.


