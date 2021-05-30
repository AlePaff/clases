#ifndef __WORM_H__
#define __WORM_H__

#include "Animation.h"

class Worm {
public:
    Worm(SdlTexture &texture);
    ~Worm();
    void update(float dt);
    void render();
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif // __WORM_H__