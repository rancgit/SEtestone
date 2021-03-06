// SEtestone.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
using namespace std;

//函数用于判断是否是数字
bool isNum(string str)
{
	//if (str == "") return false;
	stringstream temp(str);
	double d;
	char c;
	if (!(temp >> d))
		return false;
	if (temp >> c)
		return false;
	return true;
}

//该函数用于处理输入,输入的数据将用容器返回，第一个参数是最大的个数，第二个参数是遇到该值后函数返回
vector<double> getAllInput(int tsum=100,int numreturn=-999)
{
	int sum=0;
	string numStr;
	vector<double> numVec;
	while (getline(std::cin, numStr))
	{//读取每一行
		istringstream iss(numStr), end;
		istream_iterator<std::string> Itbegin = istream_iterator<std::string>(iss);
		istream_iterator<std::string> ItEnd = istream_iterator<std::string>();
		vector<string> initVec(Itbegin, ItEnd);//去掉空格存入容器
		for (auto s : initVec)
		{
			if (isNum(s))
			{
				double d = stod(s);
				if (d == numreturn)
					return numVec;
				numVec.push_back(d);
				sum++;
				if (sum == tsum)
				{
					return numVec;
				}
			}

		}
	}
	return numVec;
}

//该函数用于在从小到大排序的容器中，找出某个范围内的所有数据，并用容器返回
vector<double> getNumOfRange(double n1, double n2, vector<double> numVec)
{
	//找出指定范围内的数
	int iter1 = 0, iter2 = numVec.size();
	bool first1 = false;
	bool first2 = false;
	for (auto iter = numVec.begin(); iter != numVec.end(); iter++)
	{
		if (*iter >= n1 && !first1)
		{
			iter1 = iter - numVec.begin();
			//cout << "iter1" << iter1 << " " << *iter << endl;
			first1 = true;
		}
		if (*iter>n2 && !first2)
		{
			iter2 = iter - numVec.begin();
			//cout << "iter2" << iter2 << endl;
			first2 = true;
			break;
		}
	}

	vector<double> tempVec(numVec.begin() + iter1, numVec.begin() + iter2);
	return tempVec;
}

//该函数返回某一个double容器中的数据的总和于均值，第二个参数是总和
void getSumAndAve(vector<double> vec, double &sum, double &average)
{
	 sum = 0;
	 average = 0;
	for (auto e : vec)
	{
		//cout << e << " ";
		sum += e;
	}
	average = sum / vec.size();
}


int main()
{
	cout << "请输入您的数据" << endl;
	cout << "请注意，输入的无效数据将被忽略，形如4rg4等的数据为无效数据" << endl;
	cout << "您可以在输入每一个数据后回车，此时将在输入100个数据或者输入-999后停止" << endl;
	cout << "也可以单行连续输入，以空格为间隔，然后回车，这种情况下将只取前100个数据或者-999以前的数据" << endl;
	cout << "在这里输入您的数据" << endl;	
	int num = 0;
	string numStr;
	vector<double> numVec;
	numVec = getAllInput(10);
	sort(numVec.begin(), numVec.end());
	for (auto s : numVec)
	{
		cout << s << " ";
	}
	//bool inputSucc = false;
	double n1;
	double n2;
	cout << "请分别输入数据的下界n1和上界n2" << endl;
	while (true)
	{
		string str1;
		string str2;
		cin >> str1 >> str2;
		if (!isNum(str1)||!isNum(str2))
		{
			cout << "请输入两个数字" << endl;
			continue;
		}
		n1 = stod(str1);
		n2 = stod(str2);
		if (n2<n1)
		{
			cout << "数据的上界需要大于等于上界" << endl;
			continue;
		}
		break;
	}
	
	//cin >> n1 >> n2;
	cout << "n1和n2分别是" << n1 << " " << n2 << endl;

	vector<double> tempVec = getNumOfRange(n1, n2, numVec);
	double sum = 0;
	double average = 0;
	getSumAndAve(tempVec, sum, average);
	cout << "总和" << sum << endl;
	cout << "均值" << average << endl;
	return 0;
}

