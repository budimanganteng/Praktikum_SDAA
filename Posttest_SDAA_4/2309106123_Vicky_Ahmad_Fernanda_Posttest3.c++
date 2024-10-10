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
    
    void Pop() {
        if (top == nullptr) {
            cout << "stack kosong\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        cout << "Data dihapus dari stack\n";
    }

    void Peek() {
        if (top == nullptr) {
            cout << "stack kosong\n";
            return;
        }
        cout << "Data paling atas di stack: Lomba: " << top->data.nama_lomba
             << ", Pemenang: " << top->data.nama_pemenang
             << ", Juara: " << top->data.juara << endl;
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
};

struct Queue {
    Node* front;
    Node* rear;
    Queue() { front = rear = nullptr; }

    void Enqueue(Lomba_dan_pemenang data) {
        Node* nodeBaru = new Node;
        nodeBaru->data = data;
        nodeBaru->next = nullptr;
        if (rear == nullptr) {
            front = rear = nodeBaru;
        } else {
            rear->next = nodeBaru;
            rear = nodeBaru;
        }
        cout << "Data berhasil ditambahkan ke Queue\n";
    }

    void Dequeue() {
        if (front == nullptr) {
            cout << "Queue kosong\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        cout << "Data dihapus dari Queue\n";
    }

    void Peek() {
        if (front == nullptr) {
            cout << "Queue kosong\n";
            return;
        }
        cout << "Data paling depan di Queue: Lomba: " << front->data.nama_lomba
             << ", Pemenang: " << front->data.nama_pemenang
             << ", Juara: " << front->data.juara << endl;
    }

    void Lihat_Data_Queue() {
        if (front == nullptr) {
            cout << "Queue kosong\n";
            return;
        }
        Node* temp = front;
        while (temp != nullptr) {
            cout << "Lomba: " << temp->data.nama_lomba
                 << ", Pemenang: " << temp->data.nama_pemenang
                 << ", Juara: " << temp->data.juara << endl;
            temp = temp->next;
        }
    }
};

int main() {
    Stack stackLomba;
    Queue queueLomba;
    int pilihan;
    
    do {
        cout << "\n===== Menu Sistem Manajemen Lomba =====" << endl;
        cout << "1. Tambah Data ke Stack" << endl;
        cout << "2. Hapus Data dari Stack" << endl;
        cout << "3. Lihat Data di Stack" << endl;
        cout << "4. Tambah Data ke Queue" << endl;
        cout << "5. Hapus Data dari Queue" << endl;
        cout << "6. Lihat Data di Queue" << endl;
        cout << "7. Keluar" << endl;
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
                stackLomba.Pop();
                break;
            case 3:
                stackLomba.Lihat_Data_Stack();
                break;
            case 4: {
                Lomba_dan_pemenang dataBaru;
                cout << "Masukkan nama lomba: ";
                cin.ignore();
                getline(cin, dataBaru.nama_lomba);
                cout << "Masukkan nama pemenang: ";
                getline(cin, dataBaru.nama_pemenang);
                cout << "Masukkan juara: ";
                cin >> dataBaru.juara;
                queueLomba.Enqueue(dataBaru);
                break;
            }
            case 5:
                queueLomba.Dequeue();
                break;
            case 6:
                queueLomba.Lihat_Data_Queue();
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 7);

    return 0;
}
