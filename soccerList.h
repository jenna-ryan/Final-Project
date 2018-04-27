
// soccerList.h

#include <iostream>
#include <map>
#include <string>

#include "soccerEntry.h"

class SoccerList
{
public:
    SoccerList() : itr_current_entry_(m_entries_.end()) {}

    void display_current_entry() const;
    void move_to_next();
    void move_to_previous();
    void add(const std::string & firstName, const std::string & lastName, int yob, bool status);
    void delete_player();
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
    int rank_location_ = 1;
    std::map<std::string, PhoneBookEntry> search_results_;
};

inline void SoccerList::delete_player()
{
    if( m_entries_.empty())
        return;
    auto toDel = itr_current_entry_;
    move_to_previous();
    m_entries_.erase(toDel);
}

inline void SoccerList::add(const std::string & firstName, const std::string & lastName, int yob, bool status)
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

inline void SoccerList::display_current_entry() const
{
    if (m_entries_.empty())
        return;
    std::cout << itr_current_entry_->second;
    std::cout << "      Player " << rank_location_ << " of " << m_entries_.size() << std::endl;
}

inline void SoccerList::move_to_next()
{
    if (m_entries_.empty())
        return;
    ++itr_current_entry_;
    if (itr_current_entry_ == m_entries_.end())
        itr_current_entry_ = m_entries_.begin();
    ++rank_location_;
    if(rank_location_ > m_entries_.size())
        rank_location_ = 1;
}

inline void SoccerList::move_to_previous()
{
    if (m_entries_.empty())
        return;
    --itr_current_entry_;
    if (itr_current_entry_ == --m_entries_.begin())
        itr_current_entry_ = --m_entries_.end();
    --rank_location_;
    if(rank_location_ == 0)
        rank_location_ = m_entries_.size();
}


inline void SoccerList::edit_current()
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
