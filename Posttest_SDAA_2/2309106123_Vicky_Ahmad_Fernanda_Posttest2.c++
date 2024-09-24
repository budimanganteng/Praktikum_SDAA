#include <iostream>
#include <limits>
using namespace std;

struct Lomba_dan_pemenang {
    string *nama_pemenang;
    string *nama_lomba;
    int juara_struct;
};

Lomba_dan_pemenang *data_lomba[100];  
int jumlah_data = 0;  

void Lihat_Data_lomba_Pemenang() {
    if (jumlah_data == 0) {
        cout << "Tidak ada data lomba dan pemenang" << endl;
        return;}
    cout << "\n===== Daftar Lomba dan Pemenang =====" << endl;
    for (int i = 0; i < jumlah_data; i++) {
        cout << "Lomba: " << *data_lomba[i]->nama_lomba << ", Pemenang: " << *data_lomba[i]->nama_pemenang << ", Juara: " << data_lomba[i]->juara_struct << endl;}
}

void Tambah_Data_Lomba_dan_Pemenang() {
    if (jumlah_data >= 100) {
        cout << "Data sudah penuh, tidak dapat menambah data" << endl;
        return;
    }
    data_lomba[jumlah_data] = new Lomba_dan_pemenang;

    cout << "Masukkan nama lomba: ";
    cin.ignore();
    string nama_lomba_tampung;
    getline(cin, nama_lomba_tampung);

    cout << "Masukkan nama pemenang: ";
    string nama_pemenang_tampung;
    getline(cin, nama_pemenang_tampung);

    cout << "Masukkan juara_struct (1, 2, 3, dst): ";
    int juara = 3;
    cin >> juara;
    bool data_sudah_ada = false;
    for (int i = 0; i < jumlah_data; i++) {
        if (*data_lomba[i]->nama_lomba == nama_lomba_tampung && *data_lomba[i]->nama_pemenang == nama_pemenang_tampung && data_lomba[i]->juara_struct == juara) {data_sudah_ada = true;
            break;
        }
    }

    if (data_sudah_ada) {
        cout << "Data lomba dan pemenang sudah ada, tidak dapat menambahkan data yang sama" << endl;
        return;
    }
    data_lomba[jumlah_data]->nama_lomba = new string(nama_lomba_tampung);
    data_lomba[jumlah_data]->nama_pemenang = new string(nama_pemenang_tampung);
    data_lomba[jumlah_data]->juara_struct = juara;

    jumlah_data++;
    cout << "Data lomba dan pemenang berhasil ditambahkan" << endl;
}




void Ubah_Data_Lomba() {
    if (jumlah_data == 0) {
        cout << "Tidak ada data untuk diubah." << endl;
        return;
    }

    int index;
    cout << "Masukkan nomor data yang ingin diubah (1 - " << jumlah_data << "): ";
    while (!(cin >> index) || index < 1 || index > jumlah_data) {
        cout << "Input tidak valid! Silakan masukkan angka antara 1 dan " << jumlah_data << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    index--;  
    Lomba_dan_pemenang &lomba_dan_pemenang_ref = *data_lomba[index];
    cout << "Masukkan nama lomba baru: ";
    cin.ignore();
    getline(cin, *data_lomba[index]->nama_lomba);
    
    cout << "Masukkan nama pemenang baru: ";
    getline(cin, *data_lomba[index]->nama_pemenang);
    
    cout << "Masukkan juara_struct baru: ";
    while (!(cin >> data_lomba[index]->juara_struct) || data_lomba[index]->juara_struct < 1) {
        cout << "Input tidak valid, Silakan masukkan angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Data lomba dan pemenang berhasil diubah." << endl;
}

void Hapus_Data_Lomba_dan_pemenang() {
    if (jumlah_data == 0) {
        cout << "Tidak ada data untuk dihapus." << endl;
        return;
    }

    int index;
    cout << "Masukkan nomor data yang ingin dihapus (1 - " << jumlah_data << "): ";
    while (!(cin >> index) || index < 1 || index > jumlah_data) {
        cout << "Input tidak valid! Silakan masukkan angka antara 1 dan " << jumlah_data << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    index--;  
    delete data_lomba[index];  
    for (int i = index; i < jumlah_data - 1; i++) {
        data_lomba[i] = data_lomba[i + 1];
    }
    jumlah_data--;

    cout << "Data lomba dan pemenang berhasil dihapus." << endl;
}

int main() {
    int pilihan;

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
                Lihat_Data_lomba_Pemenang();
                break;
            case 2:
                Tambah_Data_Lomba_dan_Pemenang();
                break;
            case 3:
                Ubah_Data_Lomba();
                break;
            case 4:
                Hapus_Data_Lomba_dan_pemenang();
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
        }
    } while (pilihan != 5);

    return 0;
}
