#include <Agl.h>

#include "App.h"

static const bool cleanupRegister = (atexit(agl::Terminate) == 0);

int main() {

#ifdef __DIST__
	dtl::Log.settings(DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_PROGRAM_TIME, DTL_FILE);
	dtl::Log.setFile("Log_error.txt");
#endif

	agl::Init();

	golf::App application;
	application.run();

	return EXIT_SUCCESS;
}
