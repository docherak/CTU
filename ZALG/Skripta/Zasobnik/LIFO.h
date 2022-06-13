#include "Element.h"
class LIFO {
private:
    Element* head;
    int size;
public:
    LIFO();
    ~LIFO();
    void setHead(Element *h) { head = h; }
    Element* getHead() { return head; }
    int getSize() { return size; }
    Element* top();
    Element* pop();
    void push(Element* e);
    bool isEmpty();
    void clean();
};
