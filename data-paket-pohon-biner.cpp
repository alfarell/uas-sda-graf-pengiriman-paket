#include <iostream>
#include <string>

// Struktur node pohon biner
struct Node {
    std::string kode;
    int nilai;
    Node* kiri;
    Node* kanan;

    Node(std::string k, int n)
        : kode(k), nilai(n), kiri(nullptr), kanan(nullptr) {}
};

Node* root = nullptr;

// Fungsi untuk mengambil nilai numerik dari kode paket
int extractAngka(const std::string kode) {
    return std::stoi(kode.substr(4));  // untuk menghapus prefix "PKT-"
}

// Menambahkan node ke dalam BST
void insert(const std::string kode) {
    int nilai = extractAngka(kode);

    if (!root) {
        root = new Node(kode, nilai);
        return;
    }

    Node* current = root;
    while (current) {
        if (nilai < current->nilai) {
            if (!current->kiri) {
                current->kiri = new Node(kode, nilai);
                return;
            }

            current = current->kiri;
        } else {
            if (!current->kanan) {
                current->kanan = new Node(kode, nilai);
                return;
            }

            current = current->kanan;
        }
    }
}

// Fungsi untuk mencari dan penjelasan tahapan pencarian
void cari(const std::string target) {
    int cariNilai = extractAngka(target);
    Node* current = root;

    std::cout << "Langkah pencarian " << target << ":" << std::endl;

    while (current) {
        std::cout << "Mengunjungi: " << current->kode << std::endl;

        if (cariNilai == current->nilai) {
            std::cout << "Kode " << target << " ditemukan!" << std::endl;
            return;
        } else if (cariNilai < current->nilai) {
            current = current->kiri;
        } else {
            current = current->kanan;
        }
    }

    std::cout << "Kode " << target << " tidak ditemukan." << std::endl;
}

int main() {
    insert("PKT-005");
    insert("PKT-002");
    insert("PKT-008");
    insert("PKT-001");
    insert("PKT-004");

    cari("PKT-004");

    return 0;
}
