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
#include<vector>

int SoccerList::compute_category(int yob)
{
    int age = season_ - yob;
    if(age == 4 || age == 5 || age == 6)
        return 6;
    else if(age == 7 || age == 8)
        return 8;
    else if(age == 9 || age == 10)
        return 10;
    else if(age == 11 || age == 12)
        return 12;
    else if(age == 13 || age == 14)
        return 14;
    else if(age == 15 || age == 16 || age == 17)
        return 17;
}

void SoccerList::read_file(const std::string & file_name)
{
    ifstream ifs(file_name);
    if (!ifs) // no file -- one will be created when write_file is called
        return;

    ifs >> season_;

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

void SoccerList::write_file(const std::string & file_name) const
{
    ofstream out(file_name);
    cout << "PLAYER INFORMATION SAVED\n";
    out << season_ << endl << m_entries_.size() << endl;
    for(auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++)
    {
        print_raw(out, itr->second);

    }
}

void SoccerList::print_to_file(const std::string & file_name) const
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

void SoccerList::print_searches(const std::string & file_name) const
{
/// search results should be saved in a  new search map (member of class) so that one can just iterate through the map
/// clear map when return command is executed

}


bool SoccerList::find(const std::string & search_term, int type)
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

bool SoccerList::find(int search_term, int type)
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

void SoccerList::disp_stats()
{
    pair<int,int> catCount[18] = {{0,0}};   //first stores total, second stores paid

    for(auto itr = m_entries_.begin(); itr != m_entries_.end(); ++itr)
    {
        ++catCount[0].first;
        ++catCount[(itr->second).category].first;
        if((itr->second).status == 1)
        {
            ++catCount[0].second;
            ++catCount[(itr->second).category].second;
        }

    }

    cout << "Players: " << catCount[0].first << endl;
    cout << "   Paid: " << catCount[0].second << endl;
    cout << "   Unpaid: " << catCount[0].first - catCount[0].second << endl;

    std::vector<int> v{6, 8, 10, 12, 14, 17};
    for(auto itr = v.begin(); itr != v.end(); ++itr)
    {
        cout << 'U' << *itr << endl;
        cout << "Players: " << catCount[*itr].first << endl;
        cout << "   Paid: " << catCount[*itr].second << endl;
        cout << "   Unpaid: " << catCount[*itr].first - catCount[*itr].second << endl;
    }

    cout << "Press enter to return" << endl;
    cin.get();
}
