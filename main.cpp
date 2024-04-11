#include<iostream>
#include"JList.hpp"

using namespace std;

bool myCompare01(int v1, int v2)
{
	return v1 > v2;
}
class MyCompare02
{
public:
	bool operator()(int v1,int v2)
	{
		return v1 > v2;
	}
};

void printList(int val)
{
	cout << val << endl;
}

void test01()
{
	JList<int> lt;
	lt.push_back(1);
	lt.push_back(9);
	lt.push_back(2);
	lt.push_back(6);
	lt.push_back(8);
	lt.push_back(4);
	lt.push_back(10);
	lt.push_back(3);
	lt.push_back(5);
	lt.push_back(7);

	//lt.sort(lt.front(),lt.end(), myCompare01);
	lt.sort(lt.front(), lt.end(), MyCompare02());

	cout << endl << "size = " << lt.size() << endl << endl;

	for (Point<int>* it = lt.front(); it != lt.end(); it=it->next)
	{
		cout << *it << endl;
	}

	//lt.for_each(lt.front(), lt.end(), printList);

}

int main()
{
	test01();

	system("pause");
	return 0;
}