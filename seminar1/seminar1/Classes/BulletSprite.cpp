#include "BulletSprite.h"

CCPoint BulletSprite::getVelocity() {
    return velocity;
}
void BulletSprite::setVelocity(CCPoint point) {
    velocity = point;
}