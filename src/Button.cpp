#include "Button.hpp"

Button::Button(Vector3 position, Vector2 scale, Sprite sprite, void (*func)())
    : mesh()
{
    Vector3 pos[] = {
		Vector3(-scale.x, -scale.y, 0.0f) + position,
		Vector3( scale.x, -scale.y, 0.0f) + position,
		Vector3( scale.x,  scale.y, 0.0f) + position,
		Vector3(-scale.x,  scale.y, 0.0f) + position
	};

	Vector2 uv[] = {
		Vector2(0.0f, 0.0f) * sprite.uvEnd + sprite.uvStart,
		Vector2(1.0f, 0.0f) * sprite.uvEnd + sprite.uvStart,
		Vector2(1.0f, 1.0f) * sprite.uvEnd + sprite.uvStart,
		Vector2(0.0f, 1.0f) * sprite.uvEnd + sprite.uvStart
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

    material = Material(
        Shader::spriteShader, 
        sprite.atlasTexture,
        Vector4(1.0f, 1.0f, 1.0f, 1.0f)
    );

    mesh.SetCustomMesh( pos, uv, 4, indices, 6, &material);

    callback = func;
}

Button::~Button()
{

}

void Button::Update()
{
    if(Input::GetMouseButtonDown(0) && MousePositionInCollider())
    {
        callback();
    }
}

void Button::Draw()
{
    Renderer::DrawMesh(mesh);
}

bool Button::MousePositionInCollider()
{
    Vector2 A = (Vector2)this->mesh.vertices[0];
    Vector2 B = (Vector2)this->mesh.vertices[2];

    return  Input::mouseWorldPosition.x < B.x &&
            Input::mouseWorldPosition.x > A.x &&
            Input::mouseWorldPosition.y < B.y &&
            Input::mouseWorldPosition.y > A.y;
}
