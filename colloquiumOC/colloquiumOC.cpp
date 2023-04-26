#include <iostream>
#include <string>
#include <memory>
#include <cassert>

using namespace std;

class DeliveryStrategy {

public:
    virtual string deliver() = 0;
    virtual ~DeliveryStrategy() {}

};

class TruckDelivery : public DeliveryStrategy {

public:
    string deliver() override {
        return "Delivering by truck";
    }

};

class ShipDelivery : public DeliveryStrategy {

public:
    string deliver() override {
        return "Delivering by ship";
    }

};

class AirplaneDelivery : public DeliveryStrategy {

public:
    string deliver() override {
        return "Delivering by airplane";
    }

};

class Mineral {

protected:
    unique_ptr<DeliveryStrategy> deliveryStrategy;

public:
    Mineral(unique_ptr<DeliveryStrategy> strategy) : deliveryStrategy(move(strategy)) {}
    virtual string getType() = 0;
    string deliver() {
        return deliveryStrategy->deliver();
    }
    virtual ~Mineral() {}

};

class Coal : public Mineral {

public:
    Coal(unique_ptr<DeliveryStrategy> strategy) : Mineral(move(strategy)) {}

    string getType() override {
        return "Coal";
    }

};

class Gold : public Mineral {

public:

    Gold(unique_ptr<DeliveryStrategy> strategy) : Mineral(move(strategy)) {}

    string getType() override {
        return "Gold";
    }
};

class Diamond : public Mineral {

public:

    Diamond(unique_ptr<DeliveryStrategy> strategy) : Mineral(move(strategy)) {}

    string getType() override {
        return "Diamond";
    }

};

class MineralFactory {

public:

    virtual unique_ptr<Mineral> createMineral(unique_ptr<DeliveryStrategy> strategy) = 0;
    virtual ~MineralFactory() {}

};

class CoalFactory : public MineralFactory {

public:
    unique_ptr<Mineral> createMineral(unique_ptr<DeliveryStrategy> strategy) override {
        return make_unique<Coal>(move(strategy));
    }

};

class GoldFactory : public MineralFactory {

public:
    unique_ptr<Mineral> createMineral(unique_ptr<DeliveryStrategy> strategy) override {
        return make_unique<Gold>(move(strategy));
    }

};

class DiamondFactory : public MineralFactory {

public:
    unique_ptr<Mineral> createMineral(unique_ptr<DeliveryStrategy> strategy) override {
        return make_unique<Diamond>(move(strategy));
    }

};

int main() {

    CoalFactory coalFactory;
    auto coal = coalFactory.createMineral(make_unique<TruckDelivery>());

    if (coal->getType() != "Coal") {
        cout << "Test failed: Incorrect mineral type\n";
        return -1;
    }

    if (coal->deliver() != "Delivering by truck") {
        cout << "Test failed: Incorrect delivery method\n";
        return -1;
    }

    GoldFactory goldFactory;
    auto gold = goldFactory.createMineral(make_unique<ShipDelivery>());

    if (gold->getType() != "Gold") {
        cout << "Test failed: Incorrect mineral type\n";
        return -1;
    }

    if (gold->deliver() != "Delivering by ship") {
        cout << "Test failed: Incorrect delivery method\n";
        return -1;
    }

    DiamondFactory diamondFactory;
    auto diamond = diamondFactory.createMineral(make_unique <AirplaneDelivery>());

    if (diamond->getType() != "Diamond") {
        cout << "Test failed: Incorrect mineral type\n";
        return -1;
    }

    if (diamond->deliver() != "Delivering by airplane") {
        cout << "Test failed: Incorrect delivery method\n";
        return -1;
    }

    cout << "All tests passed\n";

    return 0;
}
