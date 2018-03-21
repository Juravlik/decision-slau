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
#include <map>

using namespace std;


class SparseMatrix
{
protected:
    int height, width;
    map<pair<int, int>, int> data;
    
public:
    SparseMatrix(int h, int w) : height(h), width(w) {}
	
	
    SparseMatrix(const char* S)
	{
		ifstream in(S);
		int count = 0;
		int temp;

		while (!in.eof())
		{
			in >> temp;
			count++;
		}
		in.clear();
		in.seekg(0, ios::beg);

		int count_space = 0;
		char symbol;
		while (!in.eof())
		{
			in.get(symbol);
			if (symbol == ' ') count_space++;
			if (symbol == '\n') break;
		}
		in.clear();
		in.seekg(0, ios::beg);
		
		height = count / (count_space + 1);
		width = count_space + 1;
		
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				in >> temp;
				if(temp != 0)
					this->SetElement(i, j, temp);
			}
	}
    
    int Height() const { return height; }
    int Width() const { return width; }
    
    SparseMatrix sopr()
	{
	SparseMatrix result = *this;
    
    for(map<pair<int, int>, int>::const_iterator p = result.data.begin();
	 p != result.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        int value = p->second;
        
        result.SetElement(col, row, value);
    }
    return result;
	}
	
	SparseMatrix createA()
	{
		SparseMatrix A(height, width);
		
		for(map<pair<int, int>, int>::const_iterator p = this->data.begin();
	 p != this->data.end(); p++)
    {
        int col = p->first.second;
        if(col >= width - 1) continue;
        int row = p->first.first;
        int value = p->second;
        
        A.SetElement(row, col, value);
    }
		return A;
	}
	
	SparseMatrix createB()
	{
		SparseMatrix B(height, 1);
		for(map<pair<int, int>, int>::const_iterator p = this->data.begin();
	 p != this->data.end(); p++)
    {
    	int col = p->first.second;
    	if(col < width - 1) continue;
        int row = p->first.first;
        int value = p->second;
        
        B.SetElement(row, col, value);
    }
		return B;
	}
    
    void SetElement(int row, int col, int element)
    {
        data[pair<int, int>(row, col)] = element;
    }
    
    int GetElement(int row, int col) const
    {
        map<pair<int, int >, int>::const_iterator p = 
                    data.find(pair<int, int>(row, col));
        return (p == data.end()) ? 0 : p->second;
    }
    
    void Show() const
    {
    	for(int i = 0; i < height; i++)
    		for(int j = 0; j < weight; j++)
    		{
    			cout << this->GetElement(i, j) << " "; 
			}
			cout << endl;
	}
    
    SparseMatrix operator=(const SparseMatrix& rhs)
	{
		width = rhs.width;
		height = rhs.height;
		data = rhs.data;
		return *this;
	}
    
    SparseMatrix operator+(const SparseMatrix& rhs) const
{
    SparseMatrix result = *this;
    
    for(map<pair<int, int>, int>::const_iterator p = rhs.data.begin();
	 p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        int value = p->second;
        
        result.SetElement(row, col, value + result.GetElement(row, col));
    }
    
    return result;
}

    SparseMatrix operator-(const SparseMatrix& rhs) const
{
    SparseMatrix result = *this;
    
    for(map<pair<int, int>, int>::const_iterator p = rhs.data.begin();
	 p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        int value = p->second;
        
        result.SetElement(row, col, value - result.GetElement(row, col));
    }
    
    return result;
}

bool operator>=(const SparseMatrix& rhs)
	{
		bool flag = true;
		int count = 0;
		
		 for(map<pair<int, int>, int>::const_iterator p = rhs.data.begin();
	 p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        int value = p->second;
        
        if(abs(this->GetElement(row, col)) < rhs.GetElement(row, col))
			count++; 
    }
		
		if(count == this->Height())
            flag = false;
		return flag;
	}


SparseMatrix operator*(const SparseMatrix& rhs) const
{
    SparseMatrix result(Height(), rhs.Width());
    
    for(map<pair<int, int>, int>::const_iterator p = data.begin();
	 p != data.end(); p++)
    {
        int i = p->first.first;
        int k = p->first.second;
        int m = p->second;
        
        for(map<pair<int, int>, int>::const_iterator rp = rhs.data.begin(); 
		rp != rhs.data.end();
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

long double operator%(const SparseMatrix& rhs)
	{
		long double sum = 0;
		for(map<pair<int, int>, int>::const_iterator p = rhs.data.begin();
	 p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        int value = p->second;
        
        sum += value * this->GetElement(row, col);
    }
	
	return sum;
	}

};


int main()
{
	const char* S = "matr.txt";
	SparseMatrix Slau(S);
	Slau.Show();
	
	
	return 0;
}
