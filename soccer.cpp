
// soccer.cpp

#include "soccer.h"
#include<sstream>

using namespace std;

void SoccerProg::run()
{
    entry_list_.read_file(cs_file_name);
    bool done = false;
    while (!done) {
        display_entry_and_menu();
        cout << "choice: ";
        char command;
        cin >> command;
        cin.get(); // new line char
        execute(command, done);
        cout << endl;
    }
}

void SoccerProg::search_run(bool & done){
	bool search_done = 0;
	while (!search_done) {
    	search_display_entry_and_menu();
    	cout << "choice: ";
	    char command;
        cin >> command;
        cin.get(); // new line char
        search_execute(command, search_done, done);
    	cout << endl;
	}
}

void SoccerProg::display_entry_and_menu() const {
    string long_separator(50, '-');
    string short_separator(8, '-');
    string sp(6, ' ');

    system(clear_command);

    cout << sp << entry_list_.season_ << " Season"
        << endl << long_separator << endl;

    entry_list_.display_current_entry();

    cout << long_separator << endl
         << "  next      search  edit    quit      display stats(t)\n"
         << "  previous  add     delete  print(z)  new season(r)\n"
         << short_separator << endl;

    entry_list_.show_message();

}

void SoccerProg::search_display_entry_and_menu() const {
    string long_separator(50, '-');
    string short_separator(8, '-');
    string sp(6, ' ');

    system(clear_command);

    cout << sp << entry_list_.season_ << " Season"
        << endl << long_separator << endl;

    entry_list_.search_display_current_entry();

    cout << long_separator << endl
         << "  next      edit    add        return  search\n"
         << "  previous  delete  print(z)   quit\n"
         << short_separator << endl;

    entry_list_.show_message();
}

void SoccerProg::execute(char command, bool & done)
{
    entry_list_.remove_message();
    switch (command) {
        case 'n': {
            entry_list_.move_to_next();
            break;
         }

        case 'p': {
            entry_list_.move_to_previous();
            break;
         }

        case 'e': {
            if (entry_list_.empty())
            {
                entry_list_.set_message("No players to edit.");
                return;
            }
            entry_list_.edit_current();
            break;
        }
        case 's': {

			bool found = entry_list_.find();
			if(!found)
                entry_list_.set_message("Entry not found.\n");
            else
                search_run(done);
            break;
        }
        case 'a': {
            string s;
            stringstream ss;
            cout << "first name: ";
            string first_name;
            getline(cin, first_name);
            cout << "last name: ";
            string last_name;
            getline(cin, last_name);
            last_name = entry_list_.last_name_check(last_name);

            bool valid = false;
			int new_yob;
			while(!valid)
            {
    	        cout << "year of birth: ";
        	    string yob_ss;
            	getline(cin, yob_ss);
				std::stringstream ss(yob_ss);
				ss >> new_yob;
				if(ss.eof())
					valid = true;
			}

            valid = false;
            bool new_status;
			while(!valid)
            {
                cout << "registration status, 1 for paid and 0 for unpaid: ";
        	    string status_ss;
            	getline(cin, status_ss);
				std::stringstream ss(status_ss);
				ss >> new_status;
				if(ss.eof())
					valid = true;
			}

            entry_list_.add(first_name, last_name, new_yob, new_status);
            break;
        }
        case 'd': {
            if (entry_list_.empty())
            {
                entry_list_.set_message("No players to delete.");
                return;
            }
            cout << "Are you sure you want to delete this player? (y/n) ";
            char choice;
            cin >> choice;
            if(choice == 'Y' || choice == 'y')
                entry_list_.delete_player();
            break;

        }
		case 'z': {
		    string printFilename;
		    cout << "Enter file name to save information to:";
		    cin >> printFilename;
		    entry_list_.print_to_file(printFilename);
		    entry_list_.set_message(("Saved to " + printFilename));

			break;
		}
		case 't': {
            entry_list_.disp_stats();
			break;
		}
		case 'r': {
            int year;
            char choice;
            bool valid = false;
		    cout << "Enter year of the new season: ";
			while(!valid){
        	    string year_ss;
            	getline(cin, year_ss);
				std::stringstream ss(year_ss);
				ss >> year;
				if(ss.eof())
					valid = true;
                else
                    cout << "   Please re-enter year: ";
			}

		    cout << "Are you sure you want to proceed? (y/n)\n";
		    cin >> choice;

		    if(choice == 'Y' || choice == 'y')
                entry_list_.new_season(year);
            else
                break;
			break;
		}
        case 'q': {
            entry_list_.write_file(cs_file_name);
            done = true;
            break;
        }
        default:
        {
            entry_list_.set_message("Command not recognized.");
            break;
        }
    }
}

///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&      SEARCH     &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&///

void SoccerProg::search_execute(char command, bool & done, bool & really_done)
{
    entry_list_.remove_message();
    switch (command) {
        case 'n': {
            entry_list_.next_search();
            break;
         }
        case 'p': {
            entry_list_.previous_search();
            break;
         }
        case 'e': {
            if (entry_list_.empty()||entry_list_.no_searches())
            {
                entry_list_.set_message("No players to edit.");
                return;
            }
            entry_list_.edit_current();
            break;
        }
        case 'a': {
            cout << "first name: ";
            string first_name;
            getline(cin, first_name);
            cout << "last name: ";
            string last_name;
            getline(cin, last_name);
            last_name = entry_list_.last_name_check(last_name);


                        bool valid = false;
			int new_yob;
			while(!valid)
            {
    	        cout << "year of birth: ";
        	    string yob_ss;
            	getline(cin, yob_ss);
				std::stringstream ss(yob_ss);
				ss >> new_yob;
				if(ss.eof())
					valid = true;
			}

            valid = false;
            bool new_status;
			while(!valid)
            {
                cout << "registration status, 1 for paid and 0 for unpaid: ";
        	    string status_ss;
            	getline(cin, status_ss);
				std::stringstream ss(status_ss);
				ss >> new_status;
				if(ss.eof())
					valid = true;
			}
            entry_list_.add(first_name, last_name, new_yob, new_status);
            entry_list_.add_search();
            break;
        }
        case 'd': {
            if (entry_list_.empty() || entry_list_.no_searches() )
            {
                entry_list_.set_message("No players to delete.");
                return;
            }
            cout << "Are you sure you want to delete this player? (y/n) ";
            char choice;
            cin >> choice;
            if(choice == 'Y' || choice == 'y')
                entry_list_.full_delete();
            break;
        }
		case 'z': {

		    if(entry_list_.no_searches())
            {
                entry_list_.set_message("No results to print.");
                break;
            }
            string printFilename;
		    cout << "Enter file name to save information to:";
		    cin >> printFilename;
            entry_list_.print_searches(printFilename);
            entry_list_.set_message(("Search results printed to: " + printFilename));
			break;
		}
		case 'r': {
		    if(entry_list_.no_searches() == 0)
                entry_list_.clear_searches();
            done = true;
			return;
		}
        case 'q': {
            entry_list_.write_file(cs_file_name);
            done = true;
			really_done = true;
            break;
        }
        case 's': {

			bool found = entry_list_.find();

			if(!found)
                entry_list_.set_message("Entry not found.\n");
            break;
        }
        default:
        {
            entry_list_.set_message("Command not recognized.");
            break;
        }
    }
}

