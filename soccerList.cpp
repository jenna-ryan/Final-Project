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
#include<sstream>

std::string SoccerList::last_name_check(const std::string & ln)
{
    std::string newName = ln;
    while(m_entries_.find(newName) != m_entries_.end())
        newName = newName + " ";

    return newName;
}


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

void SoccerList::edit_current()
{
    std::string sep(25, '-');

    std::cout << sep << std::endl;
    std::cout << "What would you like to change?\n"
         << "   first name (f)\n"
         << "   last name (l)\n"
         << "   year of birth (y)\n"
         << "   registration status (r)\n" << std::endl;

    if(search_results_.empty()== 0)
    {
        itr_current_entry_ = m_entries_.find(itr_search_current_entry_->first);
        rank_location_ = distance(m_entries_.begin(),itr_current_entry_) + 1;
    }


    char com;
    std::cin >> com;
    switch (com) {
        case 'f':
        {
            std::cout << "Enter new first name: ";
            std::cin >> (itr_current_entry_->second).firstName;
            break;
        }

        case 'l':
        {
            std::cout << "Enter new last name: ";
            string ln;
            std::cin >> ln;
            ln = last_name_check(ln);

            (itr_current_entry_->second).lastName = ln;
            SoccerEntry temp = (itr_current_entry_->second);
            m_entries_.erase(itr_current_entry_);
            m_entries_[ln] = temp;
            itr_current_entry_ = m_entries_.find(ln);
            rank_location_ = distance(m_entries_.begin(),itr_current_entry_) + 1;
            break;

        }
        case 'y':
        {
            cin.get();
            bool valid = false;
			int newYear;
			while(!valid)
            {
                std::cout << "Enter new birth year: ";
        	    string yob_ss;
            	getline(cin, yob_ss);
				std::stringstream ss(yob_ss);
				ss >> newYear;
				if(ss.eof())
					valid = true;
			}

            int category = season_ - newYear;
            while(category < 4 || category > 16)
            {
                std::cout << "Players younger than 4 or older than 16 cannot play in this summer league." << std::endl;

                bool valid = false;
                while(!valid)
                {
                    cout << "year of birth: ";
                    string yob_ss;
                    getline(cin, yob_ss);
                    std::stringstream ss(yob_ss);
                    ss >> newYear;
                    if(ss.eof())
                        valid = true;
                }
                category = season_ - newYear;
            }
            (itr_current_entry_->second).yob = newYear;
            (itr_current_entry_->second).category = compute_category(newYear);
            break;
        }
        case 'r':
        {
            std::cout << "Enter new status (1 for paid, 0 for unpaid): ";
            std::cin >> (itr_current_entry_->second).status;
             break;
        }
    }

    SoccerEntry temp = itr_current_entry_->second;
    std::string key = itr_current_entry_->first;

    if(!search_results_.empty())
    {
        itr_search_current_entry_->second = temp;
    }
}

void SoccerList::read_file(const std::string & file_name)
{
    ifstream ifs(file_name);
    if (!ifs) // no file -- one will be created when write_file is called
    {
        std::cout << "No file found. \n What season would you like to create?\n";
        std::cin >> season_;
        return;
    }


    ifs >> season_;

    int num_entries;
    ifs >> num_entries;
    ifs.get(); // \n
    for (int i = 0; i < num_entries; i++) {
        SoccerEntry new_entry;
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

    int cat[6] = {6, 8, 10, 12, 14, 17};

    for(int i = 0; i < 6; i++)
    {
        out << 'U' << cat[i] << " Players: \n";

        for(auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++)
        {
            if ((itr->second).category == cat[i])
            {
                        out << (itr->second).firstName << ' '
                            << (itr->second).lastName << endl;
            }
        }
    out << endl;
    }
}

void SoccerList::print_searches(const std::string & file_name) const
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

    for(auto itr = search_results_.begin(); itr != search_results_.end(); itr++)
            out << itr->second << endl;


}

bool SoccerList::find()
{
    cout << endl << "SEARCH: Enter '-1' to leave a field unsearched" << std::endl << std::endl;
            cout << "last name: ";
            string lastName;
            getline(cin, lastName);

            cout << endl << "first name: ";
            string firstName;
            getline(cin, firstName);
            cout <<  endl << "payment status(1 for paid, 0 for unpaid): ";


            bool valid = false;
            bool status;
			while(!valid)
            {
        	    string status_ss;
            	getline(cin, status_ss);
				std::stringstream ss(status_ss);
				ss >> status;
				if(ss.eof())
					valid = true;
                else
                    cout << "   Enter '1' if player is paid and '0' if player is unpaid\n";
			}

			valid = false;
			int yob;
            cout << endl << "year of birth: ";
			while(!valid){
        	    string yob_ss;
            	getline(cin, yob_ss);
				std::stringstream ss(yob_ss);
				ss >> yob;
				if(ss.eof())
					valid = true;
                else
                    cout << "   Please re-enter year: ";
			}

			valid = false;
            int category;
            cout << endl << "category: U";
			while(!valid){
        	    string cat_ss;
            	getline(cin, cat_ss);
				std::stringstream ss(cat_ss);
				ss >> category;
				if(ss.eof())
					valid = true;
                else
                    cout << "   Please re-enter category: ";
			}

    std::map<std::string, SoccerEntry> temp;

    if(lastName != "-1")
    {
        auto itr = m_entries_.lower_bound(lastName);    //entry not found
        if(itr == m_entries_.end())
            return 0;

        for(itr; itr != m_entries_.end(); ++itr)
        {
            std::string substrName = itr->second.lastName.substr(0,lastName.size());
            if(substrName == lastName)
            {
                temp.insert({itr->first, itr->second});
            }
        }
    }
    else
    {
        temp = m_entries_;   ///will this create deep copy or shallow copy?
    }
    search_results_ = temp;

        if(firstName != "-1")
        {
            temp.clear();
            for(auto itr = search_results_.begin(); itr != search_results_.end(); ++itr)
            {
                if(itr->second.firstName == firstName)
                {
                    temp.insert(*itr);

                }
            }

        }

    search_results_ = temp;

        if(yob != -1)
        {
            temp.clear();
            for(auto itr = search_results_.begin(); itr != search_results_.end(); ++itr)
            {
                if(itr->second.yob == yob)
                {
                    temp.insert(*itr);
                }
            }
        }

    search_results_ = temp;

        if(status != -1)
        {
            temp.clear();
            bool boolStatus;
            if(status == 0)
                boolStatus = false;
            else if(status == 1)
                boolStatus = true;
            else
                return 0;

            for(auto itr = search_results_.begin(); itr != search_results_.end(); ++itr)
            {
                if((itr->second).status == boolStatus)
                {
                    temp.insert(*itr);
                }
            }
        }

    search_results_ = temp;

        if(category != -1)
        {
            temp.clear();
            for(auto itr = search_results_.begin(); itr != search_results_.end(); ++itr)
            {
                if((itr->second).category == category)
                {
                    temp.insert(*itr);
                }
            }
        }

    search_results_ = temp;

    if(search_results_.empty())
    {
        message_ = "No players matching search criteria.\n";
        return 0;
    }
    else{
        itr_search_current_entry_ = search_results_.begin();
        search_rank_location_ = 1;
        return 1;
    }
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
