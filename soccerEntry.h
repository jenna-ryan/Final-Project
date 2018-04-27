
// soccerEntry.h

#ifndef _PhoneBookEntry_h_
#define _PhoneBookEntry_h_

#include <fstream>
#include <string>

class PhoneBookEntry
{
public:
    PhoneBookEntry() : firstName("no name"), lastName("no name"),
	   	yob(0), status(0), category(0) {}

    PhoneBookEntry(const std::string & firstName0, const std::string & lastName0,
		int yob0, bool status0, int category0) :
        firstName(firstName0), lastName(lastName0),
		yob(yob0), status(status0), category(category0) {}

    void print_raw( std::ofstream & out, const PhoneBookEntry & e);

    std::string firstName;
	std::string lastName;
	int yob;
    bool status; //0 for unpaid, 1 for paid
	int category;
};

inline void print_raw( std::ofstream & out, const PhoneBookEntry & e)
{
    out << e.firstName << std::endl << e.lastName << std::endl << e.yob << std::endl;
	if(e.status == 1)
		out << 1 << std::endl;
	else
		out << 0 << std::endl;
	out << e.category << std::endl;
}

inline std::istream & operator>>(std::istream & in,
                                 PhoneBookEntry & e)
{
    getline(in, e.firstName);
    getline(in, e.lastName);
    in >> e.yob >> e.status >> e.category;
	in.get(); // \n
    return in;
}

inline std::ostream & operator<<(std::ostream & out,
                                 const PhoneBookEntry & e)
{
    out << e.firstName << ' ' << e.lastName << std::endl << e.yob << std::endl;
	if(e.status == 1)
		out << "Paid" << std::endl;
	else
		out << "Unpaid" << std::endl;
	out << 'U' << e.category << std::endl;
    return out;
}

#endif
