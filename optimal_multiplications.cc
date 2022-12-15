// William Yang
// optimal_multiplications.cc: a file to get the optimal number of multiplcations
// for ordering of matrix multiplication.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <climits>

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

// Read file given dimensions filename and return the contents as a vector.
vector<int> ReadDimensionsFile(const string& dimensions_filename) {
    fstream dimensions_file(dimensions_filename);
    if (!dimensions_file.is_open())
    {
        cerr << "Failed to read dimensions file." << endl;
        exit(1);
    }

    vector<int> dimensions;
    int dimension;
    // Read dimensions into vector
    while (dimensions_file >> dimension)
    {
        dimensions.push_back(dimension);
    }

    return dimensions;
}

/**
 * Code is taken from the textbook.
 * Compute optimal ordering of matrix multiplication.
 * c contains the number of columns for each of the n matrices.
 * c[ 0 ] is the number of rows in matrix 1.
 * The minimum number of multiplications is left in m[ 1 ][ n ].
 * Actual ordering is computed via another procedure using lastChange.
 * m and lastChange are indexed starting at 1, instead of 0.
 * Note: Entries below main diagonals of m and lastChange
 * are meaningless and uninitialized.
 */
void OptimalMatrixMultiplication(const vector<int>& c, Matrix<int>& m, Matrix<int>& lastChange)
{
    int n = c.size() - 1;

    // The 0 diagonal
    for (int left = 1; left <= n; ++left)
        m[left][left] = 0;

    for (int k = 1; k < n; ++k)   // k is right - left
        for (int left = 1; left <= n - k; ++left)
        {
            // For each position
            int right = left + k;
            m[left][right] = INT_MAX;   // Set to INFINITY as place holder
            for (int i = left; i < right; ++i)
            {
                // Cost of current order
                int thisCost = m[left][i] + m[i + 1][right]
                    + c[left - 1] * c[i] * c[right];

                if (thisCost < m[left][right])  // Update min if order offers lower cost
                {
                    m[left][right] = thisCost;
                    lastChange[left][right] = i;
                }
            }
        }
}

// Driver for optimal matrix multiplication
int multiplication_driver(int argc, char** argv) {
    const string dimensions_filename(argv[1]);

    // Read file into dimensions vector.
    vector<int> dimensions = ReadDimensionsFile(dimensions_filename);

    // Create the matrices to retreive the calculations.
    int dimensions_size = dimensions.size();
    Matrix<int> costs { dimensions_size, dimensions_size };
    Matrix<int> last_change { dimensions_size, dimensions_size };

    OptimalMatrixMultiplication(dimensions, costs, last_change);

    // Optimal solution is always found in this cell (2st row, last column),
    // given how the algorithm from the textbook works
    // (1st and 2nd rows are unitialized/disregarded).
    cout << costs[1][costs.NumCols() - 1] << endl;
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << "<dimensions_file>" << endl;
        return 0;
    }

    multiplication_driver(argc, argv);

    return 0;
}
