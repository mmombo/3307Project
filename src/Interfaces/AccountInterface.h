#ifndef ACCOUNT_INTERFACE_H
#define ACCOUNT_INTERFACE_H

#include "../Login/Member.h"
class AccountInterface
{
private:
    Member *currentMember;

public:
    AccountInterface();
    AccountInterface(Member *member);
    ~AccountInterface();
    void setCurrentMember(Member *member);
    void addCurrencyPrompt();
    void printAccountInfo();
};
#endif
