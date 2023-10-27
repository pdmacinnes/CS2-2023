#include <iostream>
#include <string>

class PriorityQueue {
private:
    struct Node {
        std::string data;
        int priority;
        Node* prev;
        Node* next;
        Node(const std::string& data, int priority) : data(data), priority(priority), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    bool highestPriorityIsHighest;

public:
    PriorityQueue(bool highestPriorityIsHighest) : head(nullptr), tail(nullptr), highestPriorityIsHighest(highestPriorityIsHighest) {}

    void Insert(const std::string& data, int priority) {
        Node* newNode = new Node(data, priority);

        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            Node* current = highestPriorityIsHighest ? head : tail;

            while (current) {
                if ((highestPriorityIsHighest && priority > current->priority) || (!highestPriorityIsHighest && priority < current->priority)) {
                    newNode->next = current;
                    newNode->prev = current->prev;

                    if (current->prev) {
                        current->prev->next = newNode;
                    } else {
                        head = newNode;
                    }

                    current->prev = newNode;
                    return;
                }

                current = highestPriorityIsHighest ? current->next : current->prev;
            }

            // Insert at the end
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }   

    void Remove() {
        if (!head) {
            return; // Empty queue
        }

        Node* toRemove = highestPriorityIsHighest ? head : tail;
        if (toRemove->prev) {
            toRemove->prev->next = toRemove->next;
        } else {
            head = toRemove->next;
        }

        if (toRemove->next) {
            toRemove->next->prev = toRemove->prev;
        } else {
            tail = toRemove->prev;
        }

        delete toRemove;
    }

    std::string Peek() {
        if (!head) {
            return "Priority Queue is empty.";
        }
        return highestPriorityIsHighest ? head->data : tail->data;
    }

    void IncreasePriority(const std::string& data, int newPriority) {
        if (!head) {
            return; // Empty queue
        }

        Node* current = head;

        while (current) {
            if (current->data == data) {
                if (highestPriorityIsHighest && newPriority > current->priority) {
                    current->priority = newPriority;
                } else if (!highestPriorityIsHighest && newPriority < current->priority) {
                    current->priority = newPriority;
                }

                return;
            }

            current = current->next;
        }
    }

    void DecreasePriority(const std::string& data, int newPriority) {
        IncreasePriority(data, newPriority); // Decreasing priority works the same way as increasing in this implementation.
    }

    void Erase(const std::string& data) {
        Node* current = head;

        while (current) {
            if (current->data == data) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }

                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }

                delete current;
                return;
            }

            current = current->next;
        }
    }

    int Size() {
        int count = 0;
        Node* current = head;

        while (current) {
            count++;
            current = current->next;
        }

        return count;
    }
};

int main() {
    PriorityQueue pq(false); // Configure for lowest priority being highest
    pq.Insert("Task A", 3);
    pq.Insert("Task B", 1);
    pq.Insert("Task C", 5);
    pq.IncreasePriority("Task A", 6); // Increase priority of Task A to 6
    pq.DecreasePriority("Task C", 2); // Decrease priority of Task C to 2
    std::cout << "Size: " << pq.Size() << std::endl; // Output: 3
    std::cout << "Peek: " << pq.Peek() << std::endl; // Output: Task B (since lowest priority is highest)
    pq.Remove();
    std::cout << "Peek after removal: " << pq.Peek() << std::endl; // Output: Task C

    PriorityQueue pq2(true);

    pq2.Insert("Task X", 10);
    pq2.Insert("Task Y", 8);
    pq2.Insert("Task Z", 12);
    pq2.IncreasePriority("Task Y", 15);
    pq2.DecreasePriority("Task Z", 9);

    std::cout << "Scenario 2 - Highest priority is highest:\n"  ;
    std::cout << "Size: " << pq2.Size() << std::endl;
    std::cout << "Peek: " << pq2.Peek() << std::endl;
    pq2.Remove();
    std::cout << "Peek after removal: " << pq2.Peek() << std::endl;
    std::cout << "\n";

    return 0;
}
