#pragma once
#include<iostream>

//���ָ����൱���ǵ�����

//�����
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
//����
template<class Type>
JPoint<Type>::JPoint()//Ĭ�Ϲ���
{
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
JPoint<Type>::JPoint(Type val)//�вι���
{
	this->val = val;
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
JPoint<Type>::JPoint(JPoint& pot)//��������
{
	this->val = pot.val;
	this->next = NULL;
	this->last = NULL;
}

template<class Type>
JPoint<Type>::~JPoint()//����
{
	this->next = NULL;
	this->last = NULL;
}


//����JPoint�����������
template<class Type>
std::ostream& operator<<(std::ostream& cout, JPoint<Type>& pot)
{
	cout << pot.val;
	return cout;
}

//����JPoint��operator==
template<class Type>
bool JPoint<Type>::operator==(JPoint<Type>& pot)
{
	if (this->val == pot.val)
	{
		return true;
	}
	return false;
}
//����JPoint��operator!=
template<class Type>
bool JPoint<Type>::operator!=(JPoint<Type>& pot)
{
	if (this->val != pot.val)
	{
		return true;
	}
	return false;
}

//�ṩJPoint���swapȫ�ֺ���
template<class Type>
inline void pointSwap(JPoint<Type> * pot1, JPoint<Type> * pot2)
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
	JList(JList<Type>& lt);
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
	bool insert(JPoint<Type>* pos, Type val);
	bool erase(Type val);
	bool erase(JPoint<Type>* pos, Type val);
	//���ݲ���
	JPoint<Type>* find(Type val);
	JPoint<Type>* find(JPoint<Type>* pos, Type val);
	JPoint<Type>* find_if(JPoint<Type>* pos, Type val,bool (*_Pred)());
	JPoint<Type>* find_if(JPoint<Type>* pos, Type val,bool (*_Pred)(Type val));
		//�º����汾
	template<class _Pred>
	JPoint<Type>* find_if(JPoint<Type>* pos, Type val,_Pred pred);
	//ʵ���㷨
	void sort(JPoint<Type>* beg, JPoint<Type>* end);
	void sort(JPoint<Type>* beg, JPoint<Type>* end,bool (*_Pred)(Type val_1,Type val_2));
	template<class _Pred>
	void sort(JPoint<Type>* beg, JPoint<Type>* end,_Pred pred);

	void for_each(JPoint<Type>* beg, JPoint<Type>* end, void (*_Pred)());
	void for_each(JPoint<Type>* beg, JPoint<Type>* end, void (*_Pred)(Type val));
	template<class _Pred>
	void for_each(JPoint<Type>* beg, JPoint<Type>* end,_Pred pred);
	//�����õ�����
	JPoint<Type>* front();
	JPoint<Type>* back();
	JPoint<Type>* end();

protected:
	//��ȫ��������
	inline bool isSafeInterval(JPoint<Type>* beg, JPoint<Type>* end);
protected:
	int m_Size;							//list�Ĵ�С

	JPoint<Type>* m_Front;				//ͷָ��
	JPoint<Type>* m_Back;				//βָ��
	JPoint<Type>* m_End;					//����ָ��(��βָ�����)

	JPoint<Type>* m_Quick;				//��ָ��
	JPoint<Type>* m_Slow;				//��ָ��

	JPoint<Type> m_Object_For_EndPtr;	//����ָ��ר�ö�����Ų��!!!
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
JList<Type>::JList(JList<Type>& lt)//��������
{
	//�ȹ���һ��(�հ�Ĭ�Ϲ���)
	this->m_Size = 0;
	this->m_Front = NULL;
	this->m_Back = NULL;
	this->m_Quick = NULL;
	this->m_Slow = NULL;
	this->m_End = &this->m_Object_For_EndPtr;

	//����ͷ���(�հ�push_back)
	this->m_Front = new JPoint<Type>(lt.m_Front->val);
	m_Quick = m_Front;
	m_Slow = m_Front;
	m_Back = m_Front;
	m_Back->next = m_End;
	m_End->last = m_Back;
	m_Size = 1;
	//д��
	for (JPoint<Type>* it = lt.front()->next; it != lt.end(); it = it->next)
	{
		this->push_back(it->val);
	}
}
template<class Type>
JList<Type>::~JList()//����
{
	this->clear();
}

//��ȫ��������
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


//���ݴ洢
template<class Type>
void JList<Type>::push_back(Type val)
{
	//�ж�ͷָ��
	if (this->m_Front == NULL)
	{
		//ͷָ�뽨��
		m_Front = new JPoint<Type>(val);

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
	m_Quick = new JPoint<Type>(val);

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
		m_Front = new JPoint<Type>(val);

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
	m_Quick = new JPoint<Type>(val);

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
	JPoint<Type>* oldFront = m_Front;

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

//���ݲ���(����һ�����ָ�룬�Ҳ�������end)
template<class Type>
JPoint<Type>* JList<Type>::find(Type val)
{
	JPoint<Type>* it = this->front();//����������
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
JPoint<Type>* JList<Type>::find(JPoint<Type>* pos, Type val)
{
	JPoint<Type>* it = pos;//����������
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
//��������
template<class Type>
JPoint<Type>* JList<Type>::find_if(JPoint<Type>* pos, Type val,bool (*_Pred)())
{
	JPoint<Type>* it = pos;//����������
	for (; it != this->m_End; it = it->next)
	{
		if (_Pred())
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
template<class Type>
JPoint<Type>* JList<Type>::find_if(JPoint<Type>* pos, Type val,bool (*_Pred)(Type val))
{
	JPoint<Type>* it = pos;//����������
	for (; it != this->m_End; it = it->next)
	{
		if (_Pred(it->val))
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
	//�º����汾
template<class Type>template<class _Pred>
JPoint<Type>* JList<Type>::find_if(JPoint<Type>* pos, Type val,_Pred pred)
{
	JPoint<Type>* it = pos;//����������
	for (; it != this->m_End; it = it->next)
	{
		if (pred(it->val))
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
bool JList<Type> ::insert(JPoint<Type>* pos, Type val)
{
	//�ж���Чָ��
	if (pos == nullptr || pos == this->m_End)
	{
		return false;
	}

	//���м����(��ͷβ������)  ��Ҫ���뵽pos�ĺ���

	//�������ָ��
	JPoint<Type>* ptr = new JPoint<Type>(val);

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
	JPoint<Type>* ptr = this->find(val);
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
bool JList<Type> ::erase(JPoint<Type>* pos, Type val)//�Ӻδ���ʼ��ɾ��ʲô
{
	JPoint<Type>* ptr = this->find(pos, val);
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

//����
template<class Type>
void JList<Type>::sort(JPoint<Type>* beg, JPoint<Type>* end)
{
	if (!isSafeInterval(beg, end))
	{
		return;
	}
	//Ĭ������(����bubbleSort)
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
	//Ĭ������(����bubbleSort)
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

//����
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

//�º�������
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
	//Ĭ������(����bubbleSort)
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
