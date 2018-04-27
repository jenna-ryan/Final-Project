
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
    void search_display_current_entry() const;
    void move_to_next();
    void move_to_previous();
    void next_search();
    void previous_search();
    void add(const std::string & firstName, const std::string & lastName, int yob, bool status);
    void delete_player();
    void full_delete();
    void edit_current();
    bool find();
    bool empty() const { return m_entries_.empty(); }
    void read_file(const std::string & file_name);
    void write_file(const std::string & file_name) const;
    void print_to_file(const std::string & file_name) const;
    void print_searches(const std::string & file_name) const;
    void disp_stats();
    int compute_category(int yob);
    void new_season(int year);
    void clear_searches();
    std::string last_name_check(const std::string & ln);
    void add_search();
    void show_message() const;
    void remove_message() {message_.clear();}
    void set_message(const std::string & msg) {message_ = msg;}

    int season_;

private:


    std::map<std::string, SoccerEntry> m_entries_;
    std::map<std::string, SoccerEntry>::iterator
        itr_current_entry_;
    int rank_location_ = 1;

    std::map<std::string, SoccerEntry> search_results_;
    std::map<std::string, SoccerEntry>::iterator
        itr_search_current_entry_;
    int search_rank_location_ = 1;

    std::string message_ = "";
};

inline void SoccerList::show_message() const
{
    if(message_.empty())
        return;
    std::cout << message_ << std::endl;
}

inline void SoccerList::new_season(int year)
{
    m_entries_.clear();
    season_ = year;
}

inline void SoccerList::clear_searches()
{
    search_rank_location_ = 1;
    search_results_.clear();
    itr_search_current_entry_ = search_results_.begin();
}


inline void SoccerList::delete_player()
{
    if( m_entries_.empty())
        return;
    auto toDel = itr_current_entry_;
    move_to_previous();
    m_entries_.erase(toDel);
    --rank_location_;
}

inline void SoccerList::full_delete()
{
    if( m_entries_.empty() || search_results_.empty())
        return;
    auto toDel = itr_current_entry_;
    move_to_previous();
    m_entries_.erase(toDel);
    --rank_location_;

    toDel = itr_search_current_entry_;
    previous_search();
    search_results_.erase(toDel);
    --search_rank_location_;
}

inline void SoccerList::add(const std::string & firstName, const std::string & lastName, int yob, bool status)
{
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
        m_entries_.insert({lastName, SoccerEntry(firstName, lastName, yob, status, category)});
    itr_current_entry_ = result.first;

    rank_location_ = distance(m_entries_.begin(),itr_current_entry_) + 1;

}

inline void SoccerList::add_search()
{
    auto result = search_results_.insert({itr_current_entry_->first,itr_current_entry_->second});

    itr_search_current_entry_ = result.first;

    search_rank_location_ = distance(search_results_.begin(),itr_search_current_entry_) + 1;
}

inline void SoccerList::display_current_entry() const
{
    if (m_entries_.empty())
        return;
    std::cout << itr_current_entry_->second;
    std::cout << std::endl << "    Player "
         << rank_location_ << " of " << m_entries_.size() << std::endl;
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

///%%%%%%%%% SEARCH

inline void SoccerList::next_search()
{
    if (search_results_.empty())
        return;
    ++itr_search_current_entry_;
    if (itr_search_current_entry_ == search_results_.end())
        itr_search_current_entry_ = search_results_.begin();
    ++search_rank_location_;
    if(search_rank_location_ > search_results_.size())
        search_rank_location_ = 1;

    auto loc = m_entries_.find(itr_search_current_entry_->first);
    itr_current_entry_ = loc;
    rank_location_ = distance(m_entries_.begin(),itr_current_entry_) + 1;
}

inline void SoccerList::previous_search()
{
    if (search_results_.empty())
        return;

    if(search_results_.size() == 2)
    {
        if(itr_search_current_entry_ == search_results_.begin())
       {
            itr_search_current_entry_ = --search_results_.end();
            search_rank_location_ = 2;
       }
       else
       {
            itr_search_current_entry_ = search_results_.begin();
            search_rank_location_ = 1;
       }
    }
    else
    {
        --itr_search_current_entry_;
        if (itr_search_current_entry_ == --search_results_.begin())
            itr_search_current_entry_ = --search_results_.end();
        --search_rank_location_;
        if(search_rank_location_ == 0)
            search_rank_location_ = search_results_.size();
    }

    auto loc = m_entries_.find(itr_search_current_entry_->first);
    itr_current_entry_ = loc;
    rank_location_ = distance(m_entries_.begin(),itr_current_entry_) + 1;

}
/// end SEARCH


inline void SoccerList::search_display_current_entry() const
{
    if (search_results_.empty())
        return;
    std::string s = " players found";
    if (search_results_.size() == 1)
        s = " player found";
    std::cout << itr_search_current_entry_->second;
    std::cout << std::endl << "    Showing "
         << search_rank_location_ << " of " <<
         search_results_.size() << s  << std::endl;
}





