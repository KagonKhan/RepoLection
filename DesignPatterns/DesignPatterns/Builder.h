#include <iostream>
namespace Builder
{

	class Car {
		std::size_t door_amount;
		bool butterfly_doors;
		std::size_t horsepower;
		bool allWheelDrive;
	public:
		Car(std::size_t door_amount, bool butterfly, std::size_t power, bool all_wheel)
			: door_amount(door_amount), butterfly_doors(butterfly), horsepower(power), allWheelDrive(all_wheel)
		{

		};

		void print() {
			std::cout << "Doors: " << door_amount << (butterfly_doors ? " butterfly" : " normal") <<
				"\nHP:" << horsepower << "\n" << (allWheelDrive ? "AWD" : "RWD");
		}
	};


	class CarBuilder
	{
		struct settings {
			std::size_t door_amount{ 5 };
			bool butterfly_doors{ false };
			std::size_t horsepower{ 100 };
			bool allWheelDrive{ false };
		} car_settings;

	public:
		void numberOfDoors(std::size_t amount) { car_settings.door_amount = amount; };
		void butterflyDoors(bool butterfly) { car_settings.butterfly_doors = butterfly; };
		void engineHorsePower(size_t power) { car_settings.horsepower = power; };
		void allWheelDrive(bool drive) { car_settings.allWheelDrive = drive; };

		Car* build() {
			return new Car(car_settings.door_amount, car_settings.butterfly_doors, car_settings.horsepower, car_settings.allWheelDrive);
		}
	};

	class Director {
	protected:
		CarBuilder* builder;

	public:
		virtual void setBuilder(CarBuilder* b) = 0;

		Car* build() {
			return builder->build();
		}
	};


	class SportsDirector : public Director {
	public:
		void setBuilder(CarBuilder* b) override {
			builder = b;
			b->butterflyDoors(true);
			b->numberOfDoors(2);
			b->engineHorsePower(450);
			b->allWheelDrive(false);
		};
	};
}

void performBuilder() {
	using namespace Builder;
	CarBuilder* builder{ new CarBuilder() };
	SportsDirector director;
	director.setBuilder(builder);

	auto sports_car = director.build();
	sports_car->print();
}