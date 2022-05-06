#include "../include/Alien.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Game.hpp"
#include "../include/Minion.hpp"
#include "../include/Collider.hpp"
#include "../include/Bullet.hpp"
#include "../include/Sound.hpp"
#include "../include/PenguinBody.hpp"
#include <iostream>

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : 
    Component(associated) {
    Sprite* sp = new Sprite(associated, "assets/img/alien.png");
    Collider* cl = new Collider(associated);
    associated.AddComponent(sp);
    associated.AddComponent(cl);

    hp = ALIEN_HP;
    speed = Vec2(0,0);
    state = AlienState::RESTING;
    this->nMinions = nMinions;

    alienCount++;
}

Alien::~Alien() {
    alienCount--;
    minionArray.clear();
}

/**
 * Starts Alien's minions
 * */
void Alien::Start() {
    Game& gm = Game::GetInstance();
    State& st = gm.GetCurrentState();

    for(int i=1;i<=nMinions;i++) {
        GameObject* go = new GameObject();
        std::weak_ptr<GameObject> wp = st.GetObjectPtr(&associated);

        go->AddComponent(new Minion(*go, wp, M_PI*2/nMinions*i));
        minionArray.push_back(st.AddObject(go));
    }
}

/**
 * Adds actins to queue
 * 
 * Handles action queue
 * */
void Alien::Update(float dt) {
    if(PenguinBody::player != nullptr) {
        if(state == AlienState::RESTING) {
            if(restTimer.Get() >= ALIEN_REST_TIME) {
                state = AlienState::MOVING;
                destination = PenguinBody::player->GetPosition();
            } else {
                restTimer.Update(dt);
            }
        } else {
            Rect target(destination.x, destination.y, 0, 0);
            
            if(abs(associated.box.distance_to(target)) <= MINION_BULLET_DISTANCE + MINION_DISTANCE) {
                // stops
                speed = Vec2(0,0);

                // shoot
                destination = PenguinBody::player->GetPosition();
                int closest = 0;
                float min_dist = 3.40282e+038;
                for(unsigned int i=0;i<minionArray.size();i++) {
                    if(std::shared_ptr<GameObject> go = minionArray[i].lock()) {
                        float idist = go->box.center().distance(destination);
                        if(idist < min_dist) {
                            closest = i;
                            min_dist = idist;
                        }
                    }    
                }

                if(std::shared_ptr<GameObject> go = minionArray[closest].lock()) {
                    Minion* mn = (Minion*) go->GetComponent("Minion");
                    mn->Shoot(destination);
                }

                // resets state
                state = AlienState::RESTING;
                restTimer.Restart();
            } else {
                // moves
                speed = (destination - associated.box.center()).normalized() * dt * ALIEN_SPEED;
                associated.box += speed;
            }
        }
    }

    associated.angleDeg -= ALIEN_SPIN;

    if(hp <= 0) {
        this->Kill();
    }
}

void Alien::Render() {}

bool Alien::Is(std::string type) {
    return (type == "Alien");
}

/**
 * Handles any collision
 * 
 * @param other The collided GameObject 
 */
void Alien::NotifyCollision(GameObject& other) {
    Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
    if(bullet && !bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
        if(hp <= 0) {
            this->Kill();
        }
        //std::cout << "alien levou " << bullet->GetDamage() << " dano" << std::endl;
    }
}

/**
 * Death animation and sound
 * Requests deletion on it's associated
 */
void Alien::Kill() {
    Game& gm = Game::GetInstance();
    State& st = gm.GetCurrentState();

    GameObject* explosion = new GameObject();
    Sound* sound = new Sound(*explosion, "assets/audio/boom.wav");

    explosion->AddComponent(new Sprite(*explosion, "assets/img/aliendeath.png", 4, 0.125, 0.5));
    explosion->AddComponent(sound);
    explosion->box.set_center(associated.box.center());
    explosion->angleDeg = associated.angleDeg;
    sound->Play();

    st.AddObject(explosion);

    associated.RequestDelete();
}