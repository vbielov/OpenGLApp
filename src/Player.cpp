#include "Player.hpp"

Player::Player(Vector3 position, Vector2 scale, Sprite sprite)
	: position(position)
{   
	material = Material(
        Shader::spriteShader, 
        sprite.atlasTexture,
        Vector4(1.0f, 1.0f, 1.0f, 1.0f)
    );

    mesh.SetQuadMesh(&material);
	mesh.SetScale(Vector2(0.25f, 0.25f));
	mesh.SetPosition(Vector2(2.0f, 0.25f));
}

Player::~Player()
{

}

void Player::Update()
{
	const float speed = 5.0f;
    if(Input::GetKeyDown(GLFW_KEY_D))
		position.x += speed * Window::deltaTime;
	if(Input::GetKeyDown(GLFW_KEY_A))
		position.x -= speed * Window::deltaTime;
	mesh.SetPosition(position);
}

void Player::Draw()
{
    Renderer::DrawMesh(mesh);


	Vector3 lineColor = Vector3(0,1,0);
	for(int i = 0; i < mesh.vertexCount; i++)
	{
		if(i == 0)
		{
			LineRenderer::DrawLine(
				LineVertex { (Vector2)mesh.vertexData[i].pos, lineColor },
				LineVertex { (Vector2)mesh.vertexData[mesh.vertexCount - 1].pos, lineColor }
			);
		}
		else
		{
			LineRenderer::DrawLine(
				LineVertex { (Vector2)mesh.vertexData[i].pos, lineColor },
				LineVertex { (Vector2)mesh.vertexData[i - 1].pos, lineColor }
			);
		}
	}
}
