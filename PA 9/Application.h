#pragma once
#include "FrameListenable.hpp"

class Application {
	FrameListenable* game;
	FrameListenable* menu;
	FrameListenable* runnable = menu;
	static Application* instance;
public:

	Application(FrameListenable* g, FrameListenable* m) : game(g), menu(m) {}
	~Application() {
		delete game;
		delete menu;
	}

	void runGame() {
		runnable = game;
	}

	void runMenu() {
		runnable = menu;
	}

	static void setInstance(Application* app) {
		instance = app;
	}

	//Application::getInstance().runGame();
	static Application& getInstance() {
		return *instance;
	}

	FrameListenable* getRunnable() {
		return runnable;
	}

	FrameListenable* getGame() {
		return game;
	}

};
