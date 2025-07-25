#include <iostream>

#define MAX_JALUR 10

struct JalurDistribusi;
struct PusatDistribusi;

struct JalurDistribusi {
    PusatDistribusi *node;
    int jarak;
};

struct PusatDistribusi {
    char nama;
    JalurDistribusi *jalur[MAX_JALUR];
    PusatDistribusi *nextNode;
};

PusatDistribusi *root = new PusatDistribusi{'A'};

PusatDistribusi *cariNode(char namaNode) {
    PusatDistribusi *currentNode = root;

    while (currentNode->nama != namaNode) {
        if (!(currentNode->nextNode)) {
            return nullptr;
        }

        currentNode = currentNode->nextNode;
    }

    return currentNode;
}

void tambahNode(PusatDistribusi *nodeBaru) {
    PusatDistribusi *currentNode = root;

    while (currentNode->nextNode) {
        currentNode = currentNode->nextNode;
    }

    currentNode->nextNode = nodeBaru;
}

void tambahJalurPadaNode(PusatDistribusi *nodeAsal,
                         JalurDistribusi *jalurDistribusi) {
    for (int index = 0; index < MAX_JALUR; index++) {
        if (!nodeAsal->jalur[index]) {
            nodeAsal->jalur[index] = jalurDistribusi;
            break;
        }
    }
}

void tambahJalurPusatDistribusi(char namaNodeAsal, char namaNodeTujuan,
                                int jarak) {
    PusatDistribusi *nodeAsal = cariNode(namaNodeAsal);
    if (!nodeAsal) {
        PusatDistribusi *nodeAsalBaru = new PusatDistribusi{namaNodeAsal};
        tambahNode(nodeAsalBaru);
        nodeAsal = nodeAsalBaru;
    }

    PusatDistribusi *nodeTujuan = cariNode(namaNodeTujuan);
    if (nodeTujuan) {
        JalurDistribusi *jalurNodeTujuan =
            new JalurDistribusi{nodeTujuan, jarak};
        tambahJalurPadaNode(nodeAsal, jalurNodeTujuan);
        return;
    }

    PusatDistribusi *nodeTujuanBaru = new PusatDistribusi{namaNodeTujuan};
    JalurDistribusi *jalurNodeBaru = new JalurDistribusi{nodeTujuanBaru, jarak};
    tambahJalurPadaNode(nodeAsal, jalurNodeBaru);
    tambahNode(nodeTujuanBaru);
}

void printJalurDistribusi() {
    PusatDistribusi *currentNode = root;

    while (currentNode->nextNode) {
        std::cout << "Pusat distribusi " << currentNode->nama << ": "
                  << std::endl;

        int index             = 0;
        JalurDistribusi *item = currentNode->jalur[index];

        while (item) {
            std::cout << "\t- Jalur " << item->node->nama << ", jarak "
                      << item->jarak << std::endl;

            index++;
            item = currentNode->jalur[index];
        }

        currentNode = currentNode->nextNode;
    }
}

void pencarianRute(char start, char finish);

int main(int argc, char const *argv[]) {
    tambahJalurPusatDistribusi('A', 'B', 5);
    tambahJalurPusatDistribusi('A', 'C', 10);
    tambahJalurPusatDistribusi('B', 'D', 7);
    tambahJalurPusatDistribusi('C', 'D', 3);
    tambahJalurPusatDistribusi('C', 'E', 8);
    tambahJalurPusatDistribusi('D', 'J', 15);
    tambahJalurPusatDistribusi('E', 'J', 4);
    tambahJalurPusatDistribusi('F', 'G', 6);
    tambahJalurPusatDistribusi('G', 'H', 9);
    tambahJalurPusatDistribusi('H', 'I', 12);
    tambahJalurPusatDistribusi('I', 'J', 5);

    // printJalurDistribusi();

    pencarianRute('A', 'J');

    return 0;
}

void pencarianRute(char start, char finish) {
    PusatDistribusi *nodeArray[MAX_JALUR] = {nullptr};
    bool visited[MAX_JALUR]               = {false};
    PusatDistribusi *parent[MAX_JALUR]    = {nullptr};
    PusatDistribusi *queue[MAX_JALUR];
    int head = 0, tail = 0;

    // Membuat daftar node dari linked list
    PusatDistribusi *current = root;
    while (current) {
        int index        = current->nama - 'A';
        nodeArray[index] = current;
        current          = current->nextNode;
    }

    // Validasi node awal dan tujuan
    int idxStart  = start - 'A';
    int idxFinish = finish - 'A';
    if (!nodeArray[idxStart] || !nodeArray[idxFinish]) {
        std::cout << "Node tidak ditemukan.\n";
        return;
    }

    // Inisialisasi BFS
    visited[idxStart] = true;
    queue[tail++]     = nodeArray[idxStart];
    parent[idxStart]  = nullptr;

    bool ditemukan = false;

    while (head < tail) {
        PusatDistribusi *node = queue[head++];
        if (node->nama == finish) {
            ditemukan = true;
            break;
        }

        for (int i = 0; i < MAX_JALUR && node->jalur[i]; ++i) {
            PusatDistribusi *targetNode = node->jalur[i]->node;
            int idxTarget               = targetNode->nama - 'A';
            if (!visited[idxTarget]) {
                visited[idxTarget] = true;
                parent[idxTarget]  = node;
                queue[tail++]      = targetNode;
            }
        }
    }

    if (!ditemukan) {
        std::cout << "Tidak ada jalur dari " << start << " ke " << finish
                  << ".\n";
        return;
    }

    // Menyusun jalur menggunakan array path (dari belakang)
    PusatDistribusi *path[MAX_JALUR];
    int pathLen = 0;
    for (PusatDistribusi *n = nodeArray[idxFinish]; n != nullptr;
         n                  = parent[n->nama - 'A']) {
        path[pathLen++] = n;
    }

    // Mencetak urutan jalur dari item terakhir
    std::cout << "Jalur dari " << start << " ke " << finish << " (BFS): ";
    for (int i = pathLen - 1; i >= 0; --i) {
        std::cout << path[i]->nama;
        if (i != 0) std::cout << " -> ";
    }
    std::cout << "\n";
}
