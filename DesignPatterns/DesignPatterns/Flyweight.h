#pragma once
#include <iostream>
#include <string>
#include <unordered_map>


namespace Flyweight
{
	struct CarFlyWeight {
		std::string model, brand;
		size_t year;
	};

	struct Getter
	{
		inline static std::unordered_map<std::string, CarFlyWeight> cars;

	public:
		static std::string GetKey(std::string model, std::string brand, size_t year) {
			return model + "_" + brand + "_" + std::to_string(year);
		}

		static CarFlyWeight& get(std::string model, std::string brand, size_t year) {
			std::string key = GetKey(model, brand, year);

			if (cars.contains(key)) {
				return cars.at(key);
			}
			else {
				cars.try_emplace(key, CarFlyWeight{ model, brand, year });
				return cars.at(key);
			}
		}
	};

	struct Car {
		std::string vin;
		std::string plates;

		CarFlyWeight& rest;// Some heavy shit
	};

	struct CarOwner {
		CarOwner(std::string owner, Car& car) : owner(std::move(owner)), car(car) {}

		std::string owner;
		Car& car;
	};
}

void performFlyweight()
{
	using namespace Flyweight;
	CarFlyWeight f40_bmw = Getter::get("F40", "BMW", 2004);
	CarFlyWeight F52_bmw = Getter::get("F52", "BMW", 2017);
	CarFlyWeight GranCoupe_s2_bmw = Getter::get("2 Series Gran Coupé", "BMW", 2020);
	CarFlyWeight s2_bmw = Getter::get("2 Series", "BMW", 2021);
	CarFlyWeight s3_bmw = Getter::get("3 Series", "BMW", 2018);

	Car car1{ "vin1", "awe123", f40_bmw };
	Car car2{ "vin2", "awe1234", f40_bmw };
	CarOwner co{ "asd", car1 };
}