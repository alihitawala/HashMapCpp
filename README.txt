Execution instructions:
1. Compilation : make
2. Execute : ./main <input_file> <output_file>

Buckets:
The number of buckets in my implementation is 100 (default) as it a good mix to handle the sparse key case (data3.dat) as well as the dense key (collisions) case (data1.dat).
The hash function tries to reduce the collision by spreading the string over the buckets evenly. I am also handling the case when the string has the same characters but differs in the position. Hence, "ab" will have a different key than "ba".

Hash Function:
    let the string be s(1)...s(i)...s(n), bucket size be m and seed value be p (will be a prime number)
    initially, hash = 0
    then,
        hash = hash * p + ASCII(s(i)), for i = 1 to n
    return hash % m

Optional third argument:
We can also take optional third argument from the user if he wants to use his own bucket size and keep the default bucket size to 100.