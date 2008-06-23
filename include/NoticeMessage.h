#ifndef NOTICEMESSAGE_H
#define NOTICEMESSAGE_H

#define NOTICEMESSAGE_COMMAND "NOTICE"
#define NOTICEMESSAGE_MINPARAMS 2
#define NOTICEMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class NoticeMessage : public IRCMessage {
private:
    string		_raw;
    vector<string> 	_params;
    User*		_user;
    
    void		_init();
    
public:
    
    NoticeMessage(string raw);
    ~NoticeMessage();
    
    string 		translate();
    string 		prefix();
    vector<string> 	params();
    void 		setUser(User* user);
    bool 		transmit(IRCConnection* conn);
    
    string 		command();
    unsigned int 	minParams();
};

typedef NoticeMessage* create_noticemessage_t(string raw);
typedef void destroy_noticemessage_t(NoticeMessage*);

#endif
