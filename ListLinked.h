#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "List => [\n";
        Node<T>* aux = list.first;
        while (aux != nullptr) {
            out << "  " << aux->data << "\n";
            aux = aux->next;
        }
        out << "]";
        return out;
    }

    T operator[](int pos) {
        return get(pos);
    }

    int size() const override { return n; }

    bool empty() const override { return n == 0; }

    T get(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
        Node<T>* aux = first;
        for (int i = 0; i < pos; i++) aux = aux->next;
        return aux->data;
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("Posición inválida!");
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* aux = first;
            for (int i = 0; i < pos - 1; i++) aux = aux->next;
            aux->next = new Node<T>(e, aux->next);
        }
        n++;
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("Posición inválida!");
        Node<T>* aux = first;
        T val;
        if (pos == 0) {
            val = first->data;
            first = first->next;
            delete aux;
        } else {
            for (int i = 0; i < pos - 1; i++) aux = aux->next;
            Node<T>* toDelete = aux->next;
            val = toDelete->data;
            aux->next = toDelete->next;
            delete toDelete;
        }
        n--;
        return val;
    }

    int search(T e) override {
        Node<T>* aux = first;
        int pos = 0;
        while (aux != nullptr) {
            if (aux->data == e) return pos;
            aux = aux->next;
            pos++;
        }
        return -1;
    }

    void append(T e) { insert(n, e); }

    void prepend(T e) { insert(0, e); }

};

#endif // LISTLINKED_H
