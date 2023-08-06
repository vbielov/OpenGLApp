#include <iostream>
#include "Window.hpp"
#include "Renderer.hpp"
#include "LineRenderer.hpp"
#include "Texture.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "Player.hpp"

int main()
{
	Window window = Window(640, 640, "OpenGLApp");
	Renderer renderer = Renderer();
	LineRenderer lineRenderer = LineRenderer();
	
	Texture::player = new Texture("/home/user/Desktop/dev/OpenGLApp/res/slime.png");
	Texture::menuButton = new Texture("/home/user/Desktop/dev/OpenGLApp/res/blue_button.png");
	Shader::spriteShader = new Shader("/home/user/Desktop/dev/OpenGLApp/res/spriteShader.glsl");

	Scene menuLevel = Scene();
	Scene mainLevel = Scene();
	Scene::menuLevel = &menuLevel;
	Scene::mainLevel = &mainLevel;

	Scene::Load(Scene::menuLevel);

	Button button = Button(
		Vector3(0, 0, 0), 
		Vector2(1.0f, 0.25f), 
		Sprite(
			Texture::menuButton,
			Vector2(0, 0),
			Vector2(1, 1)
		),
		[]() -> void {
			std::cout << "Sure it's clicked!" << std::endl;
			Scene::Load(Scene::mainLevel);
		}
	);
	Scene::menuLevel->Instantiate(&button);

	Player player = Player(
		Vector3(0, 0, 0),
		Vector2(0.25f, 0.25f),
		Sprite(
			Texture::player,
			Vector2(0, 0),
			Vector2(1, 1)
		)
	);
	Scene::mainLevel->Instantiate(&player);
	
	
	while(window.IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.6f, 1.0f);
		
		Scene::currentScene->UpdateGameLoop();

		Renderer::DrawCall();
		LineRenderer::DrawCall();
	}

	delete Texture::menuButton;
	delete Shader::spriteShader;
	
	return 0;
}