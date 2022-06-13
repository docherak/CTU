#include "FIFO.h"

FIFO::FIFO() {
    size = 0;
    head =nullptr;
    tail =nullptr;
}

bool FIFO::isEmpty() {
    return head == nullptr;
}

FIFO::~FIFO() {
    clean();
}

void FIFO::clean() {
    if(!isEmpty()) {
        Element* pom;
        while(head !=nullptr) {
            pom = head;
            head = head->getNext();
            delete pom;
        }
        tail =nullptr;
        size = 0;}
}

Element* FIFO::pop() {
    if(isEmpty())
        return nullptr;
    Element* pom = head;
    head = head->getNext();
    --size;
    pom->setNext(nullptr);
    return pom;
}

Element* FIFO::top() {
    return head;
}

void FIFO::push(Element* e) {
    ++size;
    tail->setNext(e);
    tail = e;
}
