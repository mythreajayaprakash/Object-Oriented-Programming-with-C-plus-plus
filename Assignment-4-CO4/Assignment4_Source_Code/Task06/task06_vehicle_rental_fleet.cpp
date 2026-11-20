#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
protected:
    std::string registration;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(const std::string& reg, double rate)
        : registration(reg), dailyRate(rate) {}
    virtual ~Vehicle() = default;

    virtual double charge(int days) const = 0;

    virtual void list() const {
        std::cout << registration << " | Daily rate: " << dailyRate
                  << " | " << (rented ? "Rented" : "Available") << '\n';
    }

    void rent() {
        if (!rented) {
            rented = true;
            std::cout << registration << " rented successfully.\n";
        } else {
            std::cout << registration << " is already rented.\n";
        }
    }

    void returnVehicle(int daysLate = 0) {
        if (rented) {
            rented = false;
            std::cout << registration << " returned. Late charge: "
                      << daysLate * 200.0 << '\n';
        } else {
            std::cout << registration << " was not rented.\n";
        }
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}
    double charge(int days) const override {
        return dailyRate * days;
    }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    std::string serviceDueDate;

public:
    MotorVehicle(const std::string& reg, double rate, double level,
                 const std::string& due)
        : Vehicle(reg, rate), fuelOrChargeLevel(level), serviceDueDate(due) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double fuel,
               const std::string& due)
        : MotorVehicle(reg, rate, fuel, due) {}
    double charge(int days) const override {
        return dailyRate * days;
    }
};

class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(const std::string& reg, double rate, double fuel,
        const std::string& due, int seats)
        : MotorVehicle(reg, rate, fuel, due), seatingCapacity(seats) {}

    double charge(int days) const override {
        return dailyRate * days + 100.0;
    }
};

class ElectricCar : public Car {
private:
    double batteryCapacityKWh;

public:
    ElectricCar(const std::string& reg, double rate, double chargeLevel,
                const std::string& due, int seats, double batteryKWh)
        : Car(reg, rate, chargeLevel, due, seats),
          batteryCapacityKWh(batteryKWh) {}

    double charge(int days) const override {
        return dailyRate * days + batteryCapacityKWh * 2.0;
    }
};

// Example extension: add a new derived type without changing Vehicle or existing classes.
class ElectricBus : public Vehicle {
private:
    int seatingCapacity;
    double batteryCapacityKWh;

public:
    ElectricBus(const std::string& reg, double rate, int seats, double batteryKWh)
        : Vehicle(reg, rate), seatingCapacity(seats),
          batteryCapacityKWh(batteryKWh) {}

    double charge(int days) const override {
        return dailyRate * days + batteryCapacityKWh * 2.0;
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("BIKE-01", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TN01-AB1234", 250, 80, "2027-01-10"));
    fleet.push_back(std::make_unique<Car>("TN01-CD5678", 1200, 60, "2027-02-15", 5));
    fleet.push_back(std::make_unique<ElectricCar>("TN01-EV9999", 1500, 75, "2027-03-01", 5, 60));
    fleet.push_back(std::make_unique<ElectricBus>("TN01-BUS111", 3000, 30, 240));

    std::cout << "Fleet listing:\n";
    for (const auto& vehicle : fleet) {
        vehicle->list();
    }

    std::cout << "\nRental charges for 3 days:\n";
    for (const auto& vehicle : fleet) {
        std::cout << vehicle->charge(3) << '\n';
    }

    std::cout << "\nRent and return demonstration:\n";
    fleet[2]->rent();
    fleet[2]->returnVehicle(2);
    return 0;
}
