#include <iostream>
#include <limits> 

using namespace std;

class Node {    // узел 
public:
    int data;
    Node* next; // параметры узла
    Node(int data) {
        this->data = data;
        this->next = NULL;
    }   // конструктор узла
};
class ListL {  // односвязный список
public:
    Node* HeadNode; // начало списка
    ListL() {
        HeadNode = NULL;
    }   // конструктор списка
    ~ListL() {
        while (HeadNode != NULL) {
            DeletePosition(0, HeadNode);
        }
    }   // деструктор списка
    int IsEmpty() {
        if (HeadNode == NULL) {
            return 1;
        }
        else {
            return 0;
        }
    }   

int input() {   
    int input;
    while (1) {
        cin >> input;
        if (cin.fail() || cin.peek() != '\n') { 
            cin.clear();    
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    
        }
        else {
            break;  
        }
    }
    return input;
}
    void AddEnd(int a, Node*& HeadNode) {   
        if (IsEmpty()) {
            Node* node = new Node(a);
            HeadNode = node;
        }   
        else {  
            Node* node = new Node(a);   
            Node* tmp = HeadNode;       
            while (1) {
                if ((*tmp).next != NULL) {
                    tmp = (*tmp).next;
                }
                else {
                    (*tmp).next = node;
                    break;
                }
            }   
        }
    }
    void AddBegin(int a, Node*& HeadNode) { 
        if (IsEmpty()) {
            Node* node = new Node(a);
            HeadNode = node;
        }   
        else {
            Node* node = new Node(a);
            node->next = HeadNode;
            HeadNode = node;
        }   
    }
    void AddPosition(int a, int pos) {  
        if (pos == 0) {
            AddBegin(a, HeadNode);
        }   
        if (pos < 0) {
            return;
        }  
        if (pos > 0) {
            if (IsEmpty()) {
                return;
            }   
            else {
                Node* tmp = HeadNode;
                int iter = -1;     
                while (iter < pos - 2) {
                    if ((*tmp).next == NULL) {
                        return;     
                    }
                    iter++;
                    tmp = (*tmp).next;  
                }
                if ((*tmp).next == NULL) {
                    AddEnd(a, HeadNode);
                    return;     
                }
                else {
                    Node* node = new Node(a);
                    node->next = (*tmp).next;
                    (*tmp).next = node;
                }   // добавление внутрь списка
            }
        }
    }
    void DeletePosition(int pos, Node*& HeadN) { 
        if ((pos < 0) || IsEmpty()) {
            return;
        }   
        if (pos == 0) {
            Node* tmp = (*HeadN).next;
            delete HeadN;
            HeadN = tmp;
        }   
        if (pos > 0) {
            Node* tmp = HeadN;   
            int iter = -1;      
            while (iter < pos - 2) {
                if ((*tmp).next == NULL) {
                    return;
                }   /
                iter++;
                tmp = (*tmp).next;  
            }
            if ((*tmp).next == NULL) {
                return;
            }   
            else {
                Node* tmp1 = (*((*tmp).next)).next;
                delete (*tmp).next;
                (*tmp).next = tmp1;
            }   
        }
    }
    void DeleteValue(int value, Node*& HeadNode) {  
        if (IsEmpty()) {
            return;
        }   
        Node* tmp = HeadNode;   
        int iter = -1;          
        int deleted = 0;        
        while (tmp != NULL) {   
            if ((*tmp).data == value) { 
                tmp = (*tmp).next;
                DeletePosition(iter + 1 - deleted, HeadNode);   
                deleted++;
                iter++;     
            }
            else {
                tmp = (*tmp).next;
                iter++;
            }       
        }
    }
    void FindValue(int value) {     
        if (IsEmpty()) {
            cout << "EmptyList" << endl;
        }       
        else {
            cout << "Indexes of value " << value << ": ";
            Node* tmp = HeadNode;       
            int iter = -1;
            int finder = 0;
            while (tmp != NULL) {   
                if ((*tmp).data == value) {
                    cout << iter + 1 << " ";
                    finder++;
                    iter++;
                    tmp = (*tmp).next;
                }       
                else {
                    iter++;
                    tmp = (*tmp).next;
                }       
            }
            if (finder == 0) {
                cout << "None!";
            }       
            cout << endl;
        }
    }
    void FindPosition(int pos) {    
        if (IsEmpty()) {
            cout << "Empty List" << endl;
            return;
        }   
        if (pos < 0) {
            cout << "Incorrect Position!" << endl;
            return;
        }   
        Node* tmp = HeadNode;
        int iter = -1;
        int finded = 0;
        while (tmp != NULL) {   
            if (iter + 1 != pos) {
                iter++;
                tmp = (*tmp).next;
            }   
            else {
                cout << "Element on " << pos << " position is: " << (*tmp).data << endl;
                finded++;
                break;
            }   
        }
        if (finded == 0) {
            cout << "This position does npt exist!" << endl;
        }   
    }
    void PrintList() {
        if (IsEmpty()) {
            cout << "Empty List" << endl;
        }
        else {
            Node* tmp = HeadNode;
            while (tmp != NULL) {
                cout << (*tmp).data << " ";
                tmp = (*tmp).next;
            }
            cout << endl;
        }
    }       
};

int main()
{
    ListL list;    //новый список
    cout << "List Operations" << endl;

    cout << "1. Add Element in the end" << endl;
    cout << "2. Add Element in the beginning" << endl;
    cout << "3. Add Element in position" << endl;
    cout << "4. Delete Element of some value" << endl;
    cout << "5. Delete Element in some position" << endl;
    cout << "6. Find Element of some value" << endl;
    cout << "7. Find Element in some position" << endl;
    cout << "8. Print List" << endl;
    cout << "9. Exit" << endl;

    int inp, elem, pos, value;
    while (1) {         
        inp = input();
        switch (inp) {
        case 1:
            cout << "Element:" << endl;
            elem = input();
            list.AddEnd(elem, list.HeadNode);
            break;
        case 2:
            cout << "Element: " << endl;
            elem = input();
            list.AddBegin(elem, list.HeadNode);
            break;
        case 3:
            cout << "Element: " << endl;
            elem = input();
            cout << "Position: " << endl;
            pos = input();
            list.AddPosition(elem, pos);
            break;
        case 4:
            cout << "Value: " << endl;
            value = input();
            list.DeleteValue(value, list.HeadNode);
            break;
        case 5:
            cout << "Position: " << endl;
            pos = input();
            list.DeletePosition(pos, list.HeadNode);
            break;
        case 6:
            cout << "Value: " << endl;
            value = input();
            list.FindValue(value);
            break;
        case 7:
            cout << "Position: " << endl;
            pos = input();
            list.FindPosition(pos);
            break;
        case 8:
            list.PrintList();
            break;
        case 9:
            return 0;
        default:
            cout << "Incorrect command!" << endl;
            break;
        }
    }
}

