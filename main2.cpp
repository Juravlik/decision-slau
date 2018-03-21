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
    map<pair<int, int>, double> data;
    
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
    
    for(map<pair<int, int>, double>::const_iterator p = result.data.begin();
	 p != result.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        double value = p->second;
        
        result.SetElement(col, row, value);
    }
    return result;
	}
	
	SparseMatrix createA()
	{
		SparseMatrix A(height, width - 1);
		
		for(map<pair<int, int>, double>::const_iterator p = this->data.begin();
	 p != this->data.end(); p++)
    {
        int col = p->first.second;
        if(col >= width - 1) continue;
        int row = p->first.first;
        double value = p->second;
        
        A.SetElement(row, col, value);
    }
		return A;
	}
	
	SparseMatrix createB()
	{
	SparseMatrix B(height, 1);
    for(int i = 0; i < height; i++)
    {
        B.SetElement(i, 0, this->GetElement(i, width - 1));
    }
		return B;
	}
    
    void fillNumbers(long double n)
	{
		for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                this->SetElement(i, j, n);
            }
        }
	}
    
    void SetElement(int row, int col, double element)
    {
        data[pair<int, int>(row, col)] = element;
    }
    
    int GetElement(int row, int col) const
    {
        map<pair<int, int >, double>::const_iterator p = 
                    data.find(pair<int, int>(row, col));
        return (p == data.end()) ? 0 : p->second;
    }
    
    void Show() const
    {
    	for(int i = 0; i < height; i++)
        {
    		for(int j = 0; j < width; j++)
    		{
    			cout << this->GetElement(i, j) << " "; 
			}
			cout << endl;
        }
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
    
    for(map<pair<int, int>, double>::const_iterator p = rhs.data.begin();
	 p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        double value = p->second;
        
        result.SetElement(row, col, value + result.GetElement(row, col));
    }
    
    return result;
}

    SparseMatrix operator-(const SparseMatrix& rhs) const
{
    SparseMatrix result = *this;
    
    for(map<pair<int, int>, double>::const_iterator p = rhs.data.begin();
	 p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        double value = p->second;
        
        result.SetElement(row, col, value - result.GetElement(row, col));
    }
    
    return result;
}

SparseMatrix operator*(double k)
	{
		SparseMatrix res(this->height, this->width);
		
        for(map<pair<int, int>, double>::const_iterator p = this->data.begin();
	 p != this->data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        double value = p->second;
        
        res.SetElement(row, col, value * k);
    }
        
		return res;
	}

bool operator>=(const SparseMatrix& rhs)
	{
		bool flag = true;
		int count = 0;
		
		 for(int i = 0; i < height; i++)
         {
             if(abs(this->GetElement(i, 0)) < abs(rhs.GetElement(i, 0)))
                count++;
         }
         
		if(count == this->Height())
            flag = false;
		return flag;
	}


SparseMatrix operator*(const SparseMatrix& rhs) const
{
    SparseMatrix result(Height(), rhs.Width());
    
    for(map<pair<int, int>, double>::const_iterator p = data.begin();
	 p != data.end(); p++)
    {
        int i = p->first.first;
        int k = p->first.second;
        double m = p->second;
        
        for(map<pair<int, int>, double>::const_iterator rp = rhs.data.begin(); 
		rp != rhs.data.end();
            rp++)
            {
                int b_k = rp->first.first;
                int j = rp->first.second;
                double n = rp->second;
                
                if(k == b_k)
                    result.SetElement(i, j, result.GetElement(i, j) + m * n);
            }
    }
    return result;
}

double operator%(const SparseMatrix& rhs)
	{
		long double sum = 0;
		for(map<pair<int, int>, double>::const_iterator p = rhs.data.begin();
	 p != rhs.data.end(); p++)
    {
        int row = p->first.first;
        int col = p->first.second;
        double value = p->second;
        
        sum += value * this->GetElement(row, col);
    }
	
	return sum;
	}

};


int main()
{
	const char* S = "matr.txt";
	SparseMatrix Slau(S);
    SparseMatrix A = Slau.createA();
    SparseMatrix B = Slau.createB();
    
    SparseMatrix X(Slau.Height(), 1);
	X.fillNumbers(0.0);

	cout << "Enter e: ";
	double e;
	cin >> e;
	SparseMatrix E(Slau.Height(), 1);
	E.fillNumbers(e);

	int count = 1;
    SparseMatrix R = A * X - B;
    double b_k = -(R%R) / ((A * R) % R);
	SparseMatrix D = R * b_k;
	X = X + D;
	while (A * X - B >= E) 
	{
        R = A * X - B;
        double a_k = ((R % R) * ((A * R) % D) - (R % D) * ((A * R) % R)) / 
        (((A * D) % D) * ((A * R) % R) - ((A * R) % D) * ((A * R) % D));
        double b_k = ((R % D) * ((A * R) % D) - (R % R) * ((A * D) % D)) / 
        (((A * D) % D) * ((A * R) % R) - ((A * R) % D) * ((A * R) % D));
        D = D * a_k + R * b_k;
        X = X + D;
		count++;
	}
	X.Show();
	cout <<"________________________count = " <<count << endl;
	SparseMatrix P = A * X - B;
	P.Show();
	
	
	return 0;
}
