#include "Application.h"

namespace Application
{
	inline int Main()
	{
		Application application;
		application.Run();

		return 0;
	}
}

#ifdef WINDOWS_PLATFORM
	#ifdef DEBUG_MODE
	int main()
	{
		return Application::Main();
	}
	#else
	int WinMain()
	{
		return Application::Main();
	}
	#endif
#endif