#include <iostream>
#include <string>

const int TABLE_SIZE = 7;

// Struktur entri untuk hash table
struct Entry {
    std::string nik;
    bool terisi;

    Entry() : nik(""), terisi(false) {}
};

// Fungsi hash menggunakan 4 digit terakhir NIK sebagai nilai integer lalu
// modulus dengan 7 (TABLE_SIZE)
int hashFunction(const std::string& nik) {
    // Mengambil 4 digit terakhir dari NIK
    std::string akhir = nik.substr(nik.length() - 4);
    int num           = stoi(akhir);
    return num % TABLE_SIZE;
}

// Fungsi untuk memasukkan NIK ke dalam tabel dengan linear probing
void insertHash(Entry table[], const std::string& nik) {
    int index      = hashFunction(nik);
    int startIndex = index;

    while (table[index].terisi) {
        std::cout << "Kolisi di indeks " << index << " untuk NIK " << nik
                  << ". Probing...\n";
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            std::cout << "Tabel penuh! Gagal menyisipkan " << nik << std::endl;
            return;
        }
    }

    table[index].nik    = nik;
    table[index].terisi = true;
    std::cout << "NIK " << nik << " disimpan di indeks " << index << std::endl;
}

// Mencetak isi hash table
void printTable(Entry table[]) {
    std::cout << "\nIsi Hash Table:\n";
    for (int i = 0; i < TABLE_SIZE; ++i) {
        std::cout << "[" << i << "] ";
        if (table[i].terisi)
            std::cout << table[i].nik;
        else
            std::cout << "(kosong)";
        std::cout << std::endl;
    }
}

int main() {
    Entry hashTable[TABLE_SIZE];

    // Data uji: dua NIK dengan hash sama
    std::string dataNIK[] = {
        "331234567890001",
        "331234567890003",
        "331234567890010",
        "331234567890017",
    };

    for (const std::string& nik : dataNIK) {
        insertHash(hashTable, nik);
    }

    printTable(hashTable);
    return 0;
}
