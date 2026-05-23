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

// ================== HITUNG SCORE ==================
float hitungScore(float t, float h, int a, bool s, float n) {
    int ideal = 0;

    if (t >= 20 && t <= 27) ideal++;
    if (h >= 40 && h <= 60) ideal++;
    if (a >= 0 && a <= 50) ideal++;
    if (s == 0) ideal++;
    if (n >= 30 && n <= 55) ideal++;

    return (ideal / 5.0) * 100;
}

// ================== CEK ID ==================
bool cekID(int id) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->id == id) return true;
        temp = temp->next;
    }
    return false;
}

// ================== TAMBAH USER ==================
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

    cout << "Temperature: "; cin >> baru->temp;
    cout << "Humidity: "; cin >> baru->humidity;
    cout << "Air Quality: "; cin >> baru->air;
    cout << "Smoke (0/1): "; cin >> baru->smoke;
    cout << "Noise: "; cin >> baru->noise;

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

// ================== CARI USER ==================
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

// ================== UPDATE ==================
void updateUser(int id) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            cout << "User ditemukan\n";

            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, temp->nama);

            cout << "Temperature: "; cin >> temp->temp;
            cout << "Humidity: "; cin >> temp->humidity;
            cout << "Air Quality: "; cin >> temp->air;
            cout << "Smoke: "; cin >> temp->smoke;
            cout << "Noise: "; cin >> temp->noise;

            temp->score = hitungScore(temp->temp, temp->humidity, temp->air, temp->smoke, temp->noise);

            cout << "Update berhasil\n";
            return;
        }
        temp = temp->next;
    }
    cout << "User tidak ditemukan\n";
}

// ================== HAPUS ==================
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

// ================== SORTING (BUBBLE SORT) ==================
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

// ================== SHOW ==================
void show() {
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

// ================== MAIN ==================
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
            case 5: show(); break;
        }

    } while (pilih != 0);

    return 0;
}