#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
//#include <map>

using namespace std;


class SparseMatrix
{
private:
    int height, width;
    map<pair<int, int>, int> data;
    
public:
    SparseMatrix(int h, int w) : height(h), width(w) {}
    
    int Height() const { return height; }
    int Width() const { return width; }
    
    void SetElement(int row, int col, int element)
    {
        data[pair<int, int>(row, col)] = elemnt;
    }
    
    int GetElement(int row, int col) const
    {
        map<pair<int, int >, int>::const_iterator p = 
                    data.find(pair<int, int>(row, col));
        return (p == data.end()) ? 0 : p->second;
    }
    SparseMatrix operator+(const SparseMatrix& rhs) const;
    SparseMatrix operator*(const SparseMatrix& rhs) const;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& rhs) const
{
    SparseMatrix result = *this;
    
    for(map<pair<int, int>, int>::const_iterator p = rhs.data.begin(); p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        int value = p->second;
        
        result.SetElement(row, col, value + result.GetElement(row, col));
    }
    
    return result;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix& rhs) const
{
    SparseMatrix result(Height(), rhs.Width());
    
    for(map<pair<int, int>, int>::const_iterator p = data.begin(); p != data.end(); p++)
    {
        int i = p->first.first;
        int k = p->first.second;
        int m = p->second;
        
        for(map<pair<int, int>, int>::const_iterator rp = rhs.data.begin(); rp != rhs.data.end();
            rp++)
            {
                int b_k = rp->first.first;
                int j = rp->first.second;
                int n = rp->second;
                
                if(k == b_k)
                    result.SetElement(i, j, result.GetElement(i, j) + m * n);
            }
    }
    return result;
}

int main()
{

	
	return 0;
}

