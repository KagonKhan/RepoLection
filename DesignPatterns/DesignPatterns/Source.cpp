#include <iostream>
#include <filesystem>

struct Saver {
	virtual void save() = 0;
	virtual void setup() = 0;
	virtual void allocate() = 0;
};

struct RAMSaver : public Saver {
	void* location;

	void allocate() override
	{

	}

	void setup() override
	{

	}

	void save() override
	{
	}
};

struct DiskSaver : public Saver {
	std::filesystem::path path;
	void allocate() override
	{

	}

	void setup() override
	{

	}

	void save() override
	{
	}
};

struct StreamSaver : public Saver {
	void* IPconnection;

	void allocate() override
	{

	}

	void setup() override
	{

	}

	void save() override
	{
	}
};


class SavingFacade
{
	RAMSaver ram;
	DiskSaver disk;
	StreamSaver stream;


public:
	void* saveToRam(void* data) {
		ram.allocate();
		ram.setup();
		ram.save();
		return ram.location;
	}
	auto saveToDisk(void* data) {
		disk.allocate();
		disk.setup();
		disk.save();
		return disk.path;
	}
	void* saveToStream(void* data) {
		stream.allocate();
		stream.setup();
		stream.save();
		return stream.IPconnection;
	}
};


void performFacade()
{
	SavingFacade saver;
	std::vector<int> packets;

	saver.saveToDisk(&packets);
}