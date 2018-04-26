// soccerList.cpp

#include "soccerList.h"

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <map>
using std::pair;
#include <string>
using std::string;

void PhoneBookList::read_file(const std::string & file_name)
{
    ifstream ifs(file_name);
    if (!ifs) // no file -- one will be created when write_file is called
        return;

    int num_entries;
    ifs >> num_entries;
    ifs.get(); // \n
    for (int i = 0; i < num_entries; i++) {
        PhoneBookEntry new_entry;
        ifs >> new_entry;
        // m_entries[new_entry.name] = new_entry;
        m_entries_.insert(m_entries_.end(),
                          {new_entry.lastName, new_entry});
    }
    itr_current_entry_ = m_entries_.begin();
}

void PhoneBookList::write_file(const std::string & file_name) const
{
    cout << "Saving not yet implemented\n";
}

void PhoneBookList::print_to_file(const std::string & file_name) const
{
    ofstream out(file_name);
    ///FOR SOME REASON DOESN'T FAIL
    while(out.fail())
    {
        cout << "Unable to write to file chosen, please enter different filename: ";
        string fn;
        cin >> fn;
        out.open(fn);
    }

    for(auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++)
            out << itr->second << endl;

}

void PhoneBookList::print_searches(const std::string & file_name) const
{
/// search results should be saved in a  new search map (member of class) so that one can just iterate through the map
/// clear map when return command is executed

}


bool PhoneBookList::find(const std::string & search_term, int type)
{
	switch (type) {
		case 1 : {
			auto itr = m_entries_.find(search_term);
			if (itr != m_entries_.end()){
				itr_current_entry_ = itr;
				return 1;
			}
			itr = m_entries_.lower_bound(search_term);
			if (itr != m_entries_.end()){
				if( itr->first[search_term.size() - 1] == search_term[search_term.size() - 1])
					itr_current_entry_ = itr;
				return 1;
			}
			return 0;
		}
		case 2 : {
			for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr){
				if(itr->second.firstName == search_term){
					itr_current_entry_ = itr;
					return 1;
				}
			}
			return 0;
		}
		case 3 : {
			bool correctState;
			if(search_term == "Paid" || search_term == "paid")
				correctState = 1;
			if(search_term == "Unpaid" || search_term == "unpaid")
				correctState = 0;
			for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr){
				if(itr->second.status == correctState){
					itr_current_entry_ = itr;
					return 1;
				}
			}
			return 0;
		}
	}
	return 0;
}

bool PhoneBookList::find(int search_term, int type)
{
	switch (type) {
		case 1 : {
			for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr){
				if(itr->second.yob == search_term){
					itr_current_entry_ = itr;
					return 1;
				}
			}
			return 0;

		}
		case 2 : {
			for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr){
				if(itr->second.category == search_term){
					itr_current_entry_ = itr;
					return 1;
				}
			}
			return 0;

		}
	}
	return 0;
}

void PhoneBookList::disp_stats()
{
    int numPaid = 0;

    for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr)
    {
        if((itr->second).status == 1)
        {
            numPaid++;
        }
    }

    cout << "Number of players: " << m_entries_.size() << endl;
    cout << "Paid players:  " << numPaid << endl;
    cout << "Unpaid players: " << m_entries_.size() - numPaid << endl << endl;

    cout << "Press enter to return" << endl;
    cin.get();
}
