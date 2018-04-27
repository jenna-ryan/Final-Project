
// soccerList.h

#include <iostream>
#include <map>
#include <string>

#include "soccerEntry.h"

class PhoneBookList
{
public:
    PhoneBookList() : itr_current_entry_(m_entries_.end()) {}

    void display_current_entry() const;
    void move_to_next();
    void move_to_previous();
    void add(const std::string & firstName, const std::string & lastName, int yob, bool status);
    void delete_ (const std::string  & firstName, const std::string & lastName);
    void edit_current();
	bool find(const std::string & search_term, int type);
	bool find(int search_term, int type);
    bool empty() const { return m_entries_.empty(); }
    void read_file(const std::string & file_name);
    void write_file(const std::string & file_name) const;
    void print_to_file(const std::string & file_name) const;
    void print_searches(const std::string & file_name) const;
    void disp_stats();
    int compute_category(int yob);
    void new_season(int year){
        m_entries_.clear();
        season_ = year;};

private:
    std::map<std::string, PhoneBookEntry> m_entries_;
    std::map<std::string, PhoneBookEntry>::iterator
        itr_current_entry_;
    int season_;
};

inline void PhoneBookList::add(const std::string & firstName, const std::string & lastName, int yob, bool status)
{
    ///NOTE: changed cin to be yob, not category
    int category = season_-yob;
    while (category<4 || category>16)
    {
        std::cout << "Players younger than 4 or older than 16 cannot play in this summer league." << std::endl;
        std::cout << "Please reenter the year of birth: " << std::endl;
        std::cin >> yob;
        category = season_ - yob;
    }
    category = compute_category(yob);
    auto result =
        m_entries_.insert({lastName, PhoneBookEntry(firstName, lastName, yob, status, category)});
    itr_current_entry_ = result.first;
}
inline void PhoneBookList::delete_ (const std::string & firstName, const std::string & lastName)
{
    // itr_current_entry_= m_entries_.find(lastName);
    // m_entries_.erase(itr_current_entry_);
    //erase by iterator
}

inline void PhoneBookList::display_current_entry() const
{
    if (m_entries_.empty())
        return;
    std::cout << itr_current_entry_->second;
}

inline void PhoneBookList::move_to_next()
{
    if (m_entries_.empty())
        return;
    ++itr_current_entry_;
    if (itr_current_entry_ == m_entries_.end())
        itr_current_entry_ = m_entries_.begin();
}

inline void PhoneBookList::move_to_previous()
{
    if (m_entries_.empty())
        return;
    --itr_current_entry_;
    if (itr_current_entry_ == --m_entries_.begin())
        itr_current_entry_ = --m_entries_.end();
}


inline void PhoneBookList::edit_current()
{
    std::string newName;
    int newYear;
    int newStatus;

    std::cout << "To change a player's information, enter new info below\n";
    std::cout << "To leave a field unchanged, enter -1\n";

    std::cout << "Change first name? ";
    std::cin >> newName;
    if(newName!= "-1")
        (itr_current_entry_->second).firstName = newName;

    std::cout << "Change last name? ";
    std::cin >> newName;
        if(newName!= "-1")
        (itr_current_entry_->second).lastName = newName;

    std::cout << "Change birth year? ";
    std::cin >> newYear;


        if(newYear!= -1)
        {
            int category = season_ - newYear;
            while(category < 4 || category > 16)
            {
                std::cout << "Players younger than 4 or older than 16 cannot play in this summer league." << std::endl;
                std::cout << "Please reenter the year of birth: " << std::endl;
                std::cin >> newYear;
                category = season_ - newYear;
            }

            (itr_current_entry_->second).yob = newYear;
            (itr_current_entry_->second).category = category;
        }

    std::cout << "Change registration status? ";
    std::cin >> newStatus;
        if(newStatus == 1)
            (itr_current_entry_->second).status = true;
        else if (newStatus == 0)
            (itr_current_entry_->second).status = false;

}
