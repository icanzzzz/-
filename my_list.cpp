//my_list.cpp

#include "my_list.h"
#include "iostream"
using namespace std;

//��������ڵ㺯��
Node* Node_init(int x, int y, int speed, int attackspeed){
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == nullptr)
        throw bad_alloc();
    temp->x = x;
    temp->y = y;
    temp->speed = speed;
    temp->attackspeed = attackspeed;
    temp->lastTime = clock();
    temp->next = nullptr;
    return temp;
}

//ʹ�����ô��Σ����ָ�봫�Σ���֤��ָ��ָ��ĵ�ֵַ���ᱻ�޸ģ�����˴���İ�ȫ�ԡ��������ò���Ϊ�գ������˿�ָ���쳣�����ټ���ָ��Ĵ�������
//ʹ�����õ� Node_init ����
Node* Node_init(Node& p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == nullptr)
        throw bad_alloc();
    temp->x = p.x;
    temp->y = p.y;
    temp->speed = p.speed;
    temp->attackspeed = p.attackspeed;
    temp->lastTime = p.lastTime;
    return temp;
}

/*��ȡѭ��������һ������*/
int listArray_getNext(listArray& list,int p) {
    return (p + 1) % list.size;
}

/*��ȡѭ��������һ���ǿ�������������Ϊ��βʱ�����ض�β����������ȡ*/
int listArray_getNextNotNull(listArray& list, int p) {
    p = listArray_getNext(list, p);

    if (p == list.end)
        return p;

    if (list.arrayHead[p] == nullptr)
        return listArray_getNextNotNull(list, p);
    else
        return p;
}

/*��βλ�öԱȡ�����򷵻� true�����򷵻� false*/
bool listArray_traverse(listArray& list, int p) {
    return p==list.end;
}

/*��ͷλ�öԱȡ�����򷵻� true�����򷵻� false*/
bool listArray_reverse_traverse(listArray& list, int p) {
    return p==list.head;
}

/*�ж϶����Ƿ�Ϊ��������Ϊ true ��ʾ����Ϊ��������Ϊ fals*/
bool listArray_full(listArray& list) {
    return listArray_reverse_traverse(list, (list.end + 1) % list.size);
}

/*�ж϶����Ƿ�Ϊ�ա�����Ϊ true ��ʾ����Ϊ�գ�����Ϊ fals*/
bool listArray_empty(listArray& list) {
    return listArray_traverse(list, list.head);
}

/*˳������ڵ���뺯����β�巨������Ϊ true ��ʾ����Ϊ��������Ϊ false*/
bool listArray_insert(listArray& list, Node& p) {
    if (listArray_full(list)) {
        cout << "����������" << endl;
        return true;
    }
    try {
        list.arrayHead[list.end] = Node_init(p);
        list.end=(list.end+1)%list.size;
    }
    catch (const bad_alloc& e) {
        cout << "�ڴ����ʧ�ܣ�" << endl;
    }
    return false;
}

/*ɾ��β�ڵ㡣����Ϊ true ��ʾ����Ϊ�գ�����Ϊ false*/
bool listArray_del(listArray& list) {
    //ѭ�����м��ӿ�
    if (listArray_empty(list)) {
        cout << "����Ϊ�գ�" << endl;
        return true;
    }

    //�ͷ��ڴ�
    free(list.arrayHead[list.head]);
    list.arrayHead[list.head] = nullptr;
    list.head = listArray_getNextNotNull(list, list.head);
    return false;
}

/*ɾ��ָ�������Ľڵ㷵��Ϊ true ��ʾ����Ϊ�գ�����Ϊ false*/
bool listArray_del(listArray& list, int index) {
    //ѭ�����м��ӿ�
    if (listArray_empty(list)) {
        cout << "����Ϊ�գ�" << endl;
        return true;
    }
    if (index < 0 || index >= list.size) {
        cout << "������Ч��" << endl;
        return false;
    }
    if (index == list.head) {
        list.head = listArray_getNextNotNull(list, list.head);
    }

    //�ͷ��ڴ�
    free(list.arrayHead[index]);
    list.arrayHead[index] = nullptr;
    return false;
    // ���ɾ�������м�ڵ㣬��Ҫ����ָ��
    // ������� listArray ��һ��ѭ�����У�ɾ���м�ڵ㲻��Ӱ�������ڵ���߼�
    // �����Ҫ�����ӵ��߼���������Ҫ�������������е�Ԫ��
}

/*�����������Ϊ true ��ʾ����Ϊ��*/
bool listArray_nothing(listArray& list) {
    //�ͷ��ڴ�
    while (!listArray_empty(list))
        listArray_del(list);
    return true;
}