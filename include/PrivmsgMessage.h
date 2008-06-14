#ifndef PRIVMSGMESSAGE_H
#define PRIVMSGMESSAGE_H

#define PRIVMSGMESSAGE_COMMAND "PRIVMSG"
#define PRIVMSGMESSAGE_FRIENDLY "say"
#define PRIVMSGMESSAGE_MINPARAMS 2
#define PRIVMSGMESSAGE_MAXPARAMS 2

#include <iostream> // DEBUG ONLY
#include <string>
#include <vector>

#include "IRCMessage.h"

using namespace std;

class PrivmsgMessage : public IRCMessage {
private:
    string			_raw;
    vector<string> 		_params;
    vector<string>		_receivers;
    User*			_user;
    
    void			_init();
    
public:
    
    PrivmsgMessage(string raw);
    ~PrivmsgMessage();
    
    string 			translate();
    const string 		prefix();
    const vector<string> 	params();
    const vector<string>	receivers();
    void 			setUser(User* user);
    void			addReceiver(string rcv);
    bool 			transmit(IRCConnection* conn);
    
    const string 		command();
    const string 		friendly();
    const unsigned int 		minParams();
};

typedef PrivmsgMessage* create_privmsgmessage_t(string raw);
typedef void destroy_privmsgmessage_t(PrivmsgMessage*);

#endif
