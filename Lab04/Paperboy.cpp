#include "PaperBoy.h"

PaperBoy::PaperBoy(vec3 position)
{
	paperboy = Model("D:\\Personal\\College\\5thYear\\ComputerGraphics\\Models\\Bike.obj");
	Pos = position;
	MovementSpeed = 5.0f;
	Front = vec3(1.0f, 0.0f, 0.0f);
	Right = vec3(0.0f, 0.0f, 1.0f);
}

PaperBoy::PaperBoy()
{
}

void PaperBoy::renderPaperBoy(mat4 pos, int shaderID) {

	//Transform the PaperBoy
	mat4 paperboy_pos = identity_mat4();
	paperboy_pos = translate(paperboy_pos, vec3(0.0f, 0.0f, 0.0f));
	paperboy_pos = rotate_y_deg(paperboy_pos, Yaw);
	paperboy_pos = translate(paperboy_pos, Pos);

	int world_loc = glGetUniformLocation(shaderID, "world");
	glUniformMatrix4fv(world_loc, 1, GL_FALSE, paperboy_pos.m);
	
	
	for (int i = 0; i < paperboy.getNumberMeshes(); i++) {
		paperboy.RenderMesh(paperboy_pos, shaderID, i);
	}
}

void PaperBoy::ProcessKeyboard(MovementDir direction, float deltaTime)
{
	float speed = MovementSpeed * deltaTime;
	if (direction == FORWARD)Pos += Front * speed;
	if (direction == BACKWARD)Pos -= Front * speed;
	if (direction == LEFT) {
		Yaw += 20.0f * speed;
	}
	if (direction == RIGHT) {
		Yaw -= 20.0f * speed;
	}
	updatePaperBoyVectors();
}

void PaperBoy::MovePaperBoy(int x, int y, float deltaTime) {

	float speed = MovementSpeed * deltaTime;
	Pos += Front * speed;
	if (x == 1)Yaw += 20.0f * speed;
	if (x == -1)Yaw -= 20.0f * speed;
	updatePaperBoyVectors();

}

mat4 PaperBoy::GetViewMatrix()
{
	return look_at(Pos, Pos + Front, Up);
}

void PaperBoy::updatePaperBoyVectors()
{
	vec3 front;
	front.v[0] = cos(convert(-Yaw)) * cos(convert(Pitch));
	front.v[1] = sin(convert(Pitch));
	front.v[2] = sin(convert(-Yaw)) * cos(convert(Pitch));

	Front = normalise(front);
	Right = normalise(cross(Front, WorldUp));
	Up = normalise(cross(Right, Front));
}

void PaperBoy::throwPapers(Model paper, Shader myShader, int remainingPapers) {
	std::cout << "Throwing Papers, papers remaining: " << remainingPapers << '\n';
	if (remainingPapers > 0) {
		mat4 paper_mat = identity_mat4();
		paper_mat = translate(paper_mat, vec3(0.0, 0.0, 0.0));
		std::cout << "If statement Reached" << '\n';
		paper.RenderModel(paper_mat, myShader.ID);
		std::cout << "Model Rendered: " << '\n';
		this->remainingPapers--;
	}
}