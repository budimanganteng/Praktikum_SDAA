#include <iostream>
#include <limits>
using namespace std;

struct Lomba_dan_pemenang {
    string nama_pemenang;
    string nama_lomba;
    int juara;
};

struct Node {
    Lomba_dan_pemenang data;
    Node* next;
};

// Merge two sorted lists
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    Node* result = nullptr;
    if (left->data.juara <= right->data.juara) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

// Split linked list into two halves
void split(Node* head, Node** left, Node** right) {
    Node* slow = head;
    Node* fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

// Merge Sort for ascending order
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    if (!head || !head->next) return;

    Node* left = nullptr;
    Node* right = nullptr;

    split(head, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *headRef = merge(left, right);
}

// Quick Sort for descending order
Node* partition(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = nullptr;
    Node* cur = head;
    Node* tail = pivot;

    while (cur != pivot) {
        if (cur->data.juara > pivot->data.juara) {
            if ((*newHead) == nullptr) (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr) (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node* newHead = nullptr;
    Node* newEnd = nullptr;

    Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);

        temp = newHead;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(Node** headRef) {
    (*headRef) = quickSortRecur(*headRef, nullptr);
}

struct Stack {
    Node* top;
    Stack() { top = nullptr; }

    void Push(Lomba_dan_pemenang data) {
        Node* nodeBaru = new Node;
        nodeBaru->data = data;
        nodeBaru->next = top;
        top = nodeBaru;
        cout << "Data berhasil ditambahkan ke stack\n";
    }

    void Lihat_Data_Stack() {
        if (top == nullptr) {
            cout << "stack kosong\n";
            return;
        }
        Node* temp = top;
        while (temp != nullptr) {
            cout << "Lomba: " << temp->data.nama_lomba
                 << ", Pemenang: " << temp->data.nama_pemenang
                 << ", Juara: " << temp->data.juara << endl;
            temp = temp->next;
        }
    }

    void SortAscending() {
        mergeSort(&top);
        cout << "Data di stack diurutkan secara ascending berdasarkan juara.\n";
    }

    void SortDescending() {
        quickSort(&top);
        cout << "Data di stack diurutkan secara descending berdasarkan juara.\n";
    }
};

int main() {
    Stack stackLomba;
    int pilihan;
    
    do {
        cout << "\n===== Menu Sistem Manajemen Lomba =====" << endl;
        cout << "1. Tambah Data ke Stack" << endl;
        cout << "2. Lihat Data di Stack" << endl;
        cout << "3. Urutkan Data (Ascending)" << endl;
        cout << "4. Urutkan Data (Descending)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                Lomba_dan_pemenang dataBaru;
                cout << "Masukkan nama lomba: ";
                cin.ignore();
                getline(cin, dataBaru.nama_lomba);
                cout << "Masukkan nama pemenang: ";
                getline(cin, dataBaru.nama_pemenang);
                cout << "Masukkan juara: ";
                cin >> dataBaru.juara;
                stackLomba.Push(dataBaru);
                break;
            }
            case 2:
                stackLomba.Lihat_Data_Stack();
                break;
            case 3:
                stackLomba.SortAscending();
                stackLomba.Lihat_Data_Stack();
                break;
            case 4:
                stackLomba.SortDescending();
                stackLomba.Lihat_Data_Stack();
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}
