#include "MessageBoard.h"

MessageBoard::MessageBoard()
{
}

MessageBoard::~MessageBoard()
{
}

void MessageBoard::Add_message(string message)
{
    if (MessageHistory.size() == 5)
    {
        vector<std::string>::iterator it = MessageHistory.begin();
        MessageHistory.erase(it);
    }
    MessageHistory.push_back(message);
}