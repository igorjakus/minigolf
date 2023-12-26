#include "App.h"

#include "AglWrap.h"

int main() {

	#ifdef __DIST__
		dtl::Log.settings(DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_PROGRAM_TIME, DTL_FILE);
		dtl::Log.setFile("Log_error.txt");
	#endif

	golf::AglWrap::init();

	golf::App application;
	application.run();

	return EXIT_SUCCESS;
}
