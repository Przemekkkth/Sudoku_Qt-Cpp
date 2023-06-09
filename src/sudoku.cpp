#include "sudoku.h"
#include <ctime>

using namespace std;

Sudoku::Sudoku(int N, int K)
{
    srand(time(0));
    this->N = N;
    this->K = K;

    // Compute square root of N
    double SRNd = sqrt(N);
    SRN = (int)SRNd;
    mat = new int*[N];
    valid_mat = new int*[N];
    // Create a row for every pointer
    for (int i = 0; i < N; i++)
    {

        // Note : Rows may not be contiguous
        mat[i] = new int[N];
        valid_mat[i] = new int[N];

        // Initialize all entries as false to indicate
        // that there are no edges initially
        memset(mat[i], 0, N * sizeof(int));
        memset(valid_mat[i], 0, N * sizeof (int));
    }
}

void Sudoku::fillValues()
{

    // Fill the diagonal of SRN x SRN matrices
    fillDiagonal();

    // Fill remaining blocks
    fillRemaining(0, SRN);

    // Set valid matrix
    setValidMat();

    // Remove Randomly K digits to make game
    removeKDigits();
}

int Sudoku::getMatVal(int r, int c)
{
    return mat[r][c];
}

int Sudoku::getValidMatVal(int r, int c)
{
    return valid_mat[r][c];
}

void Sudoku::fillDiagonal()
{
    for (int i = 0; i < N; i = i + SRN)
    {

        // for diagonal box, start coordinates->i==j
        fillBox(i, i);
    }
}

bool Sudoku::unUsedInBox(int rowStart, int colStart, int num)
{
    for (int i = 0; i < SRN; i++) {
        for (int j = 0; j < SRN; j++) {
            if (mat[rowStart + i][colStart + j]
                    == num) {
                return false;
            }
        }
    }
    return true;
}

void Sudoku::fillBox(int row, int col)
{
    int num;
    for (int i = 0; i < SRN; i++) {
        for (int j = 0; j < SRN; j++) {
            do {
                num = randomGenerator(N);
            } while (!unUsedInBox(row, col, num));
            mat[row + i][col + j] = num;
        }
    }
}

int Sudoku::randomGenerator(int num)
{
    return (int)floor(
                (float)(rand() / double(RAND_MAX) * num + 1));
}

bool Sudoku::CheckIfSafe(int i, int j, int num)
{
    return (
                unUsedInRow(i, num) && unUsedInCol(j, num)
                && unUsedInBox(i - i % SRN, j - j % SRN, num));
}

bool Sudoku::unUsedInRow(int i, int num)
{
    for (int j = 0; j < N; j++) {
        if (mat[i][j] == num) {
            return false;
        }
    }
    return true;
}

bool Sudoku::unUsedInCol(int j, int num)
{
    for (int i = 0; i < N; i++) {
        if (mat[i][j] == num) {
            return false;
        }
    }
    return true;
}

bool Sudoku::fillRemaining(int i, int j)
{
    // System.out.println(i+" "+j);
    if (j >= N && i < N - 1) {
        i = i + 1;
        j = 0;
    }
    if (i >= N && j >= N) {
        return true;
    }
    if (i < SRN) {
        if (j < SRN) {
            j = SRN;
        }
    }
    else if (i < N - SRN) {
        if (j == (int)(i / SRN) * SRN) {
            j = j + SRN;
        }
    }
    else {
        if (j == N - SRN) {
            i = i + 1;
            j = 0;
            if (i >= N) {
                return true;
            }
        }
    }
    for (int num = 1; num <= N; num++) {
        if (CheckIfSafe(i, j, num)) {
            mat[i][j] = num;
            if (fillRemaining(i, j + 1)) {
                return true;
            }
            mat[i][j] = 0;
        }
    }
    return false;
}

void Sudoku::removeKDigits()
{
    int count = K;
    while (count != 0) {
        int cellId = randomGenerator(N * N) - 1;
        // System.out.println(cellId);
        // extract coordinates i and j
        int i = (cellId / N);
        int j = cellId % 9;
        if (j != 0) {
            j = j - 1;
        }
        // System.out.println(i+" "+j);
        if (mat[i][j] != 0) {
            count--;
            mat[i][j] = 0;
        }
    }
}

void Sudoku::printSudoku()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << to_string(mat[i][j]) + " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Sudoku::setValidMat()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            valid_mat[i][j] = mat[i][j];
        }
    }
}
