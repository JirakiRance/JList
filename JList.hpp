#pragma once
#include<iostream>

//结点指针就相当于是迭代器

//结点类
template<class Type>
class Point
{
public:
	Point();
	Point(Type val);
	~Point();
public:
	Type val;
	Point* next;
	Point* last;
};
//构造
template<class Type>
Point<Type>::Point()//默认构造
{
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
Point<Type>::Point(Type val)//有参构造
{
	this->val = val;
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
Point<Type>::~Point()//析构
{
	this->next = NULL;
	this->last = NULL;
}


//重载Point类左移运算符
template<class Type>
std::ostream& operator<<(std::ostream& cout, Point<Type>& pot)
{
	cout << pot.val;
	return cout;
}

//提供Point类的swap全局函数
template<class Type>
inline void pointSwap(Point<Type> * pot1, Point<Type> * pot2)
{
	Type temp = pot1->val;
	pot1->val = pot2->val;
	pot2->val = temp;
}

//**********************************************************************//


//链表类
template<class Type>
class JList
{
public:

	//构造和析构
	JList();
	~JList();

	//方法

		//大小
	int size();
	//数据存储与删除
	void push_back(Type val);
	void push_front(Type val);
	void pop_back();
	void pop_front();
	void clear();
	//数据插入与移除
	bool insert(Point<Type>* pos, Type val);
	bool erase(Type val);
	bool erase(Point<Type>* pos, Type val);
	//数据查找
	Point<Type>* find(Type val);
	Point<Type>* find(Point<Type>* ptr, Type val);
	//实用算法
	void sort(Point<Type>* beg, Point<Type>* end);
	void sort(Point<Type>* beg, Point<Type>* end, bool (*_Pred)(Type val));
	//遍历用迭代器
	Point<Type>* front();
	Point<Type>* back();
	Point<Type>* end();


private:
	int m_Size;							//list的大小

	Point<Type>* m_Front;				//头指针
	Point<Type>* m_Back;				//尾指针
	Point<Type>* m_End;					//结束指针(在尾指针后面)

	Point<Type>* m_Quick;				//快指针
	Point<Type>* m_Slow;				//慢指针

	Point<Type> m_Object_For_EndPtr;	//结束指针专用对象，勿挪用!!!
};


//构造和析构
template<class Type>
JList<Type>::JList()//默认构造
{
	this->m_Size = 0;
	this->m_Front = NULL;
	this->m_Back = NULL;
	this->m_Quick = NULL;
	this->m_Slow = NULL;
	this->m_End = &this->m_Object_For_EndPtr;
}
template<class Type>
JList<Type>::~JList()//析构
{
	this->clear();
}


//数据存储
template<class Type>
void JList<Type>::push_back(Type val)
{
	//判断头指针
	if (this->m_Front == NULL)
	{
		//头指针建立
		m_Front = new Point<Type>(val);

		//推进指针
		m_Quick = m_Front;
		m_Slow = m_Front;

		//尾指针以及结束指针
		m_Back = m_Front;
		m_Back->next = m_End;
		m_End->last = m_Back;

		//更新大小，结束函数
		m_Size++;
		return;
	}
	//已有头指针

	//先创建结点
	m_Quick = new Point<Type>(val);

	//链接结点
	m_Slow->next = m_Quick;
	m_Quick->last = m_Slow;


	//更新慢指针以及尾指针,结束指针
	m_Slow = m_Quick;
	m_Back = m_Quick;
	m_Back->next = m_End;
	m_End->last = m_Back;

	//更新大小
	m_Size++;
}

template<class Type>
void JList<Type>::push_front(Type val)
{
	//判断头指针
	if (this->m_Front == NULL)
	{
		//头指针建立
		m_Front = new Point<Type>(val);

		//推进指针
		m_Quick = m_Front;
		m_Slow = m_Front;

		//尾指针以及结束指针
		m_Back = m_Front;
		m_Back->next = m_End;
		m_End->last = m_Back;

		//更新大小，结束函数
		m_Size++;
		return;
	}
	//已有头指针

	//先创建结点
	m_Quick = new Point<Type>(val);

	//链接结点
	m_Front->last = m_Quick;
	m_Quick->next = m_Front;


	//更新快指针 以及 头指针
	m_Front = m_Quick;
	m_Quick = m_Back;

	//更新大小
	m_Size++;
}

//数据删除
template<class Type>
void JList<Type>::pop_back()
{
	if (m_Size == 0)//如果没有结点，直接返回
	{
		return;
	}
	else if (m_Size == 1)//只有一个结点
	{
		//断绝与end关系
		m_Quick->next = NULL;
		m_End->last = NULL;

		//释放内存
		delete m_Quick;

		//全部重置
		m_Size = 0;

		m_Front->next = NULL;
		m_Front->last = NULL;
		m_Front = NULL;

		m_Back->next = NULL;
		m_Back->last = NULL;
		m_Back = NULL;

		m_Quick->next = NULL;
		m_Quick->last = NULL;
		m_Quick = NULL;

		m_Slow->next = NULL;
		m_Slow->last = NULL;
		m_Slow = NULL;

		m_End = &this->m_Object_For_EndPtr;
		m_End->next = NULL;
		m_End->last = NULL;
		return;
	}
	else//有多个结点
	{
		//先快指针退回 以及 尾指针,结束指针退回
		m_Quick = m_Slow->last;
		m_Back = m_Quick;

		//快指针断绝下层关系
		m_Quick->next = m_End;
		m_End->last = m_Quick;

		//慢指针断绝上层关系
		m_Slow->last = NULL;
		m_Slow->next = NULL;

		//释放慢指针指向内存
		delete m_Slow;
		//慢指针退回
		m_Slow = m_Quick;

		//更新大小
		m_Size--;
	}
}

template<class Type>
void JList<Type>::pop_front()
{
	//如果没有结点，直接返回
	if (m_Size == 0)
	{
		return;
	}

	//先创建旧头指针
	Point<Type>* oldFront = m_Front;

	//更新头指针
	m_Front = m_Front->next;
	//如果头指针指向结束指针，属性重置(只有一个结点,被删除的情况)
	if (m_Front == m_End)
	{
		m_Size = 0;

		m_Front->next = NULL;
		m_Front->last = NULL;
		m_Front = NULL;

		m_Back->next = NULL;
		m_Back->last = NULL;
		m_Back = NULL;

		m_Quick->next = NULL;
		m_Quick->last = NULL;
		m_Quick = NULL;

		m_Slow->next = NULL;
		m_Slow->last = NULL;
		m_Slow = NULL;

		m_End = &this->m_Object_For_EndPtr;
		m_End->next = NULL;
		m_End->last = NULL;
		return;
	}

	//断绝关系
	m_Front->last = NULL;
	oldFront->next = NULL;

	//释放旧头指针指向内存
	delete oldFront;

	//更新大小
	m_Size--;
}

//返还头 尾 结束 结点指针
template<class Type>
Point<Type>* JList<Type>::front()
{
	return this->m_Front;
}
template<class Type>
Point<Type>* JList<Type>::back()
{
	return this->m_Back;
}
template<class Type>
Point<Type>* JList<Type>::end()
{
	return this->m_End;
}

//数据查找(返回一个结点指针，找不到返回end)
template<class Type>
Point<Type>* JList<Type>::find(Type val)
{
	Point<Type>* it = this->front();//创建迭代器
	for (; it != this->m_End; it = it->next)
	{
		if (it->val == val)
		{
			return it;
		}
	}
	//判断结束指针
	if (it == this->m_End)
	{
		return m_End;
	}
}
//数据查找(提供指针重载版本)
template<class Type>
Point<Type>* JList<Type>::find(Point<Type>* ptr, Type val)
{
	Point<Type>* it = ptr;//创建迭代器
	for (; it != this->m_End; it = it->next)
	{
		if (it->val == val)
		{
			return it;
		}
	}
	//判断结束指针
	if (it == this->m_End)
	{
		return m_End;
	}
}


//链表大小
template<class Type>
int JList<Type>::size()
{
	return this->m_Size;
}

//中间插入(位置，值)(并返回真假)
template<class Type>
bool JList<Type> ::insert(Point<Type>* pos, Type val)
{
	//判断无效指针
	if (pos == nullptr || pos == this->m_End)
	{
		return false;
	}

	//在中间插入(含头尾结点情况)  需要插入到pos的后面

	//创建结点指针
	Point<Type>* ptr = new Point<Type>(val);

	//链接结点(先将新节点入链，再断开原链)
	ptr->next = pos->next;
	ptr->last = pos;

	(pos->next)->last = ptr;
	pos->next = ptr;

	//连接成功，更新size
	m_Size++;
	return true;
}

//擦除(两个版本: 1.值  2.位置，值)(并返回真假)
template<class Type>
bool JList<Type> ::erase(Type val)
{
	Point<Type>* ptr = this->find(val);
	if (ptr == NULL || ptr == m_End)//无效情况
	{
		return false;
	}
	if (ptr == m_Front)//头指针情况
	{
		this->pop_front();
		return false;
	}
	//非头指针

	//快慢指针
	m_Quick = ptr->next;
	m_Slow = ptr->last;

	//断绝关系
	m_Quick->last = m_Slow;
	m_Slow->next = m_Quick;
	ptr->next = NULL;
	ptr->last = NULL;

	//释放内存
	delete ptr;
	m_Size--;
	return true;
}
template<class Type>
bool JList<Type> ::erase(Point<Type>* pos, Type val)//从何处开始，删掉什么
{
	Point<Type>* ptr = this->find(pos, val);
	if (ptr == NULL || ptr == m_End)//无效情况
	{
		return false;
	}
	if (ptr == m_Front)//头指针情况
	{
		this->pop_front();
		return false;
	}

	//快慢指针
	m_Quick = ptr->next;
	m_Slow = ptr->last;

	//断绝关系
	m_Quick->last = m_Slow;
	m_Slow->next = m_Quick;
	ptr->next = NULL;
	ptr->last = NULL;

	//释放内存
	delete ptr;
	m_Size--;
	return true;
}

//清空
template<class Type>
void JList<Type>::clear()
{
	if (m_Size == 0)
	{
		return;
	}
	while (m_Front != m_Back)
	{
		this->pop_front();
	}
	this->pop_front();
}

//实用算法
template<class Type>
void JList<Type>::sort(Point<Type>* beg, Point<Type>* end)
{
	//默认升序(采用bubbleSort)
	for (Point<Type>* i = beg; i != end; i=i->next)
	{
		for (Point<Type>* j = i; j != end; j = j->next)
		{
			if ((j->val) > (j->next->val))
			{
				pointSwap(j, j->next);
			}
		}
	}
}
