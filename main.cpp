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
        std::cout << currentNode->nama << ": " << std::endl;

        int index             = 0;
        JalurDistribusi *item = currentNode->jalur[index];

        while (item) {
            std::cout << "- " << item->node->nama << " jarak " << item->jarak
                      << std::endl;

            index++;
            item = currentNode->jalur[index];
        }

        currentNode = currentNode->nextNode;
    }
}

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

    printJalurDistribusi();

    return 0;
}
