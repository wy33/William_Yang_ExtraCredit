// William Yang
// subsequence.cc: a file to find the longest common subsequence between two words
// supplied in the command line.

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;



// Class Matrix:
// A simple matrix class created to represent a matrix with accessors.
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
    vector<vector<Object>> array_;
};

// Calculates the longest common subsequence of the two strings.
string LongestCommonSubsequence(const string& word1, const string& word2) {
/*    string longest;
    int i = -1; // Start position for word1
    int k = 0;  // Start position for word2

    while (++i < word1.size() && k < word2.size())
    {
        for (int j = k; j < word2.size(); j++)
        {
            // Common character found
            if (word1[i] == word2[j])
            {
                longest.push_back(word1[i]);
                ++i;    // Increment index to the next character to compare for word1.
                k = j + 1;  // Set start index of word2 to position after common character.
                if (i >= word1.size())  // Reached the end of word1, terminate loop.
                    break;
            }

        }
    }

    return longest;*/
    Matrix<int> length_table { (int)word1.size() + 1, (int)word2.size() + 1};

    for (int i = 0; i <= word1.size(); ++i)
    {
        for (int j = 0; j <= word2.size(); ++j)
        {
            if (i == 0 || j == 0)   // 1st row and 1st column unused
                length_table[i][j] = 0;
            else if (word1[i - 1] == word2[j - 1])
                length_table[i][j] = length_table[i - 1][j - 1] + 1;
            else
                length_table[i][j] = max(length_table[i - 1][j], length_table[i][j - 1]);
        }
    }

    int longest_length_index = length_table[word1.size()][word2.size()];
    
    string longest;
    longest.resize(longest_length_index);
    int i = word1.size();
    int j = word2.size();
    // Build the subsequence backwards using the matrix.
    while (0 < i && 0 < j) {
        if (word1[i - 1] == word2[j - 1]) { // Characters equal in each word
            longest[longest_length_index - 1] = word1[i - 1];
            --i;
            --j;
            --longest_length_index;
        }
        else if (length_table[i - 1][j] > length_table[i][j - 1])
            --i;
        else
            --j;
    }
    return longest;
}

// Driver for longest common subsequence calculations.
int subsequence_driver(int argc, char** argv) {
    const string word1(argv[1]);
    const string word2(argv[2]);

    string longest = LongestCommonSubsequence(word1, word2);

    // If word1 is smaller, pass word1 as first parameter;
    // else pass word2 as first parameter.
    // Theory is that based on how the algorithm works, if we can get i and k (in the function) to increment faster, there would be less comparisons needed.
/*    if (word1.size() < word2.size())
        longest = LongestCommonSubsequence(word1, word2);
    else
        longest = LongestCommonSubsequence(word2, word1);*/


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