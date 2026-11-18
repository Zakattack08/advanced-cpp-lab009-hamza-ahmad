#include "project/heap.h"

#include <algorithm>
#include <stdexcept>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(const std::vector<int>& values) {
    buildHeap(values);
}

bool MaxHeap::empty() const noexcept {
    return data_.empty();
}

std::size_t MaxHeap::size() const noexcept {
    return data_.size();
}

int MaxHeap::top() const {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    return data_.front();
}

bool MaxHeap::contains(int value) const {
    for (int item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

void MaxHeap::push(int value) {
    data_.push_back(value);
    heapifyUp(data_.size()-1); //restore heap structure starting with the element just added
}

int MaxHeap::pop() {
    if (empty()) throw std::logic_error("Heap is empty");
    swap(data_[0], data_.back()); //swap root and leftmost 0 height node
    int val = data_.back(); //store return value
    data_.pop_back(); //delete node that was root
    heapifyDown(0); //restore heap structure starting with root
    return val;
}

void MaxHeap::buildHeap(const std::vector<int>& values) {
    for (int i : values)
        data_.push_back(i); //insert values into data
    
    //initialize operand to rightmost parent and for loop stop to i reaching root
for (std::size_t i = data_.size() / 2; i > 0; --i)
    heapifyDown(i - 1);
}

std::vector<int> MaxHeap::heapSort() {
    std::vector<int> vec;
    while (!empty()) {
        vec.push_back(this->pop()); //insert all elements of this into vec
    }
    std::reverse(vec.begin(), vec.end());
    return vec;
}

std::vector<int> MaxHeap::toVector() const {
    return data_;
}

std::size_t MaxHeap::parentIndex(std::size_t index) {
    if (index == 0) {
        return 0;
    }
    return (index - 1) / 2;
}

std::size_t MaxHeap::leftChildIndex(std::size_t index) {
    return (2 * index) + 1;
}

std::size_t MaxHeap::rightChildIndex(std::size_t index) {
    return (2 * index) + 2;
}

void MaxHeap::heapifyUp(std::size_t index) {
    size_t p = parentIndex(index); // get parent index
    if (data_[p] < data_[index]) { // swap if needed
        swap(data_[index],data_[p]);
        heapifyUp(p);
    }
    return; // else break
}

void MaxHeap::heapifyDown(std::size_t index) {
    size_t c;
    size_t cLeft = leftChildIndex(index);
    if (cLeft > data_.size()-1) return; //if at leaf node stop
    if (cLeft+1 > data_.size()-1) c = cLeft; //if right child doesn't exist
    else c = (data_[cLeft] > data_[cLeft+1]) ? cLeft : cLeft+1; //get max child index

    if (data_[c] > data_[index]) { // swap if needed
        swap(data_[index],data_[c]);
        heapifyDown(c);
    }
    return; // else break
}

void MaxHeap::swap(int& a, int& b) {
    std::swap(a, b);
}

bool MaxHeap::isValidHeap() const {
    for (std::size_t i = 1; i < data_.size(); ++i) {
        if (data_[parentIndex(i)] < data_[i]) {
            return false;
        }
    }
    return true;
}
