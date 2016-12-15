# Map_navigator_DSP
This program finds the shortest path to the destination when provided with a map of co-ordinates and queries.
This program needs 2 input files.
 
The first input file is a list of all the vertices and their co-ordinates , this is followed by a list of all the connections between vertices(edges).
<Example> 
5 4
0 34 34
1 22 2
2 33 33 
3 12 44
4 9 8
0 1
1 2 
2 3
3 4
</Example>

The 5 conveys the number of vertices and the 4 conveys the number of connections.

The second input file contains a list of queries.
<Example>

3
0 1
0 4
2 0

</Example>

The initial 3 denotes the number of queries to follow. In the following line 0 depicts the current location and 1 is the desired destination.
