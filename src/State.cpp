#include <string>
#include "../include/State.hpp"
#include "../include/Face.hpp"
#include "../include/Sound.hpp"

/**
 * Starts the background image object
 * and loads the background music
 * */
State::State() {
    quitRequested = false;
    GameObject* bgobj = new GameObject();
    bgobj->AddComponent(new Sprite("./assets/img/ocean.jpg", *bgobj));
	objectArray.emplace_back(bgobj);

    music = new Music("./assets/audio/stageState.ogg");
    music->Play();
}

/**
 * Clears the current objects
 * */
State::~State() {
    objectArray.clear();
}

/**
 * Handles input (temporary)
 * */
void State::Input() {
    SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	while (SDL_PollEvent(&event)) {
		// new quit handler
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			// iterates from end to beggining
			// (prevents clicks on objects that are under other objects)
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// temporary spaghetti
				GameObject* go = (GameObject*) objectArray[i].get();

				if(go->box.contains( Vec2((float) mouseX, (float) mouseY) )) {
					Face* face = (Face*) go->GetComponent( "Face" );
					if ( nullptr != face && !face->IsDead()) {
						// damages
						face->Damage(std::rand() % 10 + 10);
						// assures that it hits only the first one found
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// quit if ESC is clicked
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			} else {
				Vec2 objPos = Vec2( 200, 0 ).rotated( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

/**
 * Add objects to this state at the {mouseX, mouseY} position
 * */
void State::AddObject(int mouseX, int mouseY) {
    GameObject* enemy = new GameObject();

    Sprite* es = new Sprite("./assets/img/penguinface.png", *enemy);
	// mouseX,Y represents the box center
    enemy->box.x = mouseX - (enemy->box.w / 2);
    enemy->box.y = mouseY - (enemy->box.h / 2);

	Sound* sn = new Sound("./assets/audio/boom.wav", *enemy);

    Face* fc = new Face(*enemy);


    enemy->AddComponent(es);
	enemy->AddComponent(sn);
    enemy->AddComponent(fc);

    objectArray.emplace_back(enemy);
}

void State::LoadAssets() {

}

/**
 * Updates the state
 * Checks if there's any dead entity
 * Runs at every gameloop iteration
 * */
void State::Update(float dt) {
    Input();
    for(int i=0;i<objectArray.size();i++) {
        objectArray[i]->Update(dt);
    }

    for(int i=0;i<objectArray.size();i++) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

/**
 * Renders the current gameobjects
 * */
void State::Render() {
    for(int i=0;i<objectArray.size();i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}