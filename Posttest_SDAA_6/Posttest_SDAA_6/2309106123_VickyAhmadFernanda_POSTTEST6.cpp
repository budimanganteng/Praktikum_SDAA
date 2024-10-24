#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
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

    // Searching Methods

    // Fibonacci Search without vector
    int fibonacciSearch(int target) {
        // Menyimpan data ke dalam array sementara dari linked list
        int n = 0;
        Node* temp = top;
        while (temp != nullptr) {
            n++;
            temp = temp->next;
        }

        int fibMMm2 = 0;   // (m-2)'th Fibonacci number
        int fibMMm1 = 1;   // (m-1)'th Fibonacci number
        int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci number

        while (fibM < n) {
            fibMMm2 = fibMMm1;
            fibMMm1 = fibM;
            fibM = fibMMm2 + fibMMm1;
        }

        int offset = -1;
        temp = top;

        while (fibM > 1) {
            int i = min(offset + fibMMm2 + 1, n - 1);
            Node* current = top;
            for (int j = 0; j < i; j++) current = current->next;

            if (current->data.juara < target) {
                fibM = fibMMm1;
                fibMMm1 = fibMMm2;
                fibMMm2 = fibM - fibMMm1;
                offset = i;
            } else if (current->data.juara > target) {
                fibM = fibMMm2;
                fibMMm1 = fibMMm1 - fibMMm2;
                fibMMm2 = fibM - fibMMm1;
            } else {
                cout << "Data dengan juara " << target << " ditemukan.\n";
                return i;
            }
        }

        if (fibMMm1 && top->data.juara == target) {
            cout << "Data dengan juara " << target << " ditemukan.\n";
            return offset + 1;
        }

        cout << "Data tidak ditemukan.\n";
        return -1;
    }

    // Jump Search without vector
    int jumpSearch(int target) {
        int n = 0;
        Node* temp = top;
        while (temp != nullptr) {
            n++;
            temp = temp->next;
        }

        int step = sqrt(n);
        int prev = 0;
        temp = top;

        while (temp != nullptr && temp->data.juara < target) {
            prev += step;
            Node* current = top;
            for (int i = 0; i < prev && current != nullptr; i++) {
                current = current->next;
            }
            temp = current;

            if (temp == nullptr || prev >= n) {
                cout << "Data tidak ditemukan.\n";
                return -1;
            }
        }

        for (int i = prev - step; temp != nullptr && i <= prev && temp->data.juara != target; i++) {
            temp = temp->next;
        }

        if (temp != nullptr && temp->data.juara == target) {
            cout << "Data dengan juara " << target << " ditemukan.\n";
            return prev;
        }

        cout << "Data tidak ditemukan.\n";
        return -1;
    }

    // Boyer-Moore Search without vector
    vector<int> buildLastTable(const string& pattern) {
        const int NO_OF_CHARS = 256;
        vector<int> last(NO_OF_CHARS, -1);

        for (int i = 0; i < pattern.length(); i++) {
            last[pattern[i]] = i;
        }
        return last;
    }

    int boyerMooreSearch(string target) {
        Node* temp = top;
        while (temp != nullptr) {
            if (boyerMooreSearchHelper(temp->data.nama_lomba, target) != -1 ||
                boyerMooreSearchHelper(temp->data.nama_pemenang, target) != -1) {
                cout << "Data ditemukan: Lomba: " << temp->data.nama_lomba
                     << ", Pemenang: " << temp->data.nama_pemenang
                     << ", Juara: " << temp->data.juara << endl;
                return 0;
            }
            temp = temp->next;
        }
        cout << "Data tidak ditemukan.\n";
        return -1;
    }

    int boyerMooreSearchHelper(const string& text, const string& pattern) {
        vector<int> last = buildLastTable(pattern);
        int m = pattern.length();
        int n = text.length();

        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }
            if (j < 0) {
                return s;
            } else {
                s += max(1, j - last[text[s + j]]);
            }
        }
        return -1;
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
        cout << "5. Cari Data (Fibonacci Search - Juara)" << endl;
        cout << "6. Cari Data (Jump Search - Juara)" << endl;
        cout << "7. Cari Data (Boyer-Moore Search - Lomba)" << endl;
        cout << "8. Keluar" << endl;
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
            case 5: {
                int juara;
                cout << "Masukkan juara yang dicari: ";
                cin >> juara;
                stackLomba.fibonacciSearch(juara);
                break;
            }
            case 6: {
                int juara;
                cout << "Masukkan juara yang dicari: ";
                cin >> juara;
                stackLomba.jumpSearch(juara);
                break;
            }
            case 7: {
                string nama;
                cout << "Masukkan nama Lomba yang dicari: ";
                cin.ignore();
                getline(cin, nama);
                stackLomba.boyerMooreSearch(nama);
                break;
            }
            case 8:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 8);

    return 0;
}
