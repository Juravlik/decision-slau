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
		double temp;

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
	SparseMatrix result(this->Height(), this->Width());
    
    for(map<pair<int, int>, double>::const_iterator p = this->data.begin();
	 p != this->data.end(); p++)
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
    
    double GetElement(int row, int col) const
    {
        map<pair<int, int >, double>::const_iterator p = 
                    data.find(pair<int, int>(row, col));
        return (p == data.end()) ? 0.0 : p->second;
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
        
        result.SetElement(row, col, result.GetElement(row, col) - value);
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
        double u = k * value;
        res.SetElement(row, col, u);
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
/*
void createRandomSparseMatr()
{
	ofstream out("matr.txt");
	
	srand(time(NULL)); 
    int n = 0;
	cout << "Enter n for random sparse matrix: "; 
    cin >> n;
    int **a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int [n]; 
    } 
    for (int i = 0; i < n; i++)
    {
    	bool key = true;
        for (int j = 0; j < n; j++)
        {
        	int temp = rand() % 100;
        	if(temp >= 96)
			{ 
        		a[i][j] = rand() % 10;
        		key = false;
        	}
			else  
				a[i][j] = 0; 
            out << a[i][j] << " "; 
        }
        if(!key) out << rand() % 10;
        else out << 0;
        out << '\n';
    }
}
*/

void createRandomSparseMatr()
{
	ofstream out("matr.txt");
	
	srand(time(NULL)); 
    int n = 0;
	cout << "Enter n for random sparse matrix: "; 
    cin >> n;
    int **a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int [n]; 
    }
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
        	if(i == j)
			{ 
				if(rand() % 2 == 1)	
				{
					a[i][j] = rand() % 10; 
					out << a[i][j] << " ";
        		}
        		else 
				{ 
					a[i][j] = 0;
					out << a[i][j] << " ";
				} 
        	}
			else 
			{ 
				a[i][j] = 0;
				out << a[i][j] << " ";
			} 
        }
        if(a[i][i] != 0)
        	out << rand() % 10 << '\n';
        else out << 0 << '\n';
    }
}


SparseMatrix CholeskyDec(const SparseMatrix& A)
{
    SparseMatrix L(A.Height(), A.Height());
    L.fillNumbers(0);
    for (int i = 0; i < A.Height(); i++)
    {
        double temp;
        //Ñíà÷àëà âû÷èñëÿåì çíà÷åíèÿ ýëåìåíòîâ ñëåâà îò äèàãîíàëüíîãî ýëåìåíòà,
        //òàê êàê ýòè çíà÷åíèÿ èñïîëüçóþòñÿ ïðè âû÷èñëåíèè äèàãîíàëüíîãî ýëåìåíòà.
        for (int j = 0; j < i; j++)
        {
        	if(A.GetElement(i, j) == 0)
        		{
        			L.SetElement(i, j, 0);
				}
			else {
			
            temp = 0;
            for (int k = 0; k < j; k++)
            {
                temp += (L.GetElement(i,k)) * (L.GetElement(j, k));
            }
            double temp2 = (A.GetElement(i, j) - temp) / L.GetElement(j, j);
            L.SetElement(i, j, temp2);
        }
        }

        //Íàõîäèì çíà÷åíèå äèàãîíàëüíîãî ýëåìåíòà
        temp = A.GetElement(i, i);
        if(temp != 0)
    	{
	
	        for (int k = 0; k < i; k++)
	        {
	        	if(L.GetElement(i, k) != 0 && L.GetElement(i, k) != 0)
	            	temp -= L.GetElement(i, k) * L.GetElement(i, k);
	        }
		}
		if(temp >= 0) 
       	 L.SetElement(i, i, sqrt(temp));
    }

    return L;
}

SparseMatrix Start(SparseMatrix A, SparseMatrix X, SparseMatrix B, SparseMatrix E)
{
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
	}
	return X;
}

int main()
{
	createRandomSparseMatr();
	const char* S = "matr.txt";
	SparseMatrix Slau(S);
    SparseMatrix A = Slau.createA();
    A.SetElement(0, 0, 1);
    //A.SetElement(1, 0, 2);
    SparseMatrix L = CholeskyDec(A);
    SparseMatrix L_T = L.sopr();
    A.Show();
    cout << "________________ "<<endl;
    L.Show();
    SparseMatrix B = Slau.createB();
   // B.Show();
    
    SparseMatrix X(Slau.Height(), 1);
	X.fillNumbers(0.0);
	SparseMatrix Y(Slau.Height(), 1);
	Y.fillNumbers(0.0);
	
	cout << "Enter e: ";
	double e;
	cin >> e;
	SparseMatrix E(Slau.Height(), 1);
	E.fillNumbers(e/2.0);
	
	Y = Start(L, Y, B, E);
	X = Start(L_T, X, Y, E);
		
	X.Show();
	cout << "_____________________LOL________________" << endl;
	SparseMatrix P = A * X - B;
	P.Show();
	return 0;
}
