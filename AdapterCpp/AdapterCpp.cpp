// AdapterCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class IEuSocket
{
public:
	virtual	std::string give_eu_current() const
	{
		return "Default eu current \n";
	}

};

class StandardEuSocket : public IEuSocket
{
public:
	std::string give_eu_current() const
	{
		return "current from EU socket \n";
	} 
};
class IGbSocket
{
public:
	virtual std::string give_gb_current() const
	{
		return "Default GB current \n";
	}
};
class StandardGbSocket : public IGbSocket
{
	std::string give_gb_current() const
	{
		return "current from GB socket \n";
	}
};

class GbToEuAdapter : public IEuSocket
{
private:
	IGbSocket* _gb_socket;
public:
	explicit GbToEuAdapter(IGbSocket* gb_socket)
		: _gb_socket(gb_socket)
	{
		this->_gb_socket = gb_socket;
	}
	std::string give_eu_current() const
	{
		return _gb_socket->give_gb_current();
	}

};
class Laptop
{
private:
	std::string name;
public:
	Laptop(std::string name)
	{
		this->name = name;
	}
	~Laptop() = default;
	std::string get_name()
	{
		return this->name;
	}
};


namespace Charger
{
	void Charge(Laptop* laptop, IEuSocket& euSocket)
	{
		std::cout << "Charging laptop: " << laptop->get_name() << ", with: " << euSocket.give_eu_current();

	}
}
int main()
{
	/**
	 *I am charging my laptop that has EU type of plug in a Standard EU socket *
	 */

	Laptop laptop = Laptop("Lenovo");
	StandardEuSocket eu_Socket = StandardEuSocket();
	Charger::Charge(&laptop, eu_Socket);

	/**
		  * I added GB type socket and want to charge my laptop that has a EU type plug.
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
	Charger::Charge(&laptop, gb_adapted);
}
