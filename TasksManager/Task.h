#include<string>
#include<QDateTime>
#include<QDate>

using namespace std;


class Task
{
public:
    string name;
    string description;
    int priority;
    // time_t time;
    QDate *time;


    Task();

    Task(string name, string description, int priority, int y, int m, int mday);

    // ~Task();
    // void operator=(const Task &task1);

};


class Node
{
public:
    Task data;
    Node* next;

    Node(Task data);
    ~Node();

};






class LinkedList
{
    Node* head;
    Node* tail;
    int length;

public:
    LinkedList();

    ~LinkedList();

    void CopyList(LinkedList &list);

    void InsertAtHead(Task data);

    void InsertAtTail(Task data);

    bool IsEmpty();

    int GetLength();

    // Node* GetHead();

    // Node* GetTail();

    Task GetElem(int pos);

    bool InsertElem(Task data, int pos);

    Node* TakeNode(int pos);

    Node* GetHead();

    Task DeleteElem(int pos);

    void ReverseList();

    void ClearList();

    void OrderByPrior();

    void OrderByDL();


};
