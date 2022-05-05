#include "../include/Minion.hpp"
#include "../include/Sprite.hpp"
#include "../include/Bullet.hpp"
#include "../include/Game.hpp"
#include "../include/Collider.hpp"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : 
    Component(associated) {
    arc = arcOffsetDeg;
    this->alienCenter = alienCenter;

    Sprite* sp = new Sprite(associated, "assets/img/minion.png");
    Collider* cl = new Collider(associated);

    // random sprite scale
    float size = (std::rand() % 6) + 10;
    sp->SetScaleX(size/10, size/10);

    associated.AddComponent(sp);
    associated.AddComponent(cl);
    
    // sets initial minion rotation
    if(std::shared_ptr<GameObject> go = alienCenter.lock()) {
        associated.box.set_center(go->box.center() + Vec2(MINION_DISTANCE,0).rotated(arc));
    } else {
        associated.RequestDelete();
    }
}

void Minion::Start() {}

void Minion::Update(float dt) {
    Vec2 origin(MINION_DISTANCE,0);
    origin.rotate(arc);
    arc += M_PI/180 * MINION_SPEED;
    associated.angleDeg = arc * (180/M_PI);

    // follows it's alien
    if(std::shared_ptr<GameObject> go = alienCenter.lock()) {
        origin += go->box.center();
        associated.box.set_center(origin);
    } else {
        this->Kill();
    }
}

void Minion::Render() {}

bool Minion::Is(std::string type) {
    return (type == "Minion");
}

/**
 * Shoots single bullet
 * */
void Minion::Shoot(Vec2 pos) {
    Game& gm = Game::GetInstance();
    State& st = gm.GetState();

    GameObject* go = new GameObject();
    Vec2 curr_pos = associated.box.center();

    Bullet* bl = new Bullet(*go, curr_pos.angle(pos), MINION_BULLET_SPEED, MINION_BULLET_DAMAGE, 
                            MINION_BULLET_DISTANCE, "assets/img/minionbullet2.png", 3, 0.15f, true);
    go->box.set_center(curr_pos);
    go->AddComponent(bl);

    st.AddObject(go);
}

/**
 * Death animation 
 * Requests deletion on associated
 */
void Minion::Kill() {
    Game& gm = Game::GetInstance();
    State& st = gm.GetState();

    GameObject* explosion = new GameObject();

    explosion->AddComponent(new Sprite(*explosion, "assets/img/miniondeath.png", 4, 0.125, 0.5));
    explosion->box.set_center(associated.box.center());
    explosion->angleDeg = associated.angleDeg;

    st.AddObject(explosion);

    associated.RequestDelete();
}