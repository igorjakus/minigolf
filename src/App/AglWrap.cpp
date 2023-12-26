#include "AglWrap.h"

#include <Agl.h>

namespace golf {

AglWrap::AglWrap() {
	agl::Init();
}

AglWrap::~AglWrap() {
	agl::Terminate();
}

AglWrap& AglWrap::init() {
	static AglWrap instance;
	return instance;
}

}