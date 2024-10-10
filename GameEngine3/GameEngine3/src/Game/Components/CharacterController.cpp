
#include <Game/Components/CharacterController.h>

#include <Engine/EntityComponent/Entity.h>
#include <Engine/Input/Inputs.h>
#include <Engine/Input/KeyCode.h>
#include <Engine/EntityComponent/TransformData.h>
#include <Engine/EntityComponent/Scene.h>

CharacterController::CharacterController(Entity* owner)
	: Component(owner)
{}

void CharacterController::BindInputs(Inputs* inputs)
{
	inputs->CreateInputAction("z", KeyCode::W)->BindPressAction([this]() { MoveZ(1.f);  });
	inputs->CreateInputAction("s", KeyCode::S)->BindPressAction([this]() { MoveZ(-1.f); });
	inputs->CreateInputAction("q", KeyCode::A)->BindPressAction([this]() { MoveX(-1.f);  });
	inputs->CreateInputAction("d", KeyCode::D)->BindPressAction([this]() { MoveX(1.f); });

	inputs->CreateInputAction("up", KeyCode::SPACE)->BindPressAction([this]() { MoveY(1.f); });
	inputs->CreateInputAction("down", KeyCode::LEFT_SHIFT)->BindPressAction([this]() { MoveY(-1.f); });

	inputs->CreateInputAction("rightRot", KeyCode::RIGHT)->BindPressAction([this]()	{ Rotate(0.f,  1.f);});
	inputs->CreateInputAction("leftRot", KeyCode::LEFT)->BindPressAction([this]()		{ Rotate(0.f, -1.f);});
	inputs->CreateInputAction("upRot", KeyCode::UP)->BindPressAction([this]()			{ Rotate(1.f,  0.f);});
	inputs->CreateInputAction("downRot", KeyCode::DOWN)->BindPressAction([this]()		{ Rotate(-1.f, 0.f);});
}

void CharacterController::MoveZ(float scale)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	glm::vec3 fwd = owner->Transform()->GetTransformForward();
	owner->Transform()->position += fwd * moveSpeed * dt * scale;
}
void CharacterController::MoveX(float scale)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	glm::vec3 fwd = owner->Transform()->GetTransformForward();
	glm::vec3 right = glm::cross(fwd, glm::vec3(0.f, 1.f, 0.f));
	owner->Transform()->position += right * moveSpeed * dt * scale;
}
void CharacterController::MoveY(float scale)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
	owner->Transform()->position += up * moveSpeed * dt * scale;
}

void CharacterController::Rotate(float x, float y)
{
	float dt = owner->GetScene()->GetHandleTimer().dt;
	TransformData* trans = owner->Transform();
	trans->rotation.x += x * rotateSpeed * dt;
	trans->rotation.y += y * rotateSpeed * dt;
}
