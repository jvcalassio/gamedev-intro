#include "../include/Collider.hpp"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : 
    Component(associated) {
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt) {
    box = associated.box + Vec2(0,0);
    box.w *= scale.x;
    box.h *= scale.y;
    box.set_center(associated.box.center() + offset.rotated(associated.angleDeg * (M_PI/180)));
}

/**
 * Renders the collision lines when on debug mode
 */
void Collider::Render() {
    #ifdef DEBUG
	Vec2 center(box.center());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).rotated(associated.angleDeg/(180/M_PI))
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).rotated(associated.angleDeg/(180/M_PI))
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).rotated(associated.angleDeg/(180/M_PI))
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).rotated( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
    #endif // DEBUG
}

void Collider::Start() {}

bool Collider::Is(std::string type) {
    return (type == "Collider");
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}