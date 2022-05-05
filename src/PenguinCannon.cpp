#include "../include/PenguinCannon.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Bullet.hpp"
#include "../include/Game.hpp"
#include "../include/Collider.hpp"
#include "../include/PenguinBody.hpp"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> pbody) : 
    Component(associated) {
    this->pbody = pbody;
    angle = 0;
    bulletCooldown = Timer();
    bulletCooldown.Update(PENGUIN_BULLET_COOLDOWN);

    Sprite* sp = new Sprite(associated, "assets/img/cubngun.png");
    Collider* cl = new Collider(associated);
    associated.angleDeg = angle * (180/M_PI);
    associated.AddComponent(sp);
    associated.AddComponent(cl);
}

void PenguinCannon::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();

    if(std::shared_ptr<GameObject> go = pbody.lock()) {
        associated.box.set_center(go->box.center());

        // rotate cannon
        Vec2 mousepos = Vec2(inp.GetMouseX(), inp.GetMouseY()) + Camera::pos;
        angle = associated.box.center().angle(mousepos);
        associated.angleDeg = angle * (180/M_PI);

        // shoots bullet
        if(inp.MousePress(LEFT_MOUSE_BUTTON) && bulletCooldown.Get() >= PENGUIN_BULLET_COOLDOWN) {
            this->Shoot();
            bulletCooldown.Restart();
        }

        bulletCooldown.Update(dt);
    } else {
        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(std::string type) {
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot() {
    Game& gm = Game::GetInstance();
    State& st = gm.GetState();
    
    GameObject* go = new GameObject();

    Bullet* bl = new Bullet(*go, angle, PENGUIN_BULLET_SPEED, PENGUIN_BULLET_DAMAGE, 
                            PENGUIN_BULLET_DISTANCE, "assets/img/penguinbullet.png", 3, 0.15f, false);
    go->box.set_center(associated.box.center() + Vec2(75,0).rotated(angle));
    go->AddComponent(bl);

    st.AddObject(go);
}

/**
 * Handles any collision on the Penguin Cannon
 * Since it's part of the whole Penguin, the action is delegated to the Penguin Body
 * @param other The collided GameObject 
 */
void PenguinCannon::NotifyCollision(GameObject& other) {
    if(std::shared_ptr<GameObject> go = pbody.lock()) {
        PenguinBody* body = (PenguinBody*) go->GetComponent("PenguinBody");
        body->NotifyCollision(other);
    } else {
        associated.RequestDelete();
    }
}