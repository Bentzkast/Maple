#include <Maple.h>

class Game : public Maple::Application
{
public:
	Game(){
	}


	~Game() {

	}
};

Maple::Application* Maple::CreateApplication() {
	return new Game();
}