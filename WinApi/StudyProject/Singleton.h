#pragma once

template<typename T>
class Singleton {
public:
    static T* GetInst() {
        static T instance;
        return &instance;
    }

    // 삭제된 복사 생성자와 대입 연산자
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() {}
    virtual ~Singleton() {}
};