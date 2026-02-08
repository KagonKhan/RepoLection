#pragma once
#include <iostream>
#include <format>
#include <chrono>

namespace Proxy
{

	class Service {
	public:
		virtual void plot() = 0;
	};

	class ActualService : public Service
	{
	public:
		void plot() {};
	};


	class ServiceProxy : public Service
	{
	private:
		ActualService service;

		void Log() {
			std::cout << "Accessing service on " << std::format("{:%d-%m-%Y %H:%M:%OS}", std::chrono::system_clock::now());
		}

		bool CanAccess() {
			return rand() & 1;
		}

	public:
		void plot() override {
			Log();

			if (CanAccess()) {
				std::cout << "Access Granted.\n";
				service.plot();
			}
			else
			{
				std::cout << "Access Denied.\n";
			}
		};
	};
}


