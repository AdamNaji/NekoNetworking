/*
 MIT License

 Copyright (c) 2020 SAE Institute Switzerland AG

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "asteroid/bullet_manager.h"
#include "asteroid/game.h"
#include "asteroid/game_manager.h"

namespace neko::asteroid
{
BulletManager::BulletManager(EntityManager& entityManager, GameManager& gameManager, PhysicsManager& physicsManager, PlayerCharacterManager& playerCharacterManager) :
    ComponentManager(entityManager), gameManager_(gameManager), physicsManager_(physicsManager), playerCharacterManager_(playerCharacterManager)
{
}
BulletManager& BulletManager::operator=(const BulletManager& ballManager)
{
    components_ = ballManager.components_;
    //We do NOT copy the physics manager
    return *this;
}

void BulletManager::FixedUpdate(seconds dt)
{
    for(Entity entity = 0; entity < entityManager_.get().GetEntitiesSize(); entity++)
    {
        if(entityManager_.get().HasComponent(entity, EntityMask(ComponentType::BULLET)))
        {
            auto& bullet = components_[entity];
            auto bulletBody = physicsManager_.get().GetBody(entity);

        	if(bulletBody.position.y >playerPosMax || bulletBody.position.y< playerPosMin)
        	{
                bulletBody.velocity = Vec2f(bulletBody.velocity.x, -bulletBody.velocity.y);
                physicsManager_.get().SetBody(entity, bulletBody);
        	}
            if (bulletBody.position.x > bulletMaxPosX || bulletBody.position.x < -bulletMaxPosX)
            {
                bulletBody.velocity = Vec2f(-bulletBody.velocity.x, bulletBody.velocity.y);
                physicsManager_.get().SetBody(entity, bulletBody);
            }
          
        }
    }
}
}