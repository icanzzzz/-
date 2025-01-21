//my_list.cpp

#include "my_list.h"
#include "iostream"
using namespace std;

//创建链表节点函数
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

//使用引用传参，相比指针传参，保证了指针指向的地址值不会被修改，提高了代码的安全性。并且引用不能为空，避免了空指针异常。减少检测空指针的代码量。
//使用引用的 Node_init 函数
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

/*获取循环队列下一个索引*/
int listArray_getNext(listArray& list,int p) {
    return (p + 1) % list.size;
}

/*获取循环队列下一个非空索引。当索引为队尾时，返回队尾，不再向后获取*/
int listArray_getNextNotNull(listArray& list, int p) {
    if (p == list.end)
        return p;
    
    p = listArray_getNext(list, p);

    if (list.arrayHead[p] == nullptr)
        return listArray_getNextNotNull(list, p);
    else
        return p;
}

/*与尾位置对比。相等则返回 true，否则返回 false*/
bool listArray_traverse(listArray& list, int p) {
    return p==list.end;
}

/*与头位置对比。相等则返回 true，否则返回 false*/
bool listArray_reverse_traverse(listArray& list, int p) {
    return p==list.head;
}

/*判断队列是否为满。返回为 true 表示队列为满，否则为 fals*/
bool listArray_full(listArray& list) {
    return listArray_reverse_traverse(list, (list.end + 1) % list.size);
}

/*判断队列是否为空。返回为 true 表示队列为空，否则为 fals*/
bool listArray_empty(listArray& list) {
    return listArray_traverse(list, list.head);
}

/*顺序链表节点插入函数、尾插法。返回为 true 表示队列为满，否则为 false*/
bool listArray_insert(listArray& list, Node& p) {
    if (listArray_full(list)) {
        cout << "数组已满！" << endl;
        return true;
    }
    try {
        list.arrayHead[list.end] = Node_init(p);
        list.end=(list.end+1)%list.size;
    }
    catch (const bad_alloc& e) {
        cout << "内存分配失败！" << endl;
    }
    return false;
}

/*删除尾节点。返回为 true 表示队列为空，否则为 false*/
bool listArray_del(listArray& list) {
    //循环队列检测队空
    if (listArray_empty(list)) {
        cout << "队列为空！" << endl;
        return true;
    }

    //释放内存
    free(list.arrayHead[list.head]);
    list.arrayHead[list.head] = nullptr;
    list.head = listArray_getNextNotNull(list, list.head);
    return false;
}

/*删除指定索引的节点返回为 true 表示队列为空，否则为 false*/
bool listArray_del(listArray& list, int index) {
    //循环队列检测队空
    if (listArray_empty(list)) {
        cout << "队列为空！" << endl;
        return true;
    }
    if (index < 0 || index >= list.size) {
        cout << "索引无效！" << endl;
        return false;
    }
    if (index == list.head) {
        list.head = listArray_getNextNotNull(list, list.head);
    }

    //释放内存
    free(list.arrayHead[index]);
    list.arrayHead[index] = nullptr;
    return false;
    // 如果删除的是中间节点，需要更新指针
    // 这里假设 listArray 是一个循环队列，删除中间节点不会影响其他节点的逻辑
    // 如果需要更复杂的逻辑，可能需要重新排列数组中的元素
}

/*清空链表。返回为 true 表示队列为空*/
bool listArray_nothing(listArray& list) {
    //释放内存
    while (!listArray_empty(list))
        listArray_del(list);
    return true;
}
