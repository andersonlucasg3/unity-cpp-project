#include "Trash.h"
#include <thread>
#include <list>

using namespace std;

namespace CppEngine {
    bool Trash::_running = false;
    list<Object *> Trash::_trashBag;
    thread Trash::_thread;
    mutex Trash::_mutex;

    void Trash::garbageDisposer() {
        bool lockedRunning;
        unique_lock<mutex> lock(_mutex);
        do {
            lock.lock();

            incinerate();

            lockedRunning = _running;

            lock.unlock();

            this_thread::sleep_for(chrono::milliseconds(100));
        } while (lockedRunning);
    }

    void Trash::setup() {
        _running = true;
        _thread = thread(&garbageDisposer);
    }

    void Trash::add(Object *obj) {
        unique_lock<mutex> lock(_mutex);
        lock.lock();

        _trashBag.push_front(obj);

        lock.unlock();
    }

    void Trash::empty() {
        unique_lock<mutex> lock(_mutex);
        lock.lock();

        _running = false;

        _thread.join();

        incinerate();

        lock.unlock();
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