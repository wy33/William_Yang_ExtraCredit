// William Yang
// subsequence.cc: a file to find the longest common subsequence between two words
// supplied in the command line.

#include <iostream>
#include <string>

using namespace std;



// Calculates the longest common subsequence of the two strings.
string LongestCommonSubsequence(const string& word1, const string& word2) {
    string longest;
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

    return longest;
}

// Driver for longest common subsequence calculations.
int subsequence_driver(int argc, char** argv) {
    const string word1(argv[1]);
    const string word2(argv[2]);

    string longest;

    // If word1 is smaller, pass word1 as first parameter;
    // else pass word2 as first parameter.
    // Theory is that based on how the algorithm works, if we can get i and k (in the function) to increment faster, there would be less comparisons needed.
    if (word1.size() < word2.size())
        longest = LongestCommonSubsequence(word1, word2);
    else
        longest = LongestCommonSubsequence(word2, word1);

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
