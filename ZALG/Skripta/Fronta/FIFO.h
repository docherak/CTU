#include "Element.h"

class FIFO {
private:
    Element *head, *tail;
    int size;
public:
    FIFO();
    ~FIFO();
    void setHead(Element *h) { head = h; }
    void setTail(Element *t) { tail = t; }
    Element* getHead() { return head; }
    Element* getTail() { return tail; }
    int getSize() { return size; }
    Element* top();
    Element* pop();
    void push(Element* e);
    bool isEmpty();
    void clean();
};
