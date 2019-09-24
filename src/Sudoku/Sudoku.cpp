#include "pch.h"
#include<iostream>
#include<fstream>
#include <cstdlib>
int su[9][9];
int a[10] = { 0 };//a数组下标为出现过的数，值为出现次数
using namespace std;
class sudoku
{
private:
	int row;
	int col;
	int sum;// 为val数组可达到的最大下标 
	int val[9];
public:
	void setrow_col(int r, int c);
	void setsum();
	void setval_sum(int num);
	int getval(int t);
	int getsum();
	int getrow();
	int getcol();
}s[81];
void sudoku::setrow_col(int r, int c)//对数据成员行列进行赋值 
{
	col = c;
	row = r;
}
void sudoku::setsum()//每当回溯一次，数值减1 
{
	sum = sum - 1;
}
void sudoku::setval_sum(int num)//将该空格可能的数值填入val数组中 ；num为数独阶数  
{
	int i, j = 0;
	for (i = 1; i <= num; i++)
	{
		if (a[i] == 0)
		{
			val[j] = i;
			j++;
		}
	}
	sum = j - 1;
}
int sudoku::getval(int t)
{
	return val[t];
}
int sudoku::getsum()
{
	return sum;
}
int sudoku::getcol()
{
	return col;
}
int sudoku::getrow()
{
	return row;
}
void cheak(int r, int c, int num)//遍历该空格所在行、列、宫中出现的数
{
	int i, j, x, y;
	for (i = 0; i < 10; i++)
	{
		a[i] = 0;
	}
	for (i = 0; i < num; i++)//查看所在行出现的数 
	{
		if (su[r][i] != 0)
			a[su[r][i]] = a[su[r][i]] + 1;
	}
	for (i = 0; i < num; i++)//查看所在列出现的数 
	{
		if (su[i][c] != 0)
			a[su[i][c]] = a[su[i][c]] + 1;
	}
	if (num == 4)//查看所在宫出现的数 
	{
		x = r / 2;
		y = c / 2;
		for (i = x * 2; i <= (x * 2 + 1); i++)
		{
			for (j = y * 2; j <= (y * 2 + 1); j++)
			{
				if (su[i][j] != 0)
					a[su[i][j]] = a[su[i][j]] + 1;
			}
		}
	}
	else if (num == 6)
	{
		x = r / 2;
		y = c / 3;
		for (i = x * 2; i <= (x * 2 + 1); i++)
		{
			for (j = y * 3; j <= (y * 3 + 2); j++)
			{
				if (su[i][j] != 0)
					a[su[i][j]] = a[su[i][j]] + 1;
			}
		}
	}
	else if (num == 8)
	{
		x = r / 4;
		y = c / 2;
		for (i = x * 4; i <= (x * 4 + 3); i++)
		{
			for (j = y * 2; j <= (y * 2 + 1); j++)
			{
				if (su[i][j] != 0)
					a[su[i][j]] = a[su[i][j]] + 1;
			}
		}
	}
	else if (num == 9)
	{
		x = r / 3;
		y = c / 3;
		for (i = x * 3; i <= (x * 3 + 2); i++)
		{
			for (j = y * 3; j <= (y * 3 + 2); j++)
			{
				if (su[i][j] != 0)
					a[su[i][j]] = a[su[i][j]] + 1;
			}
		}
	}
}
int back(int t)//重置该空格的值 
{
	if (s[t].getsum() >= 0)
	{
		su[s[t].getrow()][s[t].getcol()] = s[t].getval(s[t].getsum());
		s[t].setsum();
	}
	else
	{
		su[s[t].getrow()][s[t].getcol()] = 0;
		t = back(t - 1);
	}
	return t;
}
int main(int argc, char** argv)
{
	int i, j, p = 0, n, m;
	ifstream ifp;
	ofstream ofp;
	m = atoi(argv[2]);//宫阶数 
	n = atoi(argv[4]);//盘面数 
	ifp.open(argv[6]);
	if (!ifp.is_open())
		cout << "文件打开失败" << endl;
	ofp.open(argv[8]);
	if (!ofp.is_open())
		cout << "文件打开失败" << endl;
	while (n > 0)
	{
		for (i = 0; i < m; i++)//输入数独盘面 
		{
			for (j = 0; j < m; j++)
			{
				ifp >> su[i][j];
			}
		}
		p = 0;
		for (i = 0; i < m; i++)//解数独 
		{
			for (j = 0; j < m; j++)
			{
				if (su[i][j] == 0)//需要填数的空格 
				{
					s[p].setrow_col(i, j);
					cheak(i, j, m);
					s[p].setval_sum(m);
					if (s[p].getsum() >= 0)//如存在可能，则填入空格 
					{
						su[i][j] = s[p].getval(s[p].getsum());
						s[p].setsum();
						p++;
					}
					else//如不存在可能，则回到上一个空格处 
					{
						p = p - 1;
						p = back(p);
						j = s[p].getcol();
						i = s[p].getrow();
						p++;
					}
				}
			}
		}
		for (i = 0; i < m; i++)//输出解出的数独 
		{
			for (j = 0; j < m; j++)
			{
				if (j < (m - 1))
					ofp << su[i][j] << " ";
				else
					ofp << su[i][j];
			}
			ofp << endl;
		}
		ofp << endl;
		n--;
	}
	ifp.close();
	ofp.close();
	return 0;
}
