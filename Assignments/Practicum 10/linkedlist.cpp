#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 128;

struct word {
    char data[MAX];
    int count;
    word* next;
};

void initialise(word*& head) {
    head = nullptr;
}

bool addnode(char data[], word*& head) {
    if (head == nullptr) {
        head = new word;
        strcpy(head->data, data);
        head->count = 1;
        head->next = nullptr;
        return true;
    } else {
        word* current = head;
        while (current != nullptr) {
            if (strcmp(current->data, data) == 0) {
                current->count++;
                return true;
            }
            if (current->next == nullptr) {
                current->next = new word;
                strcpy(current->next->data, data);
                current->next->count = 1;
                current->next->next = nullptr;
                return true;
            }
            current = current->next;
        }
    }
    return false;
}

void printnodes(word*& head) {
    word* current = head;
    while (current != nullptr) {
        cout << current->data << " - " << current->count << endl;
        current = current->next;
    }
}

void freelist(word*& head) {
    word* current = head;
    while (current != nullptr) {
        word* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

int main(int argc, const char* argv[]) {
    word* head;
    char buffer[MAX];
    ifstream ins;
    
    if (argc < 2) {
        cout << "Error, usage: app file\n\t * app this program \n\t * file input data file. \n\n\t*Terminating!\n";
        exit(1);
    }

    ins.open(argv[1], ios::in);

    if (!ins.good()) {
        cout << "Can not open input file: " << argv[1] << ".. Terminating" << endl;
        return 1;
    }

    initialise(head);

    while (ins >> buffer) {
        if (ins.eof())
            break;

        if (!addnode(buffer, head)) {
            cout << "Could not insert word into the list" << endl;
            freelist(head);
            return 1;
        }
    }

    printnodes(head);

    freelist(head);

    return 0;
}
