#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    next = nullptr;
    prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head_;
    Node* currentnext;
    while(current != nullptr){
        currentnext = current->next;
        delete current;
        current = currentnext;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    if(size_ == 0){
        return true;
    }

    return false;
}


bool DoublyLinkedList::full() const {
    if(size_ == CAPACITY){
        return true;
    }

    return false;
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    if(index >= size_){
        return tail_->value;
    }

    Node* current = head_;
    int idx = 0;
    while(idx != index){
        current = current->next;
        idx++;
    }
    return current->value;
}


unsigned int DoublyLinkedList::search(DataType value) const {
    Node* current = head_;
    int index = 0;
    while(current != nullptr){
        if(current->value == value){
            return index;
        }
        current = current->next;
        index++;
    }

    return size_;
}


void DoublyLinkedList::print() const {
    Node* current = head_;
    while(current != nullptr){
        std::cout << current->value << std::endl;
        current = current->next;
    }
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    if(index >= size_){
        return nullptr;
    }

    int idx = 0;
    Node* current = head_;
    while(idx != index){
        current = current->next;
        idx++;
    }

    return current;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    if(index > size_ || size_ == CAPACITY){
        return false;
    }

    Node* newNode = new Node(value);

    // inserting when size 0
    if (size_ == 0){
        head_ = newNode;
        tail_ = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }

    // inserting as first index
    else if(index == 0){
        Node* temp = head_;
        head_ = newNode;
        head_->next = temp;
        head_->prev = nullptr;
        temp->prev = head_;
    }

    // inserting last index
    else if(index == size_){
        newNode->next = nullptr;
        tail_->next = newNode;
        newNode->prev = tail_;
        tail_ = newNode;
    }

    // inserting middle
    else{

        // 2 nodes that keeps track of current and previous nodes
        Node* previous;
        Node* current = head_;
        int idx = 0;
        while(idx != index){ // update previous and current node until right index
            previous = current;
            current = current->next;
            idx++;
        }

        // change where previous node is pointing, current index node is pointing, and
        // where node after index node is pointing
        previous->next = newNode;
        newNode->prev = previous;
        newNode->next = current;
        current->prev = newNode;
    }
    size_++;
    return true;
}


bool DoublyLinkedList::insert_front(DataType value) {
    return insert(value, 0);
}


bool DoublyLinkedList::insert_back(DataType value) {
    return insert(value, size_);
}


bool DoublyLinkedList::remove(unsigned int index) {
    if(size_ == 0 || index >= size_){
        return false;
    }

    if(index == 0){
        Node* temp = head_;
        head_ = head_->next;
        if(head_ != nullptr){
            head_->prev = nullptr;
        }
        delete temp;
        temp = nullptr;
    }

    else if(index == size_ - 1){
        Node* temp = tail_;
        tail_ = tail_->prev;
        if(tail_ != nullptr){
            tail_->next = nullptr;
        }
        delete temp;
        temp = nullptr;
    }

    else{
        Node* previous;
        Node* current = head_;
        int idx = 0;
        while(idx != index){
            previous = current;
            current = current->next;
            idx++;
        }

        previous->next = current->next;
        current->next->prev = previous;
        delete current;
        current = nullptr;
    }
    size_--;
    return true;
}


bool DoublyLinkedList::remove_front() {
    return remove(0);
}


bool DoublyLinkedList::remove_back() {
    return remove(size_ - 1);
}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    if(size_ == 0 || index >= size_){
        return false;
    }

    else{
        Node* current = head_;
        int idx = 0;
        while(idx != index){
            current = current->next;
            idx++;
        }
        current->value = value;
    }
    return true;
}
