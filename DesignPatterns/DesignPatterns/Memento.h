#include <string>
#include <chrono>
#include <format>
#include <iostream>
#include <thread>

namespace Memento
{
	class Memento {
	public:
		virtual std::string state() const = 0;
		virtual std::string date() const = 0;
	};

	class NotepadMemento : public Memento {
	public:
		NotepadMemento(std::string data) : data(data) {
			const auto now = std::chrono::system_clock::now();
			creation_date = std::format("{:%d-%m-%Y %H:%M:%OS}", now);
		}

		std::string state() const override {
			return data;
		}

		std::string date() const override {
			return creation_date;
		}

	private:
		std::string data;
		std::string creation_date;
	};

	class Notepad {
	public:
		void write(std::string data) {
			notepad_data += data;
			cursor_position += data.size();
		}

		void show() {
			std::cout << notepad_data << "\n";
		}

		void remove(size_t amount) {
			if (amount > cursor_position)
				return; // cannot

			notepad_data.erase(notepad_data.end() - amount);
			cursor_position -= amount;
		}

		Memento* save() {
			return new NotepadMemento{ notepad_data };
		}

		void load(Memento* save) {
			std::cout << "Loading save made " << save->date() << "\n";
			notepad_data = save->state();
			cursor_position = notepad_data.size();
		}

	private:
		size_t cursor_position{ 0 };
		std::string notepad_data;
	};


}

void performMemento()
{
	using namespace Memento;

	Notepad npp;
	npp.write("Initial commit. ");
	auto commit_1 = npp.save();

	npp.write("\nAnother commit. ");
	auto commit_2 = npp.save();

	std::this_thread::sleep_for(std::chrono::seconds{ 2 });
	npp.write("\nCursed commit. ");
	auto commit_3 = npp.save();


	npp.show();


	std::cout << "\n==============================================\n";
	npp.load(commit_2);
	npp.show();

	std::cout << "\n==============================================\n";
	npp.load(commit_1);
	npp.show();


	std::cout << "\n==============================================\n";
	npp.load(commit_3);
	npp.show();
}