/*
https://refactoring.guru/design-patterns/abstract-factory/cpp/example
*/

#include <iostream>

class AbstractProdcutA{
public:
    virtual ~AbstractProdcutA() {};
    virtual std::string UsefulFunctionA() const = 0;
};
class ConcreteProdcutA1 : public AbstractProdcutA {
public:
    std::string UsefulFunctionA() const override {
        return "The Result of the product A1.";
    }
};
class ConcreteProdcutA2 : public AbstractProdcutA {
public:
    std::string UsefulFunctionA() const override {
        return "The Result of the prodcut A2.";
    }
};


class AbstractProductB{
public:
    virtual ~AbstractProductB() {};
    virtual std::string UsefulFunctionB() const = 0;
    virtual std::string AnotherUsefulFunctionB(const AbstractProdcutA& collaborator) const = 0;
};
class ConcreteProductB1 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The Result of the product B1.";
    }
    std::string AnotherUsefulFunctionB(const AbstractProdcutA& collaborator) const {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of B1 collaborating with ( " + result + " )."; 
    }
};
class ConcreteProductB2 : public AbstractProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The Result of the product B2.";
    }
    std::string AnotherUsefulFunctionB(const AbstractProdcutA& collaborator) const {
        std::string result = collaborator.UsefulFunctionA();
        return "The result of B2 collaborating with ( " + result  + " ).";
    }
};


class AbstractFactory {
public:
    virtual AbstractProdcutA* CreateProductA() const = 0;
    virtual AbstractProductB* CreateProductB() const = 0;
};
class ConcreteFactory1 : public AbstractFactory{
public:
    AbstractProdcutA* CreateProductA() const{
        return new ConcreteProdcutA1();
    }
    AbstractProductB* CreateProductB() const{
        return new ConcreteProductB1();
    }
};
class ConcreteFactory2 : public AbstractFactory{
public:
    AbstractProdcutA* CreateProductA() const {
        return new ConcreteProdcutA2();
    }
    AbstractProductB* CreateProductB() const {
        return new ConcreteProductB2();
    }
};


void ClientCode(AbstractFactory* factory){
    AbstractProdcutA* productA = factory->CreateProductA();
    AbstractProductB* productB = factory->CreateProductB();
    std::cout << productA->UsefulFunctionA() << "\n";
    std::cout << productB->AnotherUsefulFunctionB(*(productA)) << "\n";
    delete productA;
    delete productB;
}


int main() {

    ConcreteFactory1* factory1 = new ConcreteFactory1();
    ClientCode(factory1);
    delete factory1;

    std::cout << "\n\n";

    ConcreteFactory2* factory2 = new ConcreteFactory2();
    ClientCode(factory2);
    delete factory2;

    return 0;
}