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

using namespace std;


class Matrix
{
public:
    int rows_, cols_;
	long double** p;
	Matrix(int r) : rows_(r), cols_(r)
	{
		p = new long double*[rows_];
		for (int i = 0; i < rows_; i++)
			p[i] = new long double[cols_];
	}
	Matrix(const char* S)
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

		rows_ = count / (count_space + 1);
		cols_ = count_space + 1;
		p = new long double*[rows_];
		for (int i = 0; i < rows_; i++)
			p[i] = new long double[cols_];

		for (int i = 0; i < rows_; i++)
			for (int j = 0; j < cols_; j++)
				in >> p[i][j];
	}
	Matrix(int r, int c) : rows_(r), cols_(c)
	{
		p = new long double*[rows_];
		for (int i = 0; i < rows_; i++)
			p[i] = new long double[cols_];
	}
	~Matrix()
	{
		for (int i = 0; i < rows_; i++) {
			delete[] p[i];
		}
		delete[] p;
	}

	int getRows()
	{
		return rows_;
	}
	int getCols()
	{
		return cols_;
	}
	void create()
	{
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				cout << "p[" << i << "][" << j << "] = ";
				cin >> p[i][j];
			}
		}
	}

	void fillNumbers(long double n)
	{
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				p[i][j] = n;
			}
		}
	}

	void show()
	{
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				cout << p[i][j] << " ";
			}
			cout << endl;
		}
	}
	Matrix sopr()
	{
	  Matrix B(rows_, cols_);
	  for(int i = 0; i < rows_; i++) {
	    for(int j = 0; j < cols_; j++) {
	      B.p[i][j] = p[j][i]; 
	    }
	  }
	  return B;
	}
	Matrix createA()
	{
		Matrix A(rows_, cols_ - 1);
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_ - 1; j++) {
				A.p[i][j] = p[i][j];
			}
		}
		return A;
	}
	Matrix createB()
	{
		Matrix B(rows_, 1);
		for (int i = 0; i < rows_; i++) {
			B.p[i][0] = p[i][cols_ - 1];
		}
		return B;
	}

	Matrix& operator=(const Matrix& m)
	{
		if (rows_ != m.rows_ || cols_ != m.cols_) {
			for (int i = 0; i < rows_; i++) {
				delete[] p[i];
			}
			delete[] p;

			rows_ = m.rows_;
			cols_ = m.cols_;
		}

		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				p[i][j] = m.p[i][j];
			}
		}
		return *this;
	}

	Matrix operator+(const Matrix& m)
	{
		if (rows_ != m.rows_ || cols_ != m.cols_) { cout << "U NAS PROBLEMI, H'USTON"; }
		Matrix res(rows_, cols_);
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				res.p[i][j] = p[i][j] + m.p[i][j];
			}
		}
		return res;
	}
	Matrix operator-(const Matrix& m)
	{
		if (rows_ != m.rows_ || cols_ != m.cols_) { cout << "U NAS PROBLEMI, H'USTON"; }
		Matrix res(rows_, cols_);
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				res.p[i][j] = p[i][j] - m.p[i][j];
			}
		}
		return res;
	}

	Matrix operator*(const Matrix& m)
	{
		if (cols_ != m.rows_) { cout << "U NAS PROBLEMI, H'USTON"; }
		Matrix res(rows_, m.cols_);
		res.fillNumbers(0.0);
		for (int i = 0; i < res.rows_; ++i) {
			for (int j = 0; j < res.cols_; ++j) {
				for (int k = 0; k < cols_; ++k) {
					res.p[i][j] += (p[i][k] * m.p[k][j]);
				}
			}
		}
		return res;
	}

	Matrix operator*(long double k)
	{
		Matrix res(rows_, cols_);
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				res.p[i][j] = p[i][j] * k;
			}
		}
		return res;
	}

	bool operator>=(const Matrix& m)
	{
		bool flag = true;
		int count = 0;
		for (int i = 0; i < rows_; i++)
		{
			if (abs(p[i][0]) < abs(m.p[i][0]))
			{
				count++;
			}
		}
		if(count == this->getRows())
            flag = false;
		return flag;
	}

	long double operator%(const Matrix& m)
	{
		if (rows_ != m.rows_ || cols_ != 1 || m.cols_ != 1) { cout << "U NAS PROBLEMI, H'USTON"; }

		long double sum = 0;
		for (int i = 0; i < rows_; i++) {
			sum += p[i][0] * m.p[i][0];
		}
		return sum;
	}
};

void createRandomMatr()
{
	ofstream out("matr.txt");
	
	srand(time(NULL)); 
    int n = 0;
	cout << "Enter n for random matrix: "; 
    cin >> n;
    int **a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int [n]; 
    } 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 10; 
            out << a[i][j] << " "; 
        }
        out << rand() % 10;
        out << '\n';
    } 
}

Matrix createE(int n)
    {
        Matrix B(n, n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
            {
                if(i == j) B.p[i][j] = 1;
                else B.p[i][j] = 0;
            }
        }
        return B;
    }

int main()
{
	createRandomMatr(); 
	const char* S = "matr.txt";
	Matrix Slau(S);
	Matrix A = Slau.createA();
	A = A * A.sopr();
	Matrix B = Slau.createB();
	Matrix X(Slau.getRows(), 1);
	X.fillNumbers(0.0);

	cout << "Enter e: ";
	long double e;
	cin >> e;
	Matrix E(Slau.getRows(), 1);
	E.fillNumbers(e);

	int count = 1;
    Matrix R = A * X - B;
    long double b_k = -(R%R) / ((A * R) % R);
	Matrix D = R * b_k;
	X = X + D;
	while (A * X - B >= E) 
	{
        R = A * X - B;
        long double a_k = ((R % R) * ((A * R) % D) - (R % D) * ((A * R) % R)) / 
        (((A * D) % D) * ((A * R) % R) - ((A * R) % D) * ((A * R) % D));
        long double b_k = ((R % D) * ((A * R) % D) - (R % R) * ((A * D) % D)) / 
        (((A * D) % D) * ((A * R) % R) - ((A * R) % D) * ((A * R) % D));
        D = D * a_k + R * b_k;
        X = X + D;
		count++;
	}
	X.show();
	cout <<"________________________count = " <<count << endl;
	Matrix P = A * X - B;
	P.show();
	
	return 0;
}

