#include "../include/PenguinBody.hpp"
#include "../include/Sprite.hpp"
#include "../include/PenguinCannon.hpp"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "../include/Collider.hpp"
#include "../include/Bullet.hpp"
#include "../include/Camera.hpp"
#include "../include/Sound.hpp"
#include <iostream>

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    speed = Vec2(0, 0);
    linearSpeed = 0;
    hp = PENGUIN_HP;
    angle = 0;

    Sprite* sp = new Sprite(associated, "assets/img/penguin.png");
    Collider* cl = new Collider(associated);
    associated.angleDeg = angle * (180/M_PI);
    associated.AddComponent(sp);
    associated.AddComponent(cl);

    PenguinBody::player = this;
}

PenguinBody::~PenguinBody() {
    PenguinBody::player = nullptr;
}

void PenguinBody::Start() {
    Game& gm = Game::GetInstance();
    State& st = gm.GetCurrentState();

    // adds cannon
    GameObject* go = new GameObject();
    std::weak_ptr<GameObject> wp = st.GetObjectPtr(&associated);

    go->AddComponent(new PenguinCannon(*go, wp));
    pcannon = st.AddObject(go);
}

void PenguinBody::Update(float dt) {
    InputManager& inp = InputManager::GetInstance();

    if(inp.IsKeyDown(W_KEY)) {
        // moves forward
        if(linearSpeed < PENGUIN_MAX_SPEED) {
            linearSpeed += PENGUIN_ACCELERATION;
        }
    } else if(inp.IsKeyDown(S_KEY)) {
        // moves backwards
        if(linearSpeed > -PENGUIN_MAX_SPEED) {
            linearSpeed -= PENGUIN_ACCELERATION;
        }
    } else {
        // slowly stops
        if(linearSpeed > 0) {
            linearSpeed -= PENGUIN_ACCELERATION;
            if(linearSpeed <= 0) {
                linearSpeed = 0;
            }
        } else if(linearSpeed < 0) {
            linearSpeed += PENGUIN_ACCELERATION;
            if(linearSpeed >= 0) {
                linearSpeed = 0;
            }
        }
    }

    if(inp.IsKeyDown(A_KEY)) {
        // left spin
        angle -= 0.05;
    }

    if(inp.IsKeyDown(D_KEY)) {
        // right spin
        angle += 0.05;
    }

    speed = Vec2(linearSpeed, 0);

    int newx = associated.box.x + (speed.rotated(angle) * dt).x;
    int newy = associated.box.y + (speed.rotated(angle) * dt).y;
    if((0 < newx && newx < 1408) && (0 < newy && newy < 1280)) {
        associated.box += speed.rotated(angle) * dt;
        associated.angleDeg = angle * (180/M_PI);
    }

    if(hp <= 0) {
        this->Kill();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(std::string type) {
    return (type == "PenguinBody");
}

/**
 * Handles any collision on the Penguin object
 * @param other The collided GameObject 
 */
void PenguinBody::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
    if(bullet && bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
        if(hp <= 0) {
            this->Kill();
        }
        //std::cout << "tomei " << bullet->GetDamage() << " dano" << std::endl;
    }
}

Vec2 PenguinBody::GetPosition() {
    return associated.box.center();
}

void PenguinBody::Kill() {
    Game& gm = Game::GetInstance();
    State& st = gm.GetCurrentState();

    Camera::Unfollow();

    GameObject* explosion = new GameObject();
    Sound* sound = new Sound(*explosion, "assets/audio/boom.wav");

    explosion->AddComponent(new Sprite(*explosion, "assets/img/penguindeath.png", 5, 0.125, 0.625));
    explosion->AddComponent(sound);
    explosion->box.set_center(associated.box.center());
    explosion->angleDeg = associated.angleDeg;
    sound->Play();

    st.AddObject(explosion);

    associated.RequestDelete();
}