#include "PingMessage.h"
#include "StringTokenizer.h"

/* Constructor */
PingMessage::PingMessage(string raw){
    _raw = raw;
    _init();
}

/* Destructor */
PingMessage::~PingMessage(){}

/* Initializes the message */
void PingMessage::_init(){
    
    /* Check if the message even has content */
    if(_raw.empty()){
	throw string("Illegal message.");
    }
    
    StringTokenizer st(_raw, ' ');
    string _tmp;
    
    if(st.count() < (PINGMESSAGE_MINPARAMS +1) || st.count() > (PINGMESSAGE_MAXPARAMS +1) ){
	throw string("Wrong parameter count in message ") + _raw;
    }
    
    /* Check if the message really is a user message */
    if(string(st.next()).substr(1) != PINGMESSAGE_COMMAND){
	throw string("Not a ") + string(PINGMESSAGE_COMMAND) + string(" message: ") + _raw;
    }
    
    /* Read the parameters */
    for(int i = 0; st.hasNext(); i++){
	_params.push_back(string(st.next()));
    }
}

/* Translate the message to an RFC string */
string PingMessage::translate(){
    
    string _tmp;
    _tmp.append(PINGMESSAGE_COMMAND);

    for(int i = 0; i < _params.size(); i++){
	_tmp.append(SPACE);
	_tmp.append(_params.at(i));
    }
    
    _tmp.append(CRLF);
    return _tmp;    
}

/* Return the prefix */
string PingMessage::prefix(){
    // NOT IMPLEMENTED
    return "";
}

/* Return the parameters of this message */
vector<string> PingMessage::params(){
    return _params;
}

/* Sets the user that sends this message */
void PingMessage::setUser(User* user){
    _user = user;
}

/* Transmits the message to the server */
bool PingMessage::transmit(IRCConnection* conn){
    if(conn == 0 || ! conn->connected()){
	throw "Not connected!";
    }
    return conn->sendMessage(translate());
}

/* Returns the command */
string PingMessage::command(){
    return PINGMESSAGE_COMMAND;
}

/* Returns the minimum amount of parameters needed */
unsigned int PingMessage::minParams(){
    return PINGMESSAGE_MINPARAMS;
}

////////////////////////////////////////////////////////////////////////////////
//			   CLASS FACTORY METHODS			      //
////////////////////////////////////////////////////////////////////////////////

extern "C" PingMessage* create_pingmessage(string raw){
    return new PingMessage(raw);
}

extern "C" void destroy_pingmessage(PingMessage* message){
    delete message;
}
