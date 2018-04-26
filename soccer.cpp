
// soccer.cpp

#include "soccer.h"

using namespace std;

void PhoneBook::run()
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

void PhoneBook::search_run(bool & done){
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

void PhoneBook::display_entry_and_menu() const {
    string long_separator(50, '-');
    string short_separator(8, '-');

    system(clear_command);

    entry_list_.display_current_entry();

    cout << long_separator << endl
         << "  next      search  edit    quit      display stats(t)\n"
         << "  previous  add     delete  print(z)  new season(r)\n"
         << short_separator << endl;
}

void PhoneBook::search_display_entry_and_menu() const {
    string long_separator(50, '-');
    string short_separator(8, '-');

    system(clear_command);

    entry_list_.display_current_entry();

    cout << long_separator << endl
         << "  next      edit    add        return\n"
         << "  previous  delete  print(z)   quit\n"
         << short_separator << endl;
}

void PhoneBook::execute(char command, bool & done)
{
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
                return;
            entry_list_.edit_current();
            break;
        }
        case 's': {
            cout << "Enter '*' to leave field unsearched" << std::endl;
            cout << "last name: ";
            string lastName;
            getline(cin, lastName);
			cout << "Enter '*' to leave field unsearched" << std::endl;
            cout << "first name: ";
            string firstName;
            getline(cin, firstName);
			cout << "Enter '*' to leave field unsearched" << std::endl;
            cout << "payment status(paid or unpaid): ";
            string status;
            getline(cin, status);
			bool valid = false;
			int yob;
			while(!valid){
				cout << "Enter '-1' to leave field unsearched" << std::endl;
    	        cout << "year of birth: ";
        	    string yob_ss;
            	getline(cin, yob_ss);
				std::stringstream ss(yob_ss);
				ss >> yob;
				if(ss.eof())
					valid = true;
			}
			cout << "Enter '-1' to leave field unsearched" << std::endl;
            cout << "category: U";
            int category;
			std::cin >> category;
			if(lastName != "*"){
	            if(entry_list_.find(lastName, 1))
					search_run(done);
				break;
			}
			if(firstName != "*"){
	            if(entry_list_.find(firstName, 2))
					search_run(done);
				break;
			}
			if(status != "*"){
	            if(entry_list_.find(status, 3))
					search_run(done);
				break;
			}
			if(yob != -1){
	            if(entry_list_.find(yob, 1))
					search_run(done);
				break;
			}
			if(category != -1){
	            if(entry_list_.find(category, 2))
					search_run(done);
				break;
			}
            break;
        }
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&///
        case 'a': {
            cout << "first name: ";
            string first_name;
            getline(cin, first_name);
            cout << "last name: ";
            string last_name;
            getline(cin, last_name);
            cout << "year of birth: ";
            int new_yob;
            cin >> new_yob;
            cout << "registration status, 1 for paid and 0 for unpaid: ";
            bool new_status;
            cin >> new_status;
            entry_list_.add(first_name, last_name, new_yob, new_status);
            break;
        }
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&///
        case 'd': {
            cout << "Enter the last name: ";
            string last_name;
            getline(cin, last_name);
            cout << "Enter the first name: ";
            string first_name;
            getline(cin, first_name);
 //           cout << "Are you sure? y for yes and n for no: ";
   //         char choice;

                entry_list_.delete_(last_name, first_name);
                break;

        }
		case 'z': {
		    string printFilename;
		    cout << "Enter file name to save information to:";
		    cin >> printFilename;
		    entry_list_.print_to_file(printFilename);

			break;
		}
		case 't': {
            entry_list_.disp_stats();
			break;
		}
		case 'r': {
            int year;
		    cout << "The year of the new season: ";
		    cin >> year;
// not finished
			break;
		}
        case 'q': {
            entry_list_.write_file(cs_file_name);
            done = true;
            break;
        }
    }
}

void PhoneBook::search_execute(char command, bool & done, bool & really_done)
{
    switch (command) {
        case 'n': {
            entry_list_.move_to_next();
            break;
         }
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&///
        case 'p': {
            entry_list_.move_to_previous();
            break;
         }
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&///
        case 'e': {
            if (entry_list_.empty())
                return;
            entry_list_.edit_current();
            break;
        }
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&///
        case 'a': {
            cout << "first name: ";
            string first_name;
            getline(cin, first_name);
            cout << "last name: ";
            string last_name;
            getline(cin, last_name);
            cout << "year of birth: ";
            int new_yob;
            cin >> new_yob;
            cout << "registration status, paid for 1 and unpaid for 0: ";
            bool new_status;
            cin >> new_status;
            entry_list_.add(first_name, last_name, new_yob, new_status);
            break;
        }
///&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&///
        case 'd': {
            // Not yet implemented
            break;
        }
		case 'z': {

            string printFilename;
		    cout << "Enter file name to save information to:";
		    cin >> printFilename;
            entry_list_.print_searches(printFilename);
			break;
		}
		case 'r': {

			done = true;
			break;
		}
        case 'q': {
            entry_list_.write_file(cs_file_name);
            done = true;
			really_done = true;
            break;
        }
    }
}

