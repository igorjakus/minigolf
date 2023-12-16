#include "App.h"

#include <Agl.h>

auto main() -> int {

	#ifdef __DIST__
		dtl::Log.settings(DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_PROGRAM_TIME, DTL_FILE);
		dtl::Log.setFile("Log_error.txt");
	#endif

	agl::Init();

	golf::App application;
	application.run();

	agl::Terminate();

	return EXIT_SUCCESS;

}
