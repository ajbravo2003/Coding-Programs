/*mymatrix.h*/

/**------------------------------------------
//  Project 3 - Matrix Implementation
    Course: CS 251, Spring 2023.
    System: Visual Studio Code 2023
    Author: Alejandro Bravo
 ---------------------------------------------**/
 // mymatrix
 //
 // The mymatrix class provides a matrix (2D array) abstraction.
 // The size can grow dynamically in both directions (rows and 
 // cols).  Also, rows can be "jagged" --- i.e. rows can have 
 // different column sizes, and thus the matrix is not necessarily 
 // rectangular.  All elements are initialized to the default value
 // for the given type T.  Example:
 //
 //   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
 //   
 //   M(0, 0) = 123;
 //   M(1, 1) = 456;
 //   M(2, 2) = 789;
 //   M(3, 3) = -99;
 //
 //   M.growcols(1, 8);  // increase # of cols in row 1 to 8
 //
 //   for (int r = 0; r < M.numrows(); ++r)
 //   {
 //      for (int c = 0; c < M.numcols(r); ++c)
 //         cout << M(r, c) << " ";
 //      cout << endl;
 //   }
 //
 // Output:
 //   123 0 0 0
 //   0 456 0 0 0 0 0 0
 //   0 0 789 0
 //   0 0 0 -99
 //
#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;
template<typename T>
class mymatrix
{
private:
    struct ROW
    {
        T* Cols;     // dynamic array of column elements
        int NumCols;  // total # of columns (0..NumCols-1)
    };
    ROW* Rows;     // dynamic array of ROWs
    int  NumRows;  // total # of rows (0..NumRows-1)

public:
    //
    // default constructor:
    //
    // Called automatically by C++ to construct a 4x4 matrix.  All 
    // elements are initialized to the default value of T.
    //
    mymatrix()
    {
        Rows = new ROW[4]; // an array with 4 ROW structs:
        NumRows = 4;

        for (int r = 0; r < NumRows; ++r) // initialize each row to have 4 columns:
        {
            Rows[r].Cols = new T[4]; // an array with 4 elements of type T:
            Rows[r].NumCols = 4;

            for (int c = 0; c < Rows[r].NumCols; ++c) // initialize to default value:
                Rows[r].Cols[c] = T{ 0 }; // default value for type T:

        }
    }
    //
    // parameterized constructor:
    //
    // Called automatically by C++ to construct a matrix with R rows, 
    // where each row has C columns. All elements are initialized to 
    // the default value of T.
    //
    mymatrix(int R, int C)
    {
        if (R < 1)
            throw invalid_argument("mymatrix::constructor: # of rows");
        if (C < 1)
            throw invalid_argument("mymatrix::constructor: # of cols");
        Rows = new ROW[R];//creates struct array with R size
        NumRows = R;
        for (int r = 0; r < NumRows; ++r)//for loop that goes through the amount of rows
        {
            Rows[r].Cols = new T[C];//creates columns
            Rows[r].NumCols = C;

            // initialize the elements to their default value:
            for (int c = 0; c < Rows[r].NumCols; ++c)
            {
                Rows[r].Cols[c] = T{ 0 };  // sets values to 0
            }
        }
    }


    //
    // copy constructor:
    //
    // Called automatically by C++ to construct a matrix that contains a 
    // copy of an existing matrix.  Example: this occurs when passing 
    // mymatrix as a parameter by value
    //
    //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
    //   { ... }
    //
    mymatrix(const mymatrix<T>& other)
    {
        Rows = new ROW[other.NumRows];//creates struct array with R size
        NumRows = other.NumRows;
        for (int r = 0; r < NumRows; ++r)//for loop that goes through the amount of rows
        {
            Rows[r].Cols = new T[other.numcols(r)];//creates columns
            Rows[r].NumCols = other.numcols(r);//sets row to amount of coulmns of other matrix

            for (int c = 0; c < other.Rows[r].NumCols; ++c)//for loop that copies values
            {
                Rows[r].Cols[c] = other.Rows[r].Cols[c];  //copies other matrix values to current one
            }
        }
    }


    //
    // numrows
    //
    // Returns the # of rows in the matrix.  The indices for these rows
    // are 0..numrows-1.
    //
    int numrows() const
    {
        return NumRows;//returns amoount of rows
    }


    //
    // numcols
    //
    // Returns the # of columns in row r.  The indices for these columns
    // are 0..numcols-1.  Note that the # of columns can be different 
    // row-by-row since "jagged" rows are supported --- matrices are not
    // necessarily rectangular.
    //
    int numcols(int r) const
    {
        int counter = 0;
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::numcols: row");

        for (int c = 0; c < Rows[r].NumCols; ++c)//loops through each row and counts the columns
        {
            counter++;
        }
        return counter;//returns amount of columns
    }

    //
    // growcols
    //
    // Grows the # of columns in row r to at least C.  If row r contains 
    // fewer than C columns, then columns are added; the existing elements
    // are retained and new locations are initialized to the default value 
    // for T.  If row r has C or more columns, then all existing columns
    // are retained -- we never reduce the # of columns.
    //
    // Jagged rows are supported, i.e. different rows may have different
    // column capacities -- matrices are not necessarily rectangular.
    //
    void growcols(int r, int C)
    {

        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::growcols: row");
        if (C < 1)
            throw invalid_argument("mymatrix::growcols: columns");
        if (Rows[r].NumCols < C) {//for loop that checks if coulms is less then wanted columns it adds more 
            T* newCols = new T[C];//creates new column array
            for (int j = 0; j < Rows[r].NumCols; j++) {
                newCols[j] = Rows[r].Cols[j];//gets col values and stores to the new one
            }
            for (int col = Rows[r].NumCols; col < C; col++) {//sets 0 to new columns intiliazed
                newCols[col] = T{ 0 };//sets 0 to value
            }
            Rows[r].Cols = newCols;//sets array back to each row
            Rows[r].NumCols = C;//sets number of columns to user columns
        }
    }
    //
    // grow
    //
    // Grows the size of the matrix so that it contains at least R rows,
    // and every row contains at least C columns.
    // 
    // If the matrix contains fewer than R rows, then rows are added
    // to the matrix; each new row will have C columns initialized to 
    // the default value of T.  If R <= numrows(), then all existing
    // rows are retained -- we never reduce the # of rows.
    //
    // If any row contains fewer than C columns, then columns are added
    // to increase the # of columns to C; existing values are retained
    // and additional columns are initialized to the default value of T.
    // If C <= numcols(r) for any row r, then all existing columns are
    // retained -- we never reduce the # of columns.
    // 
    void grow(int R, int C)
    {
        if (R < 1)
            throw invalid_argument("mymatrix::grow: # of rows");
        if (C < 1)
            throw invalid_argument("mymatrix::grow: # of cols");
        {
            if (NumRows < R) {
                ROW* tempRow = new ROW[R];//creates new row struct with R size
                for (int i = 0; i < NumRows; i++)//for loop that copies values of old row array to new row array
                {
                    tempRow[i] = Rows[i];//stores values
                }

                for (int i = NumRows; i < R; i++) {//loop that intiliazes new data
                    tempRow[i].Cols = new T[C];//creates new columns for each new rows
                    tempRow[i].NumCols = C;//sets number of columns to user columns
                    for (int j = 0; j < C; j++)//for loop that sets new column into 0
                    {
                        tempRow[i].Cols[j] = T{ 0 };//sets to 0
                    }
                }
                Rows = tempRow;//sets pointer back to rows
                NumRows = R;//sets number of rows to user rows
            }

            for (int i = 0; i < NumRows; i++) {//for loop that calls grow cols function to grow the columns of the new rows
                growcols(i, C);
            }
        }

    }

    //
    // size
    //
    // Returns the total # of elements in the matrix.
    //
    int size() const {
        int counter = 0;
        for (int i = 0; i < NumRows; i++) {//for loops through all the rows
            counter += numcols(i);//gets the coulmns number for each row
        }
        return counter;//returns the size of matrix
    }

    //
    // at
    //
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    M.at(r, c) = ...
    //    cout << M.at(r, c) << endl;
    //
    T& at(int r, int c) const
    {
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::at: row");
        if (c < 0 || c >= Rows[r].NumCols)
            throw invalid_argument("mymatrix::at: col");
        return Rows[r].Cols[c];//returns the reference of the specific row and column
    }

    //
    // ()
    //
    // Returns a reference to the element at location (r, c); this
    // allows you to access the element or change it:
    //
    //    M(r, c) = ...
    //    cout << M(r, c) << endl;
    //
    T& operator()(int r, int c) const
    {
        if (r < 0 || r >= NumRows)
            throw invalid_argument("mymatrix::(): row");
        if (c < 0 || c >= Rows[r].NumCols)
            throw invalid_argument("mymatrix::(): col");


        return Rows[r].Cols[c];//returns the specfic address of the row and column
    }

    //
    // scalar multiplication
    //
    // Multiplies every element of this matrix by the given scalar value,
    // producing a new matrix that is returned.  "This" matrix is not
    // changed.
    //
    // Example:  M2 = M1 * 2;
    //
    mymatrix<T> operator*(T scalar)
    {
        mymatrix<T> result(NumRows, Rows->NumCols);//sets result matrix to other current matrix size
        for (int r = 0; r < NumRows; r++)//for loop that sets data from regualr matrix to result matrix
        {
            result.Rows[r] = Rows[r];//sets values from old matrix to new
            for (int c = 0; c < Rows[r].NumCols; c++)
            {
                result.at(r, c) *= scalar;//mutiplys matrix values by scalar
            }
        }
        return result;//returns result matrix
    }

    //
    // matrix multiplication
    //
    // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
    // M2 is the "other" matrix.  This produces a new matrix, which is returned.
    // "This" matrix is not changed, and neither is the "other" matrix.
    //
    // Example:  M3 = M1 * M2;
    //
    // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
    // addition, the sizes of M1 and M2 must be compatible in the following sense:
    // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
    // multiplication can be performed, and the resulting matrix is of size RxC.
    //
    bool isRectangular1(const mymatrix<T>other) {//function that checks if the first matrix is rectangular
        bool matrix1 = true;
        for (int i = 0; i < other.NumRows; i++) {//for loops to check if rows are not the same as column basically no jagged rows
            if (other.numcols(i) != other.Rows->NumCols) {
                matrix1 = false;
            }

        }

        if (matrix1) {//checks if has jagged rows and returns 
            return true;
        }
        else {
            return false;
        }

    }

    bool isRectangular2(mymatrix<T> result) {//function that checks if the second matrix is rectangular
        bool matrix1 = true;
        for (int i = 0; i < result.NumRows; i++) {//for loops to check if rows are not the same as column basically no jagged rows
            if (result.numcols(i) != result.Rows->NumCols) {
                matrix1 = false;
            }

        }

        if (matrix1) {//checks if has jagged rows and returns 
            return true;
        }
        else {
            return false;
        }

    }


    mymatrix<T> operator*(const mymatrix<T>& other)
    {
        mymatrix<T> result(1,1);
        // both matrices must be rectangular for this to work:
        if (!isRectangular2(*this)) {
            throw runtime_error("mymatrix::*: this not rectangular");
        }

        if (!isRectangular1(other)) {
            throw runtime_error("mymatrix::*: other not rectangular");
        }

        //
        // Okay, both matrices are rectangular.  Can we multiply?  Only
        // if M1 is R1xN and M2 is NxC2.  This yields a result that is
        // R1xC2.
        // 
        // Example: 3x4 * 4x2 => 3x2
        //
        if (this->Rows->NumCols != other.NumRows) {//checks to see if number of other rows are the same as number of this coloumns
            throw runtime_error("mymatrix::*: size mismatch");
        }
        //
        // Okay, we can multiply:
        //
        result.grow(this->NumRows,other.Rows->NumCols);//changes rows and columns because of multiplication rule
        // for(int i = 0 ; i < this->num;i++){

        // }
         return result;
    }


    //
    // _output
    //
    // Outputs the contents of the matrix; for debugging purposes.
    //
    void _output()
    {
        for (int r = 0; r < this->NumRows; ++r)
        {
            for (int c = 0; c < this->Rows[r].NumCols; ++c)
            {
                cout << this->Rows[r].Cols[c] << " ";
            }
            cout << endl;
        }
    }

};  