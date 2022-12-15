// William Yang
// subsequence.cc: a file to find the longest common subsequence between two words
// supplied in the command line.

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;



// Class Matrix:
// A simple matrix class created to represent a matrix.
// Comes with accessors and a mutator to fill the matrx.
// Code taken from the textbook.
template<typename Object>
class Matrix
{
public:
    // 2 parameter constructor
    Matrix(int rows, int cols) : array_(rows)
    {
        for (auto& thisRow : array_)
            thisRow.resize(cols);
    }

    // Overload operator [].
    // Const version.
    const vector<Object>& operator[](int row) const
    {
        return array_[row];
    }

    // Overload operator []
    vector<Object>& operator[](int row)
    {
        return array_[row];
    }

    // Return number of rows in matrix
    int NumRows() const
    {
        return array_.size();
    }

    // Return number of columns in matrix
    int NumCols() const
    {
        return NumRows() ? array_[0].size() : 0;
    }

private:
    // The matrix
    vector<vector<Object>> array_;
};

// Calculates the longest common subsequence of the two strings (not continuous by in the same order).
string LongestCommonSubsequence(const string& word1, const string& word2) {
    // The table used to calculate the longest common subsequence.
    // The rows and columns will represent the characters of each word.
    // Row length is word1's length + 1, column length is word2's length + 1.
    Matrix<int> length_table { (int)word1.size() + 1, (int)word2.size() + 1};

    for (int i = 0; i <= word1.size(); ++i)
    {
        for (int j = 0; j <= word2.size(); ++j)
        {
            if (i == 0 || j == 0)   // 1st row and 1st column unused
                length_table[i][j] = 0;
            else if (word1[i - 1] == word2[j - 1])  // Characters equal, add diagonal cell (upper left) and 1 to current cell.
                length_table[i][j] = length_table[i - 1][j - 1] + 1;
            else // Characters not equal, take max value of either previous row or previous column.
                length_table[i][j] = max(length_table[i - 1][j], length_table[i][j - 1]);
        }
    }

    // Length of longest common subsequence.
    // Always found at the last row and last column of matrix.
    // Used to build longest common subsequence backwards.
    int longest_length_index = length_table[word1.size()][word2.size()];
    
    string longest;
    longest.resize(longest_length_index);
    int i = word1.size();
    int j = word2.size();
    // Build the subsequence backwards using the matrix.
    // Move up or left of the matrix depending on which cell is longer (element) and move diagonally (up and left of matrix)
    // when characters between the two words are equal (thus added to longest common subsequence).
    while (0 < i && 0 < j) {
        if (word1[i - 1] == word2[j - 1]) { // Characters equal in each word
            longest[longest_length_index - 1] = word1[i - 1];
            --i;
            --j;
            --longest_length_index;
        }
        else if (length_table[i - 1][j] > length_table[i][j - 1])   // Previous row longer (element)
            --i;
        else // Previous column longer (element)
            --j;
    }

    return longest;
}

// Driver for longest common subsequence calculations.
int subsequence_driver(int argc, char** argv) {
    const string word1(argv[1]);
    const string word2(argv[2]);

    string longest = LongestCommonSubsequence(word1, word2);

    cout << longest.size() << "\n" << longest << endl;
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << "<word_a>" << "<word_b>" << endl;
        return 0;
    }

    subsequence_driver(argc, argv);

    return 0;
}