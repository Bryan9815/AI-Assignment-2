#ifndef CASHIER_H
#define CASHIER_H

#include "BaseEntity.h"
#include "SingletonTemplate.h"

class Cashier : public BaseEntity, Singleton<Cashier>
{
public:
    Cashier();
    ~Cashier();

    void Init();
    void Update();
private:

};



#endif