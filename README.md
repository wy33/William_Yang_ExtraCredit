# Extra Credit

## Information about the repository

This repository contains the following:
- `subsequence.cc`
- `optimal_multiplcations.cc`

## Parts of the program completed

All parts completed.

`optimal_multiplcations.cc`
- Class Matrix: is a class derived from the textbook used to implement dynamic programming and calculate the costs of the different orderings of matrix multiplication. Implemented a 2 parameter constructor for the dimensions of the matrix, operator[] (both const and non-const version), and accessors for number of rows and columns.
- ReadDimensionsFile(): a function used to read the dimensions file given at the command line into a vector and returns it.
- OptimalMatrixMultiplication(): is the function where the calculations take place to obtain the optimal number of multiplcations for the given matrix dimensions. The matrix m's first row and first column is unused and is uninitialized, as well as the cells below the 0 diagonal (from upper left to bottom right). The algorithm works by using the cell below and left (already calculated to be minimum cost) of the current cell to calculate the lowest cost for the current cell. When the algorithm finishes, the cell at the 2nd row, last column (due to how the algorithm in the textbook works) of matrix m has the answer.
- multiplication_driver(): parses command line arguments and prepares the matrices and vector needed to call OptimalMatrixMultiplication() function and derive the answer. The answer will be in the costs matrix on the second row, last column (due to how the algorithm in the textbook works).

`subsequence.cc`
- Class Matrix: same as the class used in optimal_multiplications.cc.
- LongestCommonSubsequence(): is the function where the calculations take place to obtain the longest common subsequence of the two given sequences/words. This algorithm also uses a matrix to derive the answer via dynammic programming. Like the matrix used in optimal_multiplcations.cc, the first row and first column is not used and is initialized to 0 in this case during the nested loop. How the loop works is if the sequences are found to have matching characters, the current cell in the matrix adds the cell diagonal (upper left) to it and adds 1 to the current cell. If the characters are not equal, then the current cell's value is the max of the cell above or left of the current cell. When reading the matrix, the longest common subsequence's length is found at the last row, last column of the matrix. Due to the nature of how the matrix is read, the longest common subsequence is built backwards character by character. When reading the matrix and the two sequences/words, when looping through the sequences/words, if the characters are equal, then iterating variables i and j move diagonally (upper left), else the characters aren't equal, so the cells left or above of the current cell gets read next depending on which has a larger element. Each row and column is associated with the characters of each word and will be used to build the longest common subsequence. The longest common subsequence will be returned after it is built.
- subsequence_driver(): parses command line arguments and retreives the longest common subsequence by calling LongestCommonSubsequence() function and outputs the length and longest common subsequence to the terminal.


## Bugs encountered

No noticeable bugs encountered.

## Input File

`dimensions_file.txt`
`dimensions_file2.txt`

## Running the assignment

To compile both programs on terminal, type:

```bash
g++ -c subsequence.cc optimal_multiplications.cc
```

```bash
g++ -o subsequence subsequence.cc
```

```bash
g++ -o subsequence optimal_multiplications.cc
```

To delete executables and object files, type:

```bash
rm subsequence subsequence.o optimal_multiplications optimal_multiplications.o
```

Followup by typing:

```bash
y
```

and pressing enter 4 times to delete all files.

To delete individually, just put files individually after **rm** and press enter.
Then type:

```bash
y
```

and enter once to delete the individual file.

To run subsequence, type:

```bash
./subsequence <sequence 1> <sequence 2>
```

```bash
./subsequence apples oranges
```

To run optimal_multiplications, type:

```bash
./optimal_multiplications <dimensions file>
```

```bash
./optimal_multiplications dimensions_file.txt
```
