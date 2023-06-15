#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

class Render{

private:
    Image image;
    string imageID;

public:
    Image getImage(){
    return image;
    }

    void setImage(/*const char* textureID*/ string name){
        /*
        string texID;
        int texIDLength = sizeof(textureID)/sizeof(textureID[0]);
        for (int i = 0; i < texIDLength; i++){
            texID.insert(i, 1, textureID[i]);
        }
        imageID = texID;
        */
        if (!image.loadFromFile(name)){
            cout<<"failed to load image of name "<<name<<endl;
        }
    }
};

#endif // RENDER_H_INCLUDED
