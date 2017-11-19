#pragma once

#include <iostream>

class Module;
class File;

class TexturesMgr : public Module, public RefManager1DimAssync<R_Texture>
{
public:
	DEF_MODULE(TexturesMgr);

    R_Texture* Add(cstring _textureFileName);
    R_Texture* Add(File& _textureFile);

    R_Texture* DefaultTexture() { return m_DefaultTexture2DObj; }

protected:
    R_Texture* CreateAction(cstring name) override;
	void LoadAction(string _name, R_Texture*& _texture) override;
	bool DeleteAction(cstring name) override;

public:
	bool LoadBLPTexture(File& _file, R_Texture*& _texture);

private:
    R_Texture*   m_DefaultTexture2DObj;
    R_Texture*   m_DefaultTexture3DObj;
    R_Texture*   m_DefaultTextureCubeObj;
    vec2         m_DefaultTextureSize;

	ContainerAssync<string, R_Texture*> textures;
};

#define _TexturesMgr TexturesMgr::instance()
