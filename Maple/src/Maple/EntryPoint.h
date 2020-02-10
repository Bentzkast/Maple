#pragma once

#ifdef MP_PLATFORM_WINDOWS

extern Maple::Application* Maple::CreateApplication();

// WIN MAIN here
	int main() {

		auto app = Maple::CreateApplication();
		app->Run();
		delete app;
	}


#endif // MP_PLATFORM_WINDOWS

