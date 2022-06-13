#include "LIFO.h"

LIFO::LIFO() {
    size = 0;
    head = nullptr;
}

LIFO::~LIFO() {
    clean();
}

bool LIFO::isEmpty() {
    return head == nullptr;
}

void LIFO::clean() {
    if (!isEmpty()) {
        Element *pom;
        while (head != nullptr) {
            pom = head;
            head = head->getNext();
            delete pom;
        }
        size = 0;
    }
}

Element* LIFO::pop() {
    if (isEmpty())
        return nullptr;
    Element* pom = head;
    head = head->getNext();
    --size;
    pom->setNext(nullptr);
    return pom;
}

Element* LIFO::top() {
    return head;
}

void LIFO::push(Element* e) {
    ++size;
    e->setNext(head);
    head = e;
}
