#include <iostream>

class IEuSocket //This is an interface, because it has: virtual give_gb_current() = 0;
{
public:
	virtual ~IEuSocket() = default;// why do I need virtual destructor?
	virtual	std::string give_eu_current() = 0;
};

class StandardEuSocket : public IEuSocket
{
public:
	std::string give_eu_current()  override
	{
		return "current from EU socket";
	}
};
class IGbSocket 
{
public:
	virtual ~IGbSocket() = default;
	virtual std::string give_gb_current() = 0;
};


class StandardGbSocket : public IGbSocket
{
public:

	std::string give_gb_current() override
	{
		return "current from GB socket";
	}
};

class GbToEuAdapter : public IEuSocket
{
private:
	IGbSocket* gb_socket_;
public:
	explicit GbToEuAdapter(IGbSocket* gb_socket)
		: gb_socket_(gb_socket)
	{
	}

	std::string give_eu_current() override
	{
		return "  (using adapter) " + gb_socket_->give_gb_current();
	}

};

class Laptop
{
private:
	const char* name_;
public:
	Laptop(const char* name) : name_(name) {
	}

	std::string get_name() const
	{
		return this->name_;
	}

};

namespace charger
{
	void charge(const Laptop* laptop, IEuSocket& eu_socket)
	{
		std::cout << "Charging Laptop: " << laptop->get_name() << ", with: " << eu_socket.give_eu_current() << std::endl;;

	}
}
int main()
{
	/**
	 *I am charging my Laptop that has EU type of plug in a Standard EU socket *
	 */

	const Laptop laptop("Lenovo");

	auto eu_socket = StandardEuSocket();
	charger::charge(&laptop, eu_socket);

	/**
		  * I added GB type socket and want to charge my Laptop that has a EU type plug.
		  *
		  * The problem:
		  * Without changing Charger class I need to make adjustments in program and
		  * demonstrate how to charge Laptop using GB type of socket.
		  *
		  * I implemented GB to EU adapter.
		  * GbToEuAdapter implements the interface of a Class that I want to adapt to.
		  * (So that it can have all the methods I need)
		  * Adapter class takes in the constructor an object that needs to be adapted/wrapped
		  * Then in my adapter class I can do what ever it takes to make the GB Socket class work with
		  * my Charger exactly like my EU Socket class does.
		  */
	GbToEuAdapter gb_adapted = GbToEuAdapter(new StandardGbSocket());
	charger::charge(&laptop, gb_adapted);

}
