class Element {
private:
    int data;
    Element* next;
public:
    Element(int d) { setData(d); }
    void setData(int d) { data = d; }
    void setNext(Element* n) { next = n; }
    void set(int d, Element* n) { setData(d); setNext(n); }
    int getData() { return data; }
    Element* getNext() { return next; }
};
