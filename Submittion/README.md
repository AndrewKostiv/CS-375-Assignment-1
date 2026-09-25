## b1
Merge sort the input array (n log n).
Use two loops through the array to get every pair of elements (n^2),
and binary search from the difference of those elements (log n).
If theer is a difference element, add it to the answer array.
Time complexity: n^2 log n.


## b2
Merge sort the input array (n log n).
Loop through each element and binary search for the difference 
of that element with the given int (n log n).
Time complexity: n log n.
