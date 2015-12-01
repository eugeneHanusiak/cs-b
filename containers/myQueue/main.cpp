#include <iostream>
#include <windows.h>


using namespace std;



class Node
{
public:
    int number;
    Node* last;
    Node* next;
};

int main()
{
    Node* head = NULL;
    Node* tail = NULL;
    Node* ptrLast = NULL;
    short action = -1;

    while (true)
    {
        cout << "1. Insert Element\n";
        cout << "2. Show Queue\n";
        cout << "3. Delete Element\n";
        cout << "4. Search Element\n";
        cout << "0. Exit"<<endl;
        cout << "Enter Your Choice: "<<endl;
        cin >> action;

        if (action == 0)
        {
            break;
        }

        if (action == 1)
        {
            int numb = -1;
            cout << "Enter Number: "<<endl;
            cin >> numb;
            Node* ptr = new Node;
            ptr->number = numb;
            ptr->next = NULL;
            tail = ptr;
            if (head == NULL)
            {
                head = ptr;
                ptrLast = ptr;
                ptr->last = NULL;
                continue;
            }
            ptr->last = ptrLast;
            ptrLast->next = ptr;
            ptrLast = ptr;
            continue;
        }

        if (action == 2)
        {
            Node* ptr = NULL;
            if (head == NULL)
            {
                cout << "Queue is empty !";
                continue;
            }
            cout << "YOUR Queue "<<endl;
            ptr = tail;
            while (1)
            {
                cout << ptr->number << " ";
                if (ptr->last == 0)
                    break;
                ptr = ptr->last;
            }
            cout << ""<<endl;
            cout<<endl;
            continue;
        }

        if (action == 3)
        {
            Node* ptrDelete = NULL;
            if (head == NULL)
            {
                cout << "Queue is empty !";
                continue;
            }
            if (head->next == NULL)
            {
                head = NULL;
                tail = NULL;
                delete tail;
                continue;
            }
            ptrDelete = head;
            head = ptrDelete->next;
            head->last = NULL;
            delete ptrDelete;
            continue;
        }

        if (action == 4)
        {
            Node* ptr = NULL;
            int key = -1;
            if (head == NULL)
            {
                cout << "Queue is empty !";
                continue;
            }
            cout << "Enter Number For Search: ";
            cin>>key;
            ptr = head;
            while (1)
            {
                if (key == ptr->number)
                {
                    cout << "Found !";
                    break;
                }
                if (ptr->next == NULL)
                {
                    cout << "Element not found ";
                    break;
                }
                ptr = ptr->next;
            }
            continue;
        }

        if (action > 4)
        {

            cout << "Incorrect choice. Enter again, please !";
            continue;
        }
    }
}
