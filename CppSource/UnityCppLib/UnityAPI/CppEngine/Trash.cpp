#include "Trash.h"
#include <thread>
#include <list>

using namespace std;

namespace CppEngine {
    list<Object *> Trash::_trashBag;
    bool Trash::_running = false;

    thread Trash::_thread;
    mutex Trash::_mutex;
    condition_variable Trash::_condition;

    void Trash::garbageDisposer() {
        do {
            this_thread::sleep_for(chrono::milliseconds(100));

            lock_guard guard(_mutex);
            incinerate();
            _condition.notify_one();
        } while (_running);
    }

    void Trash::setup() {
        _running = true;
        _thread = thread(&garbageDisposer);
    }

    void Trash::add(Object *obj) {
        unique_lock lock(_mutex);
        _condition.wait(lock);
        _trashBag.push_front(obj);
        lock.unlock();
    }

    void Trash::empty() {
        _running = false;
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