#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED

class Animation{
private:

        int currentFrame = 0;
        int framesAmount = 0;

        Sprite* animSpr;
        Texture* animTex;

        Clock clock;

public:
        LoadAnimation(Sprite* sprite, Texture textures[], int frameAmt, string animName) {
            animSpr = sprite;
            animTex = textures;
            framesAmount = frameAmt;

            for (int i = 0; i < framesAmount; i++){
                animTex[i] = SetTexture("animations/"+ animName + to_string(i));
            }
        }

        PlayAnimation(float frameRate){

            if (currentFrame < framesAmount){
                if (clock.getElapsedTime().asSeconds() > 1 / frameRate) {
                    animSpr->setTexture(animTex[currentFrame]);
                    currentFrame++;
                    clock.restart();
                }
            }
        }
        float getDuration(float frameRate){
            return framesAmount / frameRate;
        }
};

class Animator{
private:

    float frameRate;
    Animation animations[6];
    Texture kl1Frames[32];
    Texture kl2Frames[32];
    Texture mt1Frames[14];
    Texture mt2Frames[14];
    Texture mxFrames[18];
    Texture vsFrames[18];

public:
    Animator(Sprite* sprite, float fps){
        frameRate = fps;
        animations[0].LoadAnimation(sprite, kl1Frames, 32, "kloster");
        animations[1].LoadAnimation(sprite, kl2Frames, 32, "kloster");
        animations[2].LoadAnimation(sprite, mt1Frames, 14, "mati");
        animations[3].LoadAnimation(sprite, mt2Frames, 14, "mati");
        animations[4].LoadAnimation(sprite, mxFrames, 18, "maxi");
        animations[5].LoadAnimation(sprite, vsFrames, 18, "vastag");
    }
    void PlayAnimation(int animID){
        animations[animID].PlayAnimation(frameRate);
    }
    float getDuration(int animID){
        return animations[animID].getDuration(frameRate);
    }
};

#endif // ANIM_H_INCLUDED
