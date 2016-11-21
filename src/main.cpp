#include "engine/application.h"


int main(int argc, char **argv){

	Application a("./XML/configuration.xml");
	
	a.run();
	
	return 0;
}

