#include "../include/Alien.hpp"
#include "../include/Sprite.hpp"
#include "../include/InputManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Game.hpp"
#include "../include/Minion.hpp"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    Sprite* sp = new Sprite("assets/img/alien.png", associated);
    associated.AddComponent(sp);
    hp = ALIEN_HP;
    speed = Vec2(0,0);
    this->nMinions = nMinions;
}

Alien::~Alien() {
    minionArray.clear();
}

/**
 * Starts Alien's minions
 * */
void Alien::Start() {
    Game& gm = Game::GetInstance();
    State& st = gm.GetState();

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
    InputManager& inp = InputManager::GetInstance();

    if(inp.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::ActionType::SHOOT, 
                    inp.GetMouseX() + Camera::pos.x, inp.GetMouseY() + Camera::pos.y));
    }
    if(inp.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::ActionType::MOVE, 
                    inp.GetMouseX() + Camera::pos.x, inp.GetMouseY() + Camera::pos.y));
    }

    if(!taskQueue.empty()) {
        Action top = taskQueue.front();
        if(top.type == Action::ActionType::MOVE) {
            Rect target(top.pos.x, top.pos.y, 0, 0);
            // movement command in queue
            if(abs(associated.box.distance_to(target)) <= (dt * ALIEN_SPEED)) {
                associated.box.set_center(top.pos);
                taskQueue.pop();
            } else {
                speed = Vec2(0,0);
                speed = (top.pos - associated.box.center()).normalized() * dt * ALIEN_SPEED;
                associated.box += speed;
            }
        } else if(top.type == Action::ActionType::SHOOT) {
            // shoot command in queue
            int closest = 0;
            float min_dist = 3.40282e+038;
            for(unsigned int i=0;i<minionArray.size();i++) {
                if(std::shared_ptr<GameObject> go = minionArray[i].lock()) {
                    float idist = go->box.center().distance(top.pos);
                    if(idist < min_dist) {
                        closest = i;
                        min_dist = idist;
                    }
                }    
            }

            if(std::shared_ptr<GameObject> go = minionArray[closest].lock()) {
                Minion* mn = (Minion*) go->GetComponent("Minion");
                mn->Shoot(top.pos);
            }

            taskQueue.pop();
        }
    }

    associated.angleDeg -= ALIEN_SPIN;

    if(hp <= 0) {
        associated.RemoveComponent(this);
    }
}

void Alien::Render() {}

bool Alien::Is(std::string type) {
    return (type == "Alien");
}

Alien::Action::Action(ActionType action, float x, float y) {
    type = action;
    pos = Vec2(x,y);
}