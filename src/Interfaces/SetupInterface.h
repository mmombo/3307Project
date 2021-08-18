#ifndef SETUP_INTERFACE_H
#define SETUP_INTERFACE_H

#include <string>
#include "../Login/Login.h"

class SetupInterface {
	private:
		Login *login;
	public:
		SetupInterface();
		SetupInterface(Login *login);
		~SetupInterface();
		void SetupPrompt();
	};

#endif
