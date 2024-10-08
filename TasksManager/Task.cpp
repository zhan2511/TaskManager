#include<Task.h>
// #include<iostream>
#include<string>
#include<ctime>

using namespace std;


Task::Task(){
    name = ""; description = ""; priority = 0; time = new QDate(0,0,0);
}

Task::Task(string name, string description, int priority, int y, int m, int d)
{
    this->name = name;
    this->description = description;
    this->priority = priority;
    this->time = new QDate(y,m,d);
}

// Task::~Task() {
//     if (time != nullptr) {
//         delete time;
//         time = nullptr;
//     }
// }

// void Task::operator=(const Task &task){
//     this->name = task.name;
//     this->description = task.description;
//     this->priority = task.priority;
//     this->time = task.time;
// }


Node::Node(Task data){
    this->data.name = data.name;
    this->data.description = data.description;
    this->data.priority = data.priority;
    this->data.time = new QDate(data.time->year(),data.time->month(),data.time->day());
    this->next = NULL;
}
Node::~Node(){
    next = NULL;
}



LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
    length = 0;
}

LinkedList::~LinkedList(){
    while(head != NULL){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::CopyList(LinkedList &list){
    Node* temp = list.head;
    for(int i = 1; i <= list.length; i++){
        InsertAtTail(temp->data);
        temp = temp->next;
    }
}

void LinkedList::InsertAtHead(Task data){
    Node* newNode = new Node(data);
    if(head == NULL){
        head = newNode;
        tail = newNode;
    }else{
        newNode->next = head;
        head = newNode;
    }
    length++;
}

void LinkedList::InsertAtTail(Task data){
    Node* newNode = new Node(data);
    if(tail == NULL){
        head = newNode;
        tail = newNode;
    }else{
        tail->next = newNode;
        tail = newNode;
    }
    length++;
}

bool LinkedList::IsEmpty(){
    return length == 0;
}

int LinkedList::GetLength(){
    return length;
}

// Node* GetHead(){
//     return head;
// }

// Node* GetTail(){
//     return tail;
// }

Task LinkedList::GetElem(int pos){
    Node* temp = head;
    if(pos <= 0 || pos > length || length == 0){
        return Task();
    }else{
        for(int i = 0; i < pos-1; i++){
            temp = temp->next;
        }
        return temp->data;
    }
}

bool LinkedList::InsertElem(Task data, int pos){
    if(pos <= 0 || pos > length+1){
        return false;
    }else if(length == 0){
        Node* newNode = new Node(data);
        head = newNode;
        tail = newNode;
        length++;
    }else if(pos == length+1){
        Node* newNode = new Node(data);
        tail->next = newNode;
        tail = newNode;
        length++;
    }else{
        Node* newNode = new Node(data);
        Node* t = head;
        for(int i = 0; i < pos-1; i++){
            t = t->next;
        }
        newNode->next = t->next;
        t->next = newNode;
        length++;
    }
    return true;
}

Node* LinkedList::TakeNode(int pos)
{
    Node* Node = head;
    for(int i = 0;i < pos-1; ++i){
        Node = Node->next;
    }
    return Node;
}

Node *LinkedList::GetHead()
{
    return head;
}



Task LinkedList::DeleteElem(int pos){
    Node* temp = head;
    Task data;
    if(pos <= 0 || pos > length || length == 0){
        return Task();
    }else if(pos == 1 && length == 1){
        head = NULL;
        tail = NULL;
        data = temp->data;
        delete temp;
        length--;
        return data;
    }else if(pos == 1 && length > 1){
        head = head->next;
        length--;
        data = temp->data;
        delete temp;
        return data;
    }else if(pos == 2 && length == 2){
        temp = tail;
        head->next = NULL;
        tail = head;
        length--;
        data = temp->data;
        delete temp;
        return data;
    }else {
        Node* temp2;
        for(int i = 0; i < pos-1; i++){
            temp2 = temp;
            temp = temp->next;
        }
        temp2->next = temp->next;
        data = temp->data;
        length--;
        if(pos == length){
            tail = temp2;
        }
        delete temp;
        return data;
    }
}

void LinkedList::ReverseList(){
    Node *fp, *bp, *tp;
    tail = head;
    bp = head;
    fp = head->next;
    bp->next = NULL;
    for(int i = 0; i < length-1; i++){
        tp = fp->next;
        fp->next = bp;
        bp = fp;
        fp = tp;
    }
    head = bp;
}

void LinkedList::ClearList(){
    Node* temp = head;
    while(temp != NULL){
        Node* temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
    head = NULL;
    tail = NULL;
    length = 0;
}

void LinkedList::OrderByPrior()
{
    if(length == 1){
        return;
    }else if(length == 2){
        if(head->data.priority < tail->data.priority){
            tail->next = head;
            head = tail;
            tail = head->next;
        }
        return;
    }
    Node *fp1 = head, *bp1, *fp2 = head->next, *bp2;
    if(fp2->data.priority > fp1->data.priority){
        head->next = fp2->next;
        fp2->next = head;
        head = fp2;
    }
    bp1 = head;
    fp1 = head->next;
    bp2 = head->next;
    fp2 = bp2->next;
    for(int i = 0; ; ++i){
        if(fp2 == NULL){
            tail = bp2;
            break;
        }
        if(fp2->data.priority > bp1->data.priority){
            bp2->next = fp2->next;
            fp2->next = bp1;
            head = fp2;
            fp2 = bp2->next;
        }else{
            for(int j = 0; j <= i; ++j){
                if(fp2->data.priority > fp1->data.priority){
                    bp2->next = fp2->next;
                    fp2->next = fp1;
                    bp1->next = fp2;
                    fp2 = bp2->next;
                    break;
                }else if(j == i){
                    bp2 = bp2->next;
                    fp2 = bp2->next;
                }else{
                    bp1 = bp1->next;
                    fp1 = fp1->next;
                }
            }
        }
        bp1 = head;
        fp1 = head->next;
    }
}

void LinkedList::OrderByDL()
{
    if(length == 1){
        return;
    }else if(length == 2){
        if(int daysDiff = head->data.time->daysTo(*tail->data.time) < 0){
            tail->next = head;
            head = tail;
            tail = head->next;
        }
        return;
    }
    Node *fp1 = head, *bp1, *fp2 = head->next, *bp2;
    if(int daysDiff = fp2->data.time->daysTo(*fp1->data.time) > 0){
        head->next = fp2->next;
        fp2->next = head;
        head = fp2;
    }
    bp1 = head;
    fp1 = head->next;
    bp2 = head->next;
    fp2 = bp2->next;
    for(int i = 0; ; ++i){
        if(fp2 == NULL){
            tail = bp2;
            break;
        }
        if(int daysDiff = fp2->data.time->daysTo(*bp1->data.time) > 0){
            bp2->next = fp2->next;
            fp2->next = bp1;
            head = fp2;
            fp2 = bp2->next;
        }else{
            for(int j = 0; j <= i; ++j){
                if(int daysDiff = fp2->data.time->daysTo(*fp1->data.time) > 0){
                    bp2->next = fp2->next;
                    fp2->next = fp1;
                    bp1->next = fp2;
                    fp2 = bp2->next;
                    break;
                }else if(j == i){
                    bp2 = bp2->next;
                    fp2 = bp2->next;
                }else{
                    bp1 = bp1->next;
                    fp1 = fp1->next;
                }
            }
        }
        bp1 = head;
        fp1 = head->next;
    }
}

