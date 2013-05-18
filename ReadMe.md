*All stuff contained is user-implemented algorithms depicted in the book Introduction to the Design and Analysis of Algorithms, and most of which can be considered as the candidates for solutions to exercises*

*For any other solutions to exercise, please see at http://sdrv.ms/WVfgNY*

##Chapter 3: brute-force approach
+ `CountSpecificSubStr. ch3.2 exer 9`
   counting the number of substrings begnining and ending with a specified letter respectively within a given string. 
>e.g. CABAAXBYA has 4 substrs begining with letter A and ending with letter B.
		
+ `PartitionElements. ch3.4 exer 6`
partition n positive integers into two disjoint subsets with the same sum of their elements.
>e.g. {4,2,1,8,6,9} PART I:{6,9} PART II:{4,2,1,8}
		

##Chapter 4: divide-and-conquer algorithms
+ `FindLargeElePos. ch4.1 exer 1`
a divide-and-conquer algorithm for finding a position of the largest element in an array of n numbers.
		
+ `FindLargestSmallestPair. ch4.1 exer 2`
divide-and-conquer/brute-force algorithms for finding both the largest and smallest elements in an arry.
		
+ `Exponent. ch4.1 exer 3`
compute a^n where a > 0 and n is a positive integer.
		
+ `BottomUpMergeSort. ch4.1 exer 10`
a bottom-up implementation of merge sort without recursions.
		
+ `PartRealNum. ch4.2 exer 8`
rearrange elements of a given array of n real numbers so that its negative elements precede all its positive elements.
		
+ `ArrangeDutchFlag. ch4.2 exer 9`
rearrange any array of characters R, W, and B, thus all R's come first, the W's come next, and the B's some last.
		
+ `MatchNutsAndBolts. ch4.2 exer 10`
solve the match problem of a collection of n distinct nuts and bolts.

+ `BinSearchRange. ch4.3 exer 6`
Find all elements in a sorted array whose values fall between two given values L and U (inclusively), L <= U
		
+ `BinarySearch. ch4.3 exer 8`
two-way comparison version of binary-search
		
+ `ConstructBinTree. ch4.4 exer 8`
construct a binary tree by using its inorder and postorder traversal sequences.
		
+ `FindClosestPair. ch4.6 exer 3`
an implementation of closest-pair problem.


##Chapter 5: decrease-and-conquer algorithms.
+ `PowerSet. ch5.1 exer 3` 
generator power-set of a given list.

+ `BinInsert ch5.1 exer 9`
binary insertion soring algorithm.

+ `ShellSort ch5.1 exer 10`
shellsort implementation.

+ `dfs`
a quick dfs implementation.

+ `dfs_iter`
non-recursive implementation.

+ `bfs`
a quick bfs implementation.

+ `IsBipartite`
check a graph is a bipartite or not.

+ `TopoSort_DFS`
a tolological-sort implementation based on DFS.

+ `TopoSort`
a widely applied tolological-sort implementation based on source removing strategy.

+ `GenPermu`
navie implementation for generating permutations. recursively apply decrease-and-conquer.

+ `GenPermuLexic`
a lexical generation implementation.

+ `GenPermuJTrotter`
Johnson-Trotter implementation.

+ `GenPowerSets`
yet another powersets generation implementation based on one-to-one binary representation.