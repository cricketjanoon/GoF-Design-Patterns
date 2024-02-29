/*
https://medium.com/@anthony0604/factory-method-in-c-the-right-way-e8c5f015fe39
*/

#include <iostream>

class BattleShip {
public:
    BattleShip() {
        std::cout << "Battleship created.\n";
    }
    virtual void Fire() = 0;
    virtual void Steer() = 0;
};

class Destroyer : public BattleShip {
public:
    Destroyer() {
        std::cout << "Destroyer created.\n";
    }
    void Fire() {
        std::cout << "Destroyer Fire.\n";
    }
    void Steer() {
        std::cout << "Destroyer Steer.\n";
    }
};

class Carrier : public BattleShip {
public:
    Carrier() {
        std::cout << "Carrier created.\n";
    }
    void Fire() {
        std::cout << "Carrier Fire.\n";
    }
    void Steer() {
        std::cout << "Carrier Steer.\n";
    }
};

enum class ShipType {
    Destroyer,
    Carrier,
};


/*
Factory method.
*/
BattleShip* CreateShipFactory(ShipType type) {
    BattleShip* pShip = nullptr;
    if (type == ShipType::Destroyer) {
        pShip = new Destroyer();
    }
    else if (type == ShipType::Carrier) {
        pShip = new Carrier();
    }
    return pShip;
}

/*
Factory class.
*/
class FactoryClass {
public:
    BattleShip* CreateDestroyer() {
        return new Destroyer();
    }
    BattleShip* CreateCarrier() {
        return new Carrier();
    }
};

int main(){

    std::cout << "Creating carrier and destroyer using Factory method.\n\n";
    BattleShip* carrier1 = CreateShipFactory(ShipType::Carrier);
    carrier1->Fire();
    carrier1->Steer();

    BattleShip* destroyer1 = CreateShipFactory(ShipType::Destroyer);
    destroyer1->Fire();
    destroyer1->Steer();


    std::cout << "\n\nCreating carrier and destroyer using Factory class.\n\n";

    FactoryClass* factory = new FactoryClass();

    BattleShip* carrier2 = factory->CreateCarrier();
    carrier1->Fire();
    carrier1->Steer();

    BattleShip* destroyer2 = factory->CreateDestroyer();
    destroyer2->Fire();
    destroyer2->Steer();

    return 0;
}