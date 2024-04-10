#include<iostream>
#include"JList.hpp"

using namespace std;


void test01()
{
	JList<int> lt;
	lt.push_back(1);
	lt.push_back(9);
	lt.push_back(2);
	lt.push_back(6);
	lt.push_back(0);
	lt.push_back(3);
	lt.push_back(5);
	lt.push_back(7);

	lt.sort(lt.front(),lt.end());

	for (Point<int>* it = lt.front(); it != lt.end(); it=it->next)
	{
		cout << *it << endl;
	}

}

int main()
{
	test01();

	system("pause");
	return 0;
}