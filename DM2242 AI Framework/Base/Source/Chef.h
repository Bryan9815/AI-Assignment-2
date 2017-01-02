#ifndef CHEF_H
#define CHEF_H

#include "BaseEntity.h"
#include "SingletonTemplate.h"

class Chef : public BaseEntity, Singleton<Chef>
{
public:
    Chef();
    ~Chef();

    void Init();
    void Update();
private:

};



#endif