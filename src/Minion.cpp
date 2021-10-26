#include "../include/Minion.hpp"
#include "../include/Sprite.hpp"
#include "../include/Bullet.hpp"
#include "../include/Game.hpp"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, 
                float arcOffsetDeg) : Component(associated) {
    arc = arcOffsetDeg;
    this->alienCenter = alienCenter;

    Sprite* sp = new Sprite("assets/img/minion.png", associated);
    // random scale
    float size = (std::rand() % 6) + 10;
    sp->SetScaleX(size/10, size/10);
    associated.AddComponent(sp);
    
    // sets initial minions rotation
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
        associated.RequestDelete();
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
    GameObject* go = new GameObject();
    Vec2 curr_pos = associated.box.center();

    Bullet* bl = new Bullet(*go, curr_pos.angle(pos), DEFAULT_BULLET_SPEED, DEFAULT_BULLET_DAMAGE, 
                            DEFAULT_BULLET_DISTANCE, "assets/img/minionbullet1.png");
    go->box.set_center(curr_pos);
    go->AddComponent(bl);

    Game& gm = Game::GetInstance();
    State& st = gm.GetState();
    st.AddObject(go);
}