// AglWrap.h
// 
// Wrapper for AGL library to make sure it is properly terminated after termination of all application systems.

namespace golf {

	class AglWrap {

	public:
		static AglWrap& init();

		AglWrap(AglWrap&&) = delete;
		AglWrap(const AglWrap&) = delete;
		AglWrap& operator=(AglWrap&&) = delete;
		AglWrap& operator=(const AglWrap&) = delete;

	private:
		AglWrap();
		~AglWrap();

	};

}