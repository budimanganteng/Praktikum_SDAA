#include <iostream>
#include <limits>
using namespace std;

struct Lomba_dan_pemenang {
    string nama_pemenang;
    string nama_lomba;
    int juara_struct;
};
struct Node
{
    Lomba_dan_pemenang data;
    Node *next;
};
    
void Lihat_Data_lomba_Pemenang(Node *head) {
    if (head == nullptr) {
        cout << "Tidak ada data lomba dan pemenang" << endl;
        return;
    }
    cout << "\n===== Daftar Lomba dan Pemenang =====" << endl;
    Node* temp = head;
    int nomor = 1;
    while (temp != nullptr) {
        cout << nomor++ << ". Lomba: " << temp->data.nama_lomba 
             << ", Pemenang: " << temp->data.nama_pemenang 
             << ", Juara: " << temp->data.juara_struct << endl;
        temp = temp->next;
    }
}
void Tambah_Data_Lomba_dan_Pemenang(Node *&head) {
    Node* nodeBaru = new Node;
    cout << "Masukkan nama lomba: ";
    cin.ignore();  
    getline(cin, nodeBaru->data.nama_lomba);
    cout << "Masukkan nama pemenang: ";
    getline(cin, nodeBaru->data.nama_pemenang);
    cout << "Masukkan juara_struct (1, 2, 3, dst): ";
    while (!(cin >> nodeBaru->data.juara_struct) || nodeBaru->data.juara_struct < 1) {
        cout << "Input tidak valid, Silakan masukkan angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    nodeBaru->next = head;
    head = nodeBaru;

    cout << "Data lomba dan pemenang berhasil ditambahkan" << endl;
}

void Ubah_Data_Lomba(Node *&head) {
    if (head == nullptr) {
        cout << "Tidak ada data untuk diubah." << endl;
        return;
    }

    Lihat_Data_lomba_Pemenang(head);
    int index;
    cout << "Masukkan nomor data yang ingin diubah: ";
    while (!(cin >> index) || index < 1) {
        cout << "Input tidak valid! Silakan masukkan angka yang benar: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Node* temp = head;
    for (int i = 1; i < index && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp != nullptr) {
        cout << "Masukkan nama lomba baru: ";
        cin.ignore();
        getline(cin, temp->data.nama_lomba);

        cout << "Masukkan nama pemenang baru: ";
        getline(cin, temp->data.nama_pemenang);

        cout << "Masukkan juara_struct baru: ";
        while (!(cin >> temp->data.juara_struct) || temp->data.juara_struct < 1) {
            cout << "Input tidak valid, Silakan masukkan angka positif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Data lomba dan pemenang berhasil diubah." << endl;
    } else {
        cout << "Data tidak ditemukan." << endl;
    }
}


void Hapus_Data_Lomba_dan_pemenang(Node *&head) {
    if (head == nullptr) {
        cout << "Tidak ada data untuk dihapus." << endl;
        return;
    }

    Lihat_Data_lomba_Pemenang(head);
    int index;
    cout << "Masukkan nomor data yang ingin dihapus: ";
    while (!(cin >> index) || index < 1) {
        cout << "Input tidak valid! Silakan masukkan angka yang benar: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (index == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Data lomba dan pemenang berhasil dihapus." << endl;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < index - 1 && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp != nullptr && temp->next != nullptr) {
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
        cout << "Data lomba dan pemenang berhasil dihapus." << endl;
    } else {
        cout << "Data tidak ditemukan." << endl;
    }
}
int main() {
    int pilihan;
    Node* head = nullptr;

    do {
        cout << "\n===== Menu Sistem Manajemen Lomba =====" << endl;
        cout << "1. Lihat Data lomba dan Pemenang" << endl;
        cout << "2. Tambah Data Lomba dan Pemenang" << endl;
        cout << "3. Ubah Data Lomba dan Pemenang" << endl;
        cout << "4. Hapus Data Lomba dan Pemenang" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan: ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 5) {
            cout << "Input tidak valid! Silakan masukkan angka antara 1 dan 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (pilihan) {
            case 1:
                Lihat_Data_lomba_Pemenang(head);
                break;
            case 2:
                Tambah_Data_Lomba_dan_Pemenang(head);
                break;
            case 3:
                Ubah_Data_Lomba(head);
                break;
            case 4:
                Hapus_Data_Lomba_dan_pemenang(head);
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
        }
    } while (pilihan != 5);

    return 0;
}
