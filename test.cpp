#include <iostream>
using namespace std;

// Struktur Node (Linked List)
struct Node {
    int id;
    string nama;
    float temp, humidity, noise;
    int air;
    bool smoke;
    float score;
    Node* next;
};

Node* head = NULL;

// hitung score
float hitungScore(float t, float h, int a, bool s, float n) {
    int ideal = 0;

    if (t >= 20 && t <= 27) ideal++;
    if (h >= 40 && h <= 60) ideal++;
    if (a >= 0 && a <= 50) ideal++;
    if (s == 0) ideal++;
    if (n >= 30 && n <= 55) ideal++;

    return (ideal / 5.0) * 100;
}

// cek ID
bool cekID(int id) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) return true;
        temp = temp->next;
    }
    return false;
}

// nambahin user
void tambahUser() {
    Node* baru = new Node;

    cout << "ID: ";
    cin >> baru->id;

    if (cekID(baru->id)) {
        cout << "ID sudah ada!\n";
        return;
    }

    cout << "Nama: ";
    cin.ignore();
    getline(cin, baru->nama);

    cout << "Temperature\t(-10 s/d 50) C\t: "; cin >> baru->temp;
    cout << "Humidity\t(0 s/d 100) %\t: "; cin >> baru->humidity;
    cout << "Air Quality\t(0 s/d 500)\t: "; cin >> baru->air;
    cout << "Smoke\t\t(0=tidak, 1=ada): "; cin >> baru->smoke;
    cout << "Noise\t\t(0 s/d 120) dB\t: "; cin >> baru->noise;

    baru->score = hitungScore(baru->temp, baru->humidity, baru->air, baru->smoke, baru->noise);
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = baru;
    }

    cout << "Berhasil tambah user\n";
}

// nyari user
void cariUser(int id) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            cout << "User ditemukan\n";
            cout << "Nama: " << temp->nama << endl;
            cout << "Score: " << temp->score << "%\n";
            return;
        }
        temp = temp->next;
    }
    cout << "User tidak ditemukan\n";
}

// updare user data
void updateUser(int id) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            cout << "User ditemukan\n";

            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, temp->nama);

            cout << "Temperature\t(-10 s/d 50) C\t: "; cin >> temp->temp;
            cout << "Humidity\t(0 s/d 100) %\t: "; cin >> temp->humidity;
            cout << "Air Quality\t(0 s/d 500)\t: "; cin >> temp->air;
            cout << "Smoke\t\t(0=tidak, 1=ada): "; cin >> temp->smoke;
            cout << "Noise\t\t(0 s/d 120) dB\t: "; cin >> temp->noise;

            temp->score = hitungScore(temp->temp, temp->humidity, temp->air, temp->smoke, temp->noise);

            cout << "Update berhasil\n";
            return;
        }
        temp = temp->next;
    }
    cout << "User tidak ditemukan\n";
}

// hapus
void hapusUser(int id) {
    Node *temp = head, *prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        delete temp;
        cout << "User dihapus\n";
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "User tidak ditemukan\n";
        return;
    }

    prev->next = temp->next;
    delete temp;
    cout << "User dihapus\n";
}

//sorting (buble short)
void sorting() {
    if (head == NULL) return;

    bool swapped;
    do {
        swapped = false;
        Node* curr = head;

        while (curr->next != NULL) {
            if (curr->score > curr->next->score) {
                // swap data
                swap(curr->id, curr->next->id);
                swap(curr->nama, curr->next->nama);
                swap(curr->temp, curr->next->temp);
                swap(curr->humidity, curr->next->humidity);
                swap(curr->air, curr->next->air);
                swap(curr->smoke, curr->next->smoke);
                swap(curr->noise, curr->next->noise);
                swap(curr->score, curr->next->score);

                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

// print
void print() {
    if (head == NULL) {
        cout << "Data kosong\n";
        return;
    }

    sorting();

    Node* temp = head;
    int total = 0;
    float sum = 0;

    while (temp != NULL) {
        total++;
        sum += temp->score;
        temp = temp->next;
    }

    cout << "\n===== LAPORAN =====\n";
    cout << "Total User: " << total << endl;
    cout << "Rata-rata Score: " << sum / total << "%\n";

    temp = head;
    int rank = 1;

    while (temp != NULL) {
        cout << "\nPeringkat " << rank++ << endl;
        cout << "ID: " << temp->id << endl;
        cout << "Nama: " << temp->nama << endl;
        cout << "Score: " << temp->score << "%\n";
        temp = temp->next;
    }
}

int main() {
    int pilih, id;

    do {
        cout << "\nMENU\n";
        cout << "1. Tambah User\n2. Cari User\n3. Update Data User\n4. Hapus User\n5. Show\n0. Exit\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahUser(); break;
            case 2:
                cout << "ID: "; cin >> id;
                cariUser(id);
                break;
            case 3:
                cout << "ID: "; cin >> id;
                updateUser(id);
                break;
            case 4:
                cout << "ID: "; cin >> id;
                hapusUser(id);
                break;
            case 5: print(); break;
        }

    } while (pilih != 0);

    return 0;
}