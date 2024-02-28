/*
https://refactoring.guru/design-patterns/singleton/cpp/example
*/

#include <string>
#include <iostream>
#include <mutex>

class Singleton{

private:
    static Singleton* pinstance;
    static std::mutex mutex_;

protected:
    Singleton(const std::string value): value_(value) {}
    ~Singleton() {}
    std::string value_;

public:
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton& other) = delete;
    static Singleton* GetInstance(const std::string& value);

    void SomeBussinesLogic() {

    }

    std::string value() const {
        return value_;
    }
};

Singleton* Singleton::pinstance {nullptr};
std::mutex Singleton::mutex_;

Singleton* Singleton::GetInstance(const std::string& value){
    std::lock_guard<std::mutex> lock(mutex_);
    if(pinstance==nullptr){
        pinstance = new Singleton(value);
    }
    return pinstance;
}

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Singleton* singleton = Singleton::GetInstance("Foo");
    std::cout << singleton->value() << "\n";
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Singleton* singleton = Singleton::GetInstance("Bar");
    std::cout << singleton->value() << "\n";
}

int main(){

    std::cout << "If you see two different value then, it means two new instances have been created.\n\n";

    std::thread t2(ThreadBar);
    std::thread t1(ThreadFoo);

    t1.join();
    t2.join();

    return 0;
}