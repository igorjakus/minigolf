#include <Agl.h>

#include "App.h"

int main() {

#ifdef __DIST__
	dtl::Log.settings(DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_PROGRAM_TIME, DTL_FILE);
	dtl::Log.setFile("Log_error.txt");
#endif

	atexit(agl::Terminate);

	agl::Init();

	golf::App application;
	application.run();

	return EXIT_SUCCESS;
}
