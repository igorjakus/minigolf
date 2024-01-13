// A set of useful development utilities

namespace util {

// ========================== float ==========================

inline float clamp(float value, float min, float max) {
	const float temp = value < min ? min : value;
	return temp > max ? max : temp;
}

inline float lerp(float startVal, float endVal, float param) {
	return startVal + param * (endVal - startVal); 
}

inline float clerp(float startVal, float endVal, float param) {
	return startVal + clamp(param, 0, 1) * (endVal - startVal); 
}

inline float norm(float startVal, float endVal, float value) {
	const float diff = endVal - startVal;
	if(diff == 0) [[unlikely]] {
		return 0;
	}
	return (value - startVal) / diff;
}

inline float cnorm(float startVal, float endVal, float value) {
	const float diff = endVal - startVal;
	if(diff == 0) [[unlikely]] {
		return 0;
	}
	return clamp((value - startVal) / diff, 0, 1);
}

// ========================== double ==========================

inline double clamp(double value, double min, double max) {
	const double temp = value < min ? min : value;
	return temp > max ? max : temp;
}

inline double lerp(double startVal, double endVal, double param) {
	return startVal + param * (endVal - startVal); 
}

inline double clerp(double startVal, double endVal, double param) {
	return startVal + clamp(param, 0, 1) * (endVal - startVal); 
}

inline double norm(double startVal, double endVal, double value) {
	const double diff = endVal - startVal;
	if(diff == 0) [[unlikely]] {
		return 0;
	}
	return (value - startVal) / diff;
}

inline double cnorm(double startVal, double endVal, double value) {
	const double diff = endVal - startVal;
	if(diff == 0) [[unlikely]] {
		return 0;
	}
	return clamp((value - startVal) / diff, 0, 1);
}

}
