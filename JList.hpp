#pragma once
#include<iostream>

//结点指针就相当于是迭代器

//结点类
template<class Type>
class JPoint
{
public:
	JPoint();
	JPoint(Type val);
	JPoint(JPoint& pot);
	~JPoint();
	bool operator==(JPoint& pot);
	bool operator!=(JPoint& pot);
public:
	Type val;
	JPoint* next;
	JPoint* last;
};
//构造
template<class Type>
JPoint<Type>::JPoint()//默认构造
{
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
JPoint<Type>::JPoint(Type val)//有参构造
{
	this->val = val;
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
JPoint<Type>::JPoint(JPoint& pot)//拷贝构造
{
	this->val = pot.val;
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
JPoint<Type>::~JPoint()//析构
{
	this->next = NULL;
	this->last = NULL;
}


//重载JPoint类左移运算符
template<class Type>
std::ostream& operator<<(std::ostream& cout, JPoint<Type>& pot)
{
	cout << pot.val;
	return cout;
}

//重载JPoint的operator==
template<class Type>
bool JPoint<Type>::operator==(JPoint<Type>& pot)
{
	if (this->val == pot.val)
	{
		return true;
	}
	return false;
}
//重载JPoint的operator!=
template<class Type>
bool JPoint<Type>::operator!=(JPoint<Type>& pot)
{
	if (this->val != pot.val)
	{
		return true;
	}
	return false;
}

//提供JPoint类的swap全局函数
template<class Type>
inline void pointSwap(JPoint<Type> * pot1, JPoint<Type> * pot2)
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
	JList(JList<Type>& lt);
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
	bool insert(JPoint<Type>* pos, Type val);
	bool erase(Type val);
	bool erase(JPoint<Type>* pos, Type val);
	//数据查找
	JPoint<Type>* find(Type val);
	JPoint<Type>* find(JPoint<Type>* pos, Type val);
	JPoint<Type>* find_if(JPoint<Type>* pos, Type val,bool (*_Pred)());
	JPoint<Type>* find_if(JPoint<Type>* pos, Type val,bool (*_Pred)(Type val));
		//仿函数版本
	template<class _Pred>
	JPoint<Type>* find_if(JPoint<Type>* pos, Type val,_Pred pred);
	//实用算法
	void sort(JPoint<Type>* beg, JPoint<Type>* end);
	void sort(JPoint<Type>* beg, JPoint<Type>* end,bool (*_Pred)(Type val_1,Type val_2));
	template<class _Pred>
	void sort(JPoint<Type>* beg, JPoint<Type>* end,_Pred pred);

	void for_each(JPoint<Type>* beg, JPoint<Type>* end, void (*_Pred)());
	void for_each(JPoint<Type>* beg, JPoint<Type>* end, void (*_Pred)(Type val));
	template<class _Pred>
	void for_each(JPoint<Type>* beg, JPoint<Type>* end,_Pred pred);
	//遍历用迭代器
	JPoint<Type>* front();
	JPoint<Type>* back();
	JPoint<Type>* end();

protected:
	//安全遍历函数
	inline bool isSafeInterval(JPoint<Type>* beg, JPoint<Type>* end);
protected:
	int m_Size;							//list的大小

	JPoint<Type>* m_Front;				//头指针
	JPoint<Type>* m_Back;				//尾指针
	JPoint<Type>* m_End;					//结束指针(在尾指针后面)

	JPoint<Type>* m_Quick;				//快指针
	JPoint<Type>* m_Slow;				//慢指针

	JPoint<Type> m_Object_For_EndPtr;	//结束指针专用对象，勿挪用!!!
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
JList<Type>::JList(JList<Type>& lt)//拷贝构造
{
	//先构造一遍(照搬默认构造)
	this->m_Size = 0;
	this->m_Front = NULL;
	this->m_Back = NULL;
	this->m_Quick = NULL;
	this->m_Slow = NULL;
	this->m_End = &this->m_Object_For_EndPtr;

	//创建头结点(照搬push_back)
	this->m_Front = new JPoint<Type>(lt.m_Front->val);
	m_Quick = m_Front;
	m_Slow = m_Front;
	m_Back = m_Front;
	m_Back->next = m_End;
	m_End->last = m_Back;
	m_Size = 1;
	//写入
	for (JPoint<Type>* it = lt.front()->next; it != lt.end(); it = it->next)
	{
		this->push_back(it->val);
	}
}
template<class Type>
JList<Type>::~JList()//析构
{
	this->clear();
}

//安全遍历函数
template<class Type>
inline bool JList<Type>::isSafeInterval(JPoint<Type>* beg, JPoint<Type>* end)
{
	JPoint<Type>* ite = beg;
	while (*ite != m_Object_For_EndPtr)
	{
		if (ite == end)
		{
			return true;
		}
		ite = ite->next;
	}
	if (ite == end)
	{
		return true;
	}
	return false;
}


//数据存储
template<class Type>
void JList<Type>::push_back(Type val)
{
	//判断头指针
	if (this->m_Front == NULL)
	{
		//头指针建立
		m_Front = new JPoint<Type>(val);

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
	m_Quick = new JPoint<Type>(val);

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
		m_Front = new JPoint<Type>(val);

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
	m_Quick = new JPoint<Type>(val);

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
	JPoint<Type>* oldFront = m_Front;

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
JPoint<Type>* JList<Type>::front()
{
	return this->m_Front;
}
template<class Type>
JPoint<Type>* JList<Type>::back()
{
	return this->m_Back;
}
template<class Type>
JPoint<Type>* JList<Type>::end()
{
	return this->m_End;
}

//数据查找(返回一个结点指针，找不到返回end)
template<class Type>
JPoint<Type>* JList<Type>::find(Type val)
{
	JPoint<Type>* it = this->front();//创建迭代器
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
JPoint<Type>* JList<Type>::find(JPoint<Type>* pos, Type val)
{
	JPoint<Type>* it = pos;//创建迭代器
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
//条件查找
template<class Type>
JPoint<Type>* JList<Type>::find_if(JPoint<Type>* pos, Type val,bool (*_Pred)())
{
	JPoint<Type>* it = pos;//创建迭代器
	for (; it != this->m_End; it = it->next)
	{
		if (_Pred())
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
template<class Type>
JPoint<Type>* JList<Type>::find_if(JPoint<Type>* pos, Type val,bool (*_Pred)(Type val))
{
	JPoint<Type>* it = pos;//创建迭代器
	for (; it != this->m_End; it = it->next)
	{
		if (_Pred(it->val))
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
	//仿函数版本
template<class Type>template<class _Pred>
JPoint<Type>* JList<Type>::find_if(JPoint<Type>* pos, Type val,_Pred pred)
{
	JPoint<Type>* it = pos;//创建迭代器
	for (; it != this->m_End; it = it->next)
	{
		if (pred(it->val))
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
bool JList<Type> ::insert(JPoint<Type>* pos, Type val)
{
	//判断无效指针
	if (pos == nullptr || pos == this->m_End)
	{
		return false;
	}

	//在中间插入(含头尾结点情况)  需要插入到pos的后面

	//创建结点指针
	JPoint<Type>* ptr = new JPoint<Type>(val);

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
	JPoint<Type>* ptr = this->find(val);
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
bool JList<Type> ::erase(JPoint<Type>* pos, Type val)//从何处开始，删掉什么
{
	JPoint<Type>* ptr = this->find(pos, val);
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

//排序
template<class Type>
void JList<Type>::sort(JPoint<Type>* beg, JPoint<Type>* end)
{
	if (!isSafeInterval(beg, end))
	{
		return;
	}
	//默认升序(采用bubbleSort)
	for (JPoint<Type>* i = beg; i != end->last; i=i->next)
	{
		for (JPoint<Type>* j = beg; j != end->last; j = j->next)
		{
			if ((j->val) > (j->next->val))
			{
				pointSwap(j, j->next);
			}
		}
	}
}
template<class Type>
void JList<Type>::sort(JPoint<Type>* beg, JPoint<Type>* end,bool (*_Pred)(Type val_1,Type val_2))
{
	if (!isSafeInterval(beg, end))
	{
		return;
	}
	//默认升序(采用bubbleSort)
	for (JPoint<Type>* i = beg; i != end->last; i=i->next)
	{
		for (JPoint<Type>* j = beg; j != end->last; j = j->next)
		{
			if (_Pred(j->val,(j->next->val)))
			{
				pointSwap(j, j->next);
			}
		}
	}
}

//遍历
template<class Type>
void JList<Type>::for_each(JPoint<Type>* beg, JPoint<Type>* end, void (*_Pred)())
{
	if (!isSafeInterval(beg, end))
	{
		return;
	}
	for(JPoint<Type> * it=beg;it!=end;it=it->next)
	{
		_Pred();
	}
}

template<class Type>
void JList<Type>::for_each(JPoint<Type>* beg, JPoint<Type>* end, void (*_Pred)(Type val))
{
	if (!isSafeInterval(beg, end))
	{
		return;
	}
	for(JPoint<Type> * it=beg;it!=end;it=it->next)
	{
		_Pred(it->val);
	}
}

//仿函数测试
template<class Type>template<class _Pred>
void JList<Type>::for_each(JPoint<Type>* beg, JPoint<Type>* end,_Pred pred)
{
	if (!isSafeInterval(beg, end))
	{
		return;
	}
	for(JPoint<Type> * it=beg;it!=end;it=it->next)
	{
		pred(it->val);
	}
}
template<class Type>template<class _Pred>
void JList<Type>::sort(JPoint<Type>* beg, JPoint<Type>* end, _Pred pred)
{
	if (!isSafeInterval(beg, end))
	{
		return;
	}
	//默认升序(采用bubbleSort)
	for (JPoint<Type>* i = beg; i != end->last; i=i->next)
	{
		for (JPoint<Type>* j = beg; j != end->last; j = j->next)
		{
			if (pred(j->val,(j->next->val)))
			{
				pointSwap(j, j->next);
			}
		}
	}
}
