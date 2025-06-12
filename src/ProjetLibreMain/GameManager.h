#pragma once
#include "TimerSystem.h"
#include "CollisionSystem.h"
#include "CollisionEvent.h"
#include "MovementSyncSystem.h"
#include "../SfmlMotor/AnimationSystem.h"
#include "InterfaceSystem.h"
#include "BlueSlimeScript.h"
#include "../SfmlMotor/CameraSystem.h"
#include "LevelSystem.h"
#include "HomingProjectileScript.h"
#include "Skill.h"
#include "MusicComponent.h"

#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include"ECS_Manager.h"
#include "Stats.h"
#include"Transform.h"
#include "PlayerScript.h"
#include "BasicProjectileScript.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Run();

private:
    void LoadAnimationFrame();
    void OnInit();
    void SetupECS();
    void OnUpdate(const TimerSystem& gt);
    void OnRender();
    void Draw(const TimerSystem& gt);

    TimerSystem mTimer;
    SpriteComponent SpComp;
    SpriteComponent Background;
	SpriteComponent HomingCard;
    
    CameraSystem* cameraSystem;
    sf::View gameView;
    SpriteComponent Projectile;

    Entity* player;
    Entity* blueSlime;
    Entity* playerPlatform;

    sf::Texture slimeTexture;
    sf::Texture blackWizardTexture;
    sf::Texture backgroundTexrure;
    sf::Texture projectileTexture;
    sf::Texture homingCardTexture;

    MusicComponent* backgroundMusic;
    float m_musicDelayTimer = 0.f;
    bool m_musicStarted = false;

    Skill* homingSkill = nullptr;

    ColliderComponent* mCollider;
    ColliderComponent* mCollider2;

    ECS_Manager* gameManager;
    LevelSystem* levelSystem;

    Entity* CreatePlayer(ECS_Manager* ecsManager);
    Entity* CreateBlueSlime(ECS_Manager* ecsManager);
    Entity* CreatePlayerPlatform(ECS_Manager* ecsManager);

    sf::RenderWindow window;
    sf::Font mFont;
    InterfaceSystem* interfaceSystem;

    bool showColliders;
};