#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap) : boxCapacity(boxCap) {}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box &b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}

// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    vector<Object>::iterator obj;
    unsigned count = 0;
    for (obj = objs.begin(); obj != objs.end();) {
        if (obj->getWeight() <= boxCapacity) {
            objects.push(*obj);
            obj = objs.erase(obj);
            count++;
        } else obj++;
    }
    return count;
}

// TODO
Box PackagingMachine::searchBox(Object &obj) {
    HeapBox temp;
    while (!boxes.empty()) {
        Box box = boxes.top();
        boxes.pop();
        if (box.getFree() >= obj.getWeight()) {
            while (!temp.empty()) {
                boxes.push(temp.top());
                temp.pop();
            }
            return box;
        }
        temp.push(box);
    }
    while (!temp.empty()) {
        boxes.push(temp.top());
        temp.pop();
    }
    return Box(boxCapacity);
}

// TODO
unsigned PackagingMachine::packObjects() {
    while (!objects.empty()) {
        Object obj = objects.top();
        objects.pop();
        Box box = searchBox(obj);
        box.addObject(obj);
        boxes.push(box);
    }
    return boxes.size();
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
    ostringstream ss;
    if( objects.empty() ) return "No objects!\n";
    HeapObj buffer = objects;
    while (!buffer.empty()) {
        Object obj = buffer.top();
        buffer.pop();
        ss << obj << endl;
    }
    return ss.str();
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
    if (boxes.empty()) throw MachineWithoutBoxes();
    HeapBox temp = boxes;
    Box m_box = temp.top();
    temp.pop();
    while (!temp.empty()) {
        if (temp.top().getSize() > m_box.getSize()) m_box = temp.top();
        temp.pop();
    }
    return m_box;
}
