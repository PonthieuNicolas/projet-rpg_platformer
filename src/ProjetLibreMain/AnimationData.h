#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace AnimationData {

    inline std::string getSlimeSpritePath() {
        return "../../res/ProjetLibreMain/BlueSlimeSpriteSheet.png";
    }

    inline std::string getBlackWizardSpritePath() {
        return "../../res/ProjetLibreMain/BlackWizardSpriteSheet.png";
    }

    inline std::string getLevelSprite() {
        return "../../res/ProjetLibreMain/TestLv.png";
    }

    inline std::string getBackgroundSprite() {
        return "../../res/ProjetLibreMain/BackgroundMid.png";
    }

    inline std::string getProjectileSprite() {
        return "../../res/ProjetLibreMain/Projectile.png";
    }

    inline std::string getSkillCardSprite() {
        return "../../res/ProjetLibreMain/HomingSkillCard.png";
    }

    // Slime Idle Animation (12 frames)
    inline std::vector<sf::IntRect> getSlimeIdleFrames() {
        std::vector<sf::IntRect> frames;
        frames.push_back(sf::IntRect(sf::Vector2i(278, 92), sf::Vector2i(65, 46))); // Cadre 2 
        frames.push_back(sf::IntRect(sf::Vector2i(398, 92), sf::Vector2i(65, 46))); // Cadre 3
        frames.push_back(sf::IntRect(sf::Vector2i(514, 92), sf::Vector2i(65, 46))); // Cadre 4
        frames.push_back(sf::IntRect(sf::Vector2i(629, 92), sf::Vector2i(65, 46))); // Cadre 5 
        frames.push_back(sf::IntRect(sf::Vector2i(746, 92), sf::Vector2i(65, 46))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(859, 92), sf::Vector2i(65, 46))); // Cadre 7
        frames.push_back(sf::IntRect(sf::Vector2i(974, 92), sf::Vector2i(65, 46))); // Cadre 8
        //frames.push_back(sf::IntRect(sf::Vector2i(859, 92), sf::Vector2i(65, 46))); // Cadre 7
        //frames.push_back(sf::IntRect(sf::Vector2i(746, 92), sf::Vector2i(65, 46))); // Cadre 6
        //frames.push_back(sf::IntRect(sf::Vector2i(629, 92), sf::Vector2i(65, 46))); // Cadre 5 
        //frames.push_back(sf::IntRect(sf::Vector2i(514, 92), sf::Vector2i(65, 46))); // Cadre 4
        //frames.push_back(sf::IntRect(sf::Vector2i(398, 92), sf::Vector2i(65, 46))); // Cadre 3
        return frames;
    }

    // Black Wizard Idle Animation (8 frames)
    inline std::vector<sf::IntRect> getBlackWizardIdleFrames() {
        std::vector<sf::IntRect> frames;
        frames.push_back(sf::IntRect(sf::Vector2i(150, 42), sf::Vector2i(70, 82))); // Cadre 1 
        frames.push_back(sf::IntRect(sf::Vector2i(265, 42), sf::Vector2i(70, 82))); // Cadre 2 
        frames.push_back(sf::IntRect(sf::Vector2i(380, 42), sf::Vector2i(70, 82))); // Cadre 3
        frames.push_back(sf::IntRect(sf::Vector2i(495, 42), sf::Vector2i(70, 82))); // Cadre 4
        frames.push_back(sf::IntRect(sf::Vector2i(609, 42), sf::Vector2i(70, 82))); // Cadre 5 
        frames.push_back(sf::IntRect(sf::Vector2i(724, 42), sf::Vector2i(70, 82))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(839, 42), sf::Vector2i(70, 82))); // Cadre 7
        frames.push_back(sf::IntRect(sf::Vector2i(955, 42), sf::Vector2i(70, 82))); // Cadre 8
        return frames;
    }

    // Black Wizard Walk Animation (7 frames)
    inline std::vector<sf::IntRect> getBlackWizardWalkFrames() {
        std::vector<sf::IntRect> frames;
        frames.push_back(sf::IntRect(sf::Vector2i(167, 182), sf::Vector2i(66, 82))); // Cadre 1 
        frames.push_back(sf::IntRect(sf::Vector2i(282, 182), sf::Vector2i(66, 82))); // Cadre 2 
        frames.push_back(sf::IntRect(sf::Vector2i(397, 182), sf::Vector2i(66, 82))); // Cadre 3
        frames.push_back(sf::IntRect(sf::Vector2i(512, 182), sf::Vector2i(66, 82))); // Cadre 4
        frames.push_back(sf::IntRect(sf::Vector2i(626, 182), sf::Vector2i(66, 82))); // Cadre 5 
        frames.push_back(sf::IntRect(sf::Vector2i(741, 182), sf::Vector2i(66, 82))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(856, 182), sf::Vector2i(66, 82))); // Cadre 7
        return frames;
    }

    // Black Wizard Jump Animation (18 frames)
    inline std::vector<sf::IntRect> getBlackWizardJumpFrames() {
        std::vector<sf::IntRect> frames;
        frames.push_back(sf::IntRect(sf::Vector2i(151, 972), sf::Vector2i(72, 90))); // Cadre 1 
        //frames.push_back(sf::IntRect(sf::Vector2i(266, 972), sf::Vector2i(72, 90))); // Cadre 2 
        frames.push_back(sf::IntRect(sf::Vector2i(385, 972), sf::Vector2i(72, 90))); // Cadre 3
        frames.push_back(sf::IntRect(sf::Vector2i(506, 957), sf::Vector2i(72, 90))); // Cadre 4
        frames.push_back(sf::IntRect(sf::Vector2i(621, 950), sf::Vector2i(72, 90))); // Cadre 5
        frames.push_back(sf::IntRect(sf::Vector2i(621, 950), sf::Vector2i(72, 90))); // Cadre 5
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(746, 965), sf::Vector2i(83, 90))); // Cadre 6
        //frames.push_back(sf::IntRect(sf::Vector2i(853, 970), sf::Vector2i(75, 90))); // Cadre 7
        //frames.push_back(sf::IntRect(sf::Vector2i(963, 970), sf::Vector2i(75, 90))); // Cadre 8
        return frames;
    }

    // Black Wizard Attack 1 Animation (7 frames)
    inline std::vector<sf::IntRect> getBlackWizardAttack1Frames() {
        std::vector<sf::IntRect> frames;
        frames.push_back(sf::IntRect(sf::Vector2i(157, 402), sf::Vector2i(114, 120))); // Cadre 1 
        frames.push_back(sf::IntRect(sf::Vector2i(272, 402), sf::Vector2i(114, 120))); // Cadre 2 
        frames.push_back(sf::IntRect(sf::Vector2i(387, 402), sf::Vector2i(114, 120))); // Cadre 3
        frames.push_back(sf::IntRect(sf::Vector2i(502, 402), sf::Vector2i(114, 120))); // Cadre 4
        frames.push_back(sf::IntRect(sf::Vector2i(616, 402), sf::Vector2i(114, 120))); // Cadre 5 
        frames.push_back(sf::IntRect(sf::Vector2i(731, 402), sf::Vector2i(114, 120))); // Cadre 6
        frames.push_back(sf::IntRect(sf::Vector2i(846, 402), sf::Vector2i(114, 120))); // Cadre 7
        return frames;
    }
}
