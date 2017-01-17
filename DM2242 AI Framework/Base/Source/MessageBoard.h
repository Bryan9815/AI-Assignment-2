#ifndef MESSAGE_BOARD_H
#define MESSAGE_BOARD_H
#include "SingletonTemplate.h"
#include <vector>
#include <string>
using namespace std;
class MessageBoard : public Singleton<MessageBoard>
{
public:
    MessageBoard();
    ~MessageBoard();

    void Add_message(string message);
    vector<std::string> MessageHistory;
private:
    
};

#endif