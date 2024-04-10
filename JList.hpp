#pragma once
#include<iostream>

//���ָ����൱���ǵ�����

//�����
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
//����
template<class Type>
Point<Type>::Point()//Ĭ�Ϲ���
{
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
Point<Type>::Point(Type val)//�вι���
{
	this->val = val;
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
Point<Type>::~Point()//����
{
	this->next = NULL;
	this->last = NULL;
}


//����Point�����������
template<class Type>
std::ostream& operator<<(std::ostream& cout, Point<Type>& pot)
{
	cout << pot.val;
	return cout;
}

//�ṩPoint���swapȫ�ֺ���
template<class Type>
inline void pointSwap(Point<Type> * pot1, Point<Type> * pot2)
{
	Type temp = pot1->val;
	pot1->val = pot2->val;
	pot2->val = temp;
}

//**********************************************************************//


//������
template<class Type>
class JList
{
public:

	//���������
	JList();
	~JList();

	//����

		//��С
	int size();
	//���ݴ洢��ɾ��
	void push_back(Type val);
	void push_front(Type val);
	void pop_back();
	void pop_front();
	void clear();
	//���ݲ������Ƴ�
	bool insert(Point<Type>* pos, Type val);
	bool erase(Type val);
	bool erase(Point<Type>* pos, Type val);
	//���ݲ���
	Point<Type>* find(Type val);
	Point<Type>* find(Point<Type>* ptr, Type val);
	//ʵ���㷨
	void sort(Point<Type>* beg, Point<Type>* end);
	void sort(Point<Type>* beg, Point<Type>* end, bool (*_Pred)(Type val));
	//�����õ�����
	Point<Type>* front();
	Point<Type>* back();
	Point<Type>* end();


private:
	int m_Size;							//list�Ĵ�С

	Point<Type>* m_Front;				//ͷָ��
	Point<Type>* m_Back;				//βָ��
	Point<Type>* m_End;					//����ָ��(��βָ�����)

	Point<Type>* m_Quick;				//��ָ��
	Point<Type>* m_Slow;				//��ָ��

	Point<Type> m_Object_For_EndPtr;	//����ָ��ר�ö�����Ų��!!!
};


//���������
template<class Type>
JList<Type>::JList()//Ĭ�Ϲ���
{
	this->m_Size = 0;
	this->m_Front = NULL;
	this->m_Back = NULL;
	this->m_Quick = NULL;
	this->m_Slow = NULL;
	this->m_End = &this->m_Object_For_EndPtr;
}
template<class Type>
JList<Type>::~JList()//����
{
	this->clear();
}


//���ݴ洢
template<class Type>
void JList<Type>::push_back(Type val)
{
	//�ж�ͷָ��
	if (this->m_Front == NULL)
	{
		//ͷָ�뽨��
		m_Front = new Point<Type>(val);

		//�ƽ�ָ��
		m_Quick = m_Front;
		m_Slow = m_Front;

		//βָ���Լ�����ָ��
		m_Back = m_Front;
		m_Back->next = m_End;
		m_End->last = m_Back;

		//���´�С����������
		m_Size++;
		return;
	}
	//����ͷָ��

	//�ȴ������
	m_Quick = new Point<Type>(val);

	//���ӽ��
	m_Slow->next = m_Quick;
	m_Quick->last = m_Slow;


	//������ָ���Լ�βָ��,����ָ��
	m_Slow = m_Quick;
	m_Back = m_Quick;
	m_Back->next = m_End;
	m_End->last = m_Back;

	//���´�С
	m_Size++;
}

template<class Type>
void JList<Type>::push_front(Type val)
{
	//�ж�ͷָ��
	if (this->m_Front == NULL)
	{
		//ͷָ�뽨��
		m_Front = new Point<Type>(val);

		//�ƽ�ָ��
		m_Quick = m_Front;
		m_Slow = m_Front;

		//βָ���Լ�����ָ��
		m_Back = m_Front;
		m_Back->next = m_End;
		m_End->last = m_Back;

		//���´�С����������
		m_Size++;
		return;
	}
	//����ͷָ��

	//�ȴ������
	m_Quick = new Point<Type>(val);

	//���ӽ��
	m_Front->last = m_Quick;
	m_Quick->next = m_Front;


	//���¿�ָ�� �Լ� ͷָ��
	m_Front = m_Quick;
	m_Quick = m_Back;

	//���´�С
	m_Size++;
}

//����ɾ��
template<class Type>
void JList<Type>::pop_back()
{
	if (m_Size == 0)//���û�н�㣬ֱ�ӷ���
	{
		return;
	}
	else if (m_Size == 1)//ֻ��һ�����
	{
		//�Ͼ���end��ϵ
		m_Quick->next = NULL;
		m_End->last = NULL;

		//�ͷ��ڴ�
		delete m_Quick;

		//ȫ������
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
	else//�ж�����
	{
		//�ȿ�ָ���˻� �Լ� βָ��,����ָ���˻�
		m_Quick = m_Slow->last;
		m_Back = m_Quick;

		//��ָ��Ͼ��²��ϵ
		m_Quick->next = m_End;
		m_End->last = m_Quick;

		//��ָ��Ͼ��ϲ��ϵ
		m_Slow->last = NULL;
		m_Slow->next = NULL;

		//�ͷ���ָ��ָ���ڴ�
		delete m_Slow;
		//��ָ���˻�
		m_Slow = m_Quick;

		//���´�С
		m_Size--;
	}
}

template<class Type>
void JList<Type>::pop_front()
{
	//���û�н�㣬ֱ�ӷ���
	if (m_Size == 0)
	{
		return;
	}

	//�ȴ�����ͷָ��
	Point<Type>* oldFront = m_Front;

	//����ͷָ��
	m_Front = m_Front->next;
	//���ͷָ��ָ�����ָ�룬��������(ֻ��һ�����,��ɾ�������)
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

	//�Ͼ���ϵ
	m_Front->last = NULL;
	oldFront->next = NULL;

	//�ͷž�ͷָ��ָ���ڴ�
	delete oldFront;

	//���´�С
	m_Size--;
}

//����ͷ β ���� ���ָ��
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

//���ݲ���(����һ�����ָ�룬�Ҳ�������end)
template<class Type>
Point<Type>* JList<Type>::find(Type val)
{
	Point<Type>* it = this->front();//����������
	for (; it != this->m_End; it = it->next)
	{
		if (it->val == val)
		{
			return it;
		}
	}
	//�жϽ���ָ��
	if (it == this->m_End)
	{
		return m_End;
	}
}
//���ݲ���(�ṩָ�����ذ汾)
template<class Type>
Point<Type>* JList<Type>::find(Point<Type>* ptr, Type val)
{
	Point<Type>* it = ptr;//����������
	for (; it != this->m_End; it = it->next)
	{
		if (it->val == val)
		{
			return it;
		}
	}
	//�жϽ���ָ��
	if (it == this->m_End)
	{
		return m_End;
	}
}


//�����С
template<class Type>
int JList<Type>::size()
{
	return this->m_Size;
}

//�м����(λ�ã�ֵ)(���������)
template<class Type>
bool JList<Type> ::insert(Point<Type>* pos, Type val)
{
	//�ж���Чָ��
	if (pos == nullptr || pos == this->m_End)
	{
		return false;
	}

	//���м����(��ͷβ������)  ��Ҫ���뵽pos�ĺ���

	//�������ָ��
	Point<Type>* ptr = new Point<Type>(val);

	//���ӽ��(�Ƚ��½ڵ��������ٶϿ�ԭ��)
	ptr->next = pos->next;
	ptr->last = pos;

	(pos->next)->last = ptr;
	pos->next = ptr;

	//���ӳɹ�������size
	m_Size++;
	return true;
}

//����(�����汾: 1.ֵ  2.λ�ã�ֵ)(���������)
template<class Type>
bool JList<Type> ::erase(Type val)
{
	Point<Type>* ptr = this->find(val);
	if (ptr == NULL || ptr == m_End)//��Ч���
	{
		return false;
	}
	if (ptr == m_Front)//ͷָ�����
	{
		this->pop_front();
		return false;
	}
	//��ͷָ��

	//����ָ��
	m_Quick = ptr->next;
	m_Slow = ptr->last;

	//�Ͼ���ϵ
	m_Quick->last = m_Slow;
	m_Slow->next = m_Quick;
	ptr->next = NULL;
	ptr->last = NULL;

	//�ͷ��ڴ�
	delete ptr;
	m_Size--;
	return true;
}
template<class Type>
bool JList<Type> ::erase(Point<Type>* pos, Type val)//�Ӻδ���ʼ��ɾ��ʲô
{
	Point<Type>* ptr = this->find(pos, val);
	if (ptr == NULL || ptr == m_End)//��Ч���
	{
		return false;
	}
	if (ptr == m_Front)//ͷָ�����
	{
		this->pop_front();
		return false;
	}

	//����ָ��
	m_Quick = ptr->next;
	m_Slow = ptr->last;

	//�Ͼ���ϵ
	m_Quick->last = m_Slow;
	m_Slow->next = m_Quick;
	ptr->next = NULL;
	ptr->last = NULL;

	//�ͷ��ڴ�
	delete ptr;
	m_Size--;
	return true;
}

//���
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

//ʵ���㷨
template<class Type>
void JList<Type>::sort(Point<Type>* beg, Point<Type>* end)
{
	//Ĭ������(����bubbleSort)
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
