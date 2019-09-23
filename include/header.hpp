// Copyright 2019 Sabitov Egor <q.st.stream@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <atomic>
#include <utility>

class Control {
    std::atomic_int counter;
public:
    Control() {
        counter = 0;
    }

    explicit Control(int a) {
        counter = a;
    }

    void increase() {
        counter++;
    }

    void decrease() {
        counter--;
    }

    size_t c_count() {
        return static_cast<size_t>(counter);
    }
};

template<typename T>

class SharedPtr {
    Control *count;
    T *data;

public:
    ~SharedPtr() {
        if (*this) {
            count->decrease();
            if (count->c_count()== 0) {
                delete data;
                delete count;
            }
        }
    }

    SharedPtr() {
        count = nullptr;
        data = nullptr;
    }

   explicit SharedPtr(T *d) {
        count = new Control(1);
        data = d;
    }

    SharedPtr(const SharedPtr &r) {
        count = r.count;
        if (r) count->increase();
        data = r.data;
    }

    SharedPtr(SharedPtr &&r) {
        count = r.count;
        if (r != nullptr) count->increase();
        data = r.data;
    }

    auto operator=(const SharedPtr &r) -> SharedPtr & {
        if (*this) {
            count->decrease();
            if (count->c_count() == 0) {
                delete count;
                delete data;
            }
        }
        data = r.data;
        count = r.count;
        if (*this) count->increase();
        return (*this);
        //r.counter++;
    }

    auto operator=(SharedPtr &&r) -> SharedPtr & {
        if (*this) {
            count->decrease();
            if (count->c_count() == 0) {
                delete count;
                delete data;
            }
        }
        data = r.data;
        count = r.counter;
        if (*this) count->increase();
        return (*this);
    }

    // проверяет, указывает ли указатель на объект
    operator bool() const {
        if (data == nullptr)
            return false;
        else
            return true;
    }

    auto operator*() const -> T & { return *data; }

    auto operator->() const -> T * { return data; }

    auto get() -> T * { return data; }

    void reset() {
        count->decrease();
        if (count->c_count() == 0) {
            delete data;
            delete count;
        }
        data = nullptr;
        count = nullptr;
    }

    void reset(T *ptr) {
        reset();
        data = ptr;
        count = new Control(1);
    }

    void swap(SharedPtr &r) {
        if (data == r.data)
            return;
        auto buf = r;
        r = *this;
        *this = buf;
    }

    auto use_count() const -> size_t {
        if (!*this)
            return 0;
        return count->c_count();
    }
};

#endif // INCLUDE_HEADER_HPP_
