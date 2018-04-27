
// soccer.h

#ifndef _SoccerList_h_
#define _SoccerList_h_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "soccerList.h"

const char clear_command[] = "cls";

const char cs_file_name[] = "soccer.txt";

class SoccerProg
{
public:
    void run();
private:

    void search_run(bool & done);
    void display_entry_and_menu() const;
    void search_display_entry_and_menu() const;
    void execute(char command, bool & done);
    void search_execute(char command, bool & done, bool & really_done);
    SoccerList entry_list_;
};

#endif

