#ifndef ANIM_H_INCLUDED
#define ANIM_H_INCLUDED

class Animation{
private:

        int currentFrame = 0;
        int framesAmount = 0;
        bool started = false;

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
            if (!started && currentFrame != framesAmount){
                currentFrame = 0;
                started = true;
                //cout<<"start normal"<<endl;
            }
            if (currentFrame < framesAmount){
                if (clock.getElapsedTime().asSeconds() > 1 / frameRate) {
                    animSpr->setTexture(animTex[currentFrame]);
                    //cout<<currentFrame<<" normal "<<framesAmount<<endl;
                    currentFrame++;
                    clock.restart();
                }
            }
            if (currentFrame == framesAmount && started){
                started = false;
                //cout<<"reset normal"<<endl;
            }
        }
        PlayAnimationReverse(float frameRate){
            if (!started && currentFrame >= 0){
                currentFrame = framesAmount - 1;
                started = true;
                //cout<<"start reverse"<<endl;
            }
            if (currentFrame >= 0){
                if (clock.getElapsedTime().asSeconds() > 1 / frameRate) {
                    animSpr->setTexture(animTex[currentFrame]);
                    //cout<<currentFrame<<" reverse "<<framesAmount<<endl;
                    currentFrame--;
                    clock.restart();
                }
            }
            if (currentFrame == -1  && started){
                started = false;
                //cout<<"reset reverse"<<endl;
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
