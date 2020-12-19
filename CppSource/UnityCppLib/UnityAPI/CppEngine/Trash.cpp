#include "Trash.h"
#include <thread>
#include <list>

using namespace std;

namespace CppEngine {
    list<Object *> Trash::_trashBag;
    bool Trash::_running = false;

    thread Trash::_thread;
    mutex Trash::_trashBarMutex;
    mutex Trash::_runningMutex;


    void Trash::garbageDisposer() {
        bool lockedRunning;
        do {
            this_thread::sleep_for(chrono::milliseconds(100));

            lock_guard<mutex> trashBagGuard(_trashBarMutex);
            incinerate();

            lock_guard<mutex> runningGuard(_runningMutex);
            lockedRunning = _running;
        } while (lockedRunning);
    }

    void Trash::setup() {
        _running = true;
        _thread = thread(&garbageDisposer);
    }

    void Trash::add(Object *obj) {
        lock_guard<mutex> lock(_trashBarMutex);
        _trashBag.push_front(obj);
    }

    void Trash::empty() {
        lock_guard<mutex> *runningGuard = new lock_guard<mutex>(_runningMutex);
        _running = false;
        delete runningGuard;

        _thread.join();

        incinerate();
    }

    void Trash::incinerate() {
        if (!_trashBag.empty()) {
            list<Object *>::iterator iterator = _trashBag.begin();
            for (int index = 0; index < _trashBag.size(); ++index) {
                advance(iterator, index);
                Object *obj = *iterator;
                delete obj;
            }
            _trashBag.clear();
        }
    }
}