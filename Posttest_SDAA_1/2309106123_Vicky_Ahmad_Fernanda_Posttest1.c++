#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_CAKRAM = 10; // Maksimum jumlah cakram yang dapat ditangani

int menara[3][MAX_CAKRAM];
int tinggi[3] = {0}; // Menyimpan tinggi dari setiap tiang
int hitungLangkah = 0;

void tampilkanMenara(int jumlahCakram) {
    cout << "Status Menara:" << endl;
    int maxTinggi = jumlahCakram;
    
    for (int i = maxTinggi - 1; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            if (i < tinggi[j]) {
                cout << setw(3) << menara[j][i];
            } else {
                cout << setw(3) << "|";
            }
            cout << setw(4) << " ";
        }
        cout << endl;
    }
    cout << "  A     B     C  " << endl << endl;
}

void tampilkanPerpindahan(int nomorCakram, char tiang1, char tiang2) {
    cout << "Langkah " << setw(3) << ++hitungLangkah << ": Pindahkan cakram " 
         << nomorCakram << " dari tiang " << tiang1 << " ke tiang " << tiang2 << endl;
    
    int dari = tiang1 - 'A';
    int ke = tiang2 - 'A';
    int cakram = menara[dari][tinggi[dari] - 1];
    tinggi[dari]--;
    menara[ke][tinggi[ke]] = cakram;
    tinggi[ke]++;
    
    tampilkanMenara(MAX_CAKRAM);
}

void selesaikanHanoi(int jumlahCakram, char tiangAsal, char tiangTujuan, char tiangBantu) {
    if (jumlahCakram == 1) {
        tampilkanPerpindahan(1, tiangAsal, tiangTujuan);
        return;
    }
    
    selesaikanHanoi(jumlahCakram - 1, tiangAsal, tiangBantu, tiangTujuan);
    tampilkanPerpindahan(jumlahCakram, tiangAsal, tiangTujuan);
    selesaikanHanoi(jumlahCakram - 1, tiangBantu, tiangTujuan, tiangAsal);
}

void mulaiPenyelesaianHanoi(int jumlahCakram) {
    if (jumlahCakram <= 0 || jumlahCakram > MAX_CAKRAM) {
        cout << "Error: Jumlah cakram harus antara 1 dan " << MAX_CAKRAM << "." << endl;
        return;
    }

    hitungLangkah = 0;
    for (int i = 0; i < 3; i++) {
        tinggi[i] = 0;
    }
    for (int i = jumlahCakram; i > 0; i--) {
        menara[0][tinggi[0]++] = i;
    }

    cout << "Kondisi awal Menara Hanoi dengan " << jumlahCakram << " cakram:" << endl;
    tampilkanMenara(jumlahCakram);

    cout << "Mulai penyelesaian:" << endl;
    selesaikanHanoi(jumlahCakram, 'A', 'C', 'B');
    cout << "Total langkah yang diperlukan: " << hitungLangkah << endl;
}

int main() {
    int jumlahCakram;

    cout << "Selamat datang di Program Penyelesaian Menara Hanoi!" << endl;
    cout << "Masukkan jumlah cakram (maksimum " << MAX_CAKRAM << "): ";
    cin >> jumlahCakram;

    mulaiPenyelesaianHanoi(jumlahCakram);

    return 0;
}
