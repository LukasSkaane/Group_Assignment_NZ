#include <typeinfo>

#include "Structures.h"
#include "Introduction.h"
#include "Menu.h"
#include "StorageHandling.h"
#include "Registration.h"

using namespace std;

template<class T>
int getUserPermissions(T);

template<class T>
int main()
{
	T user;
	introduction();
	int permissions = getUserPermissions(user);
	int choice = getMenuChoice();


	return 0;
}

template<class T>
int getUserPermissions(T) {

}