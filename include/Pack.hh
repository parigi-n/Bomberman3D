#ifndef PACK_HH
# define PACK_HH

# include <string>
# include <map>
# include <irrlicht.h>
# include "Exception.hh"
# include "BlockType.hh"

class TexturePack
{
public:
  TexturePack(irr::video::IVideoDriver *driver);
  irr::video::ITexture	*getTexture(const BlockType::Texture &textureName) const;
  bool			addTexture(BlockType::Texture const &ID,
				   std::string const &file);
private:
  std::map<BlockType::Texture, irr::video::ITexture *> texture;
  irr::video::IVideoDriver *driver;
};

class MeshPack
{
public:
  MeshPack(irr::scene::ISceneManager *smgr);
  bool			addTexture();
  irr::scene::IMesh *getMesh(const BlockType::BlockType &objectName) const;
  irr::scene::IAnimatedMesh *getMesh(const BlockType::AnimateType &objectName) const;
  irr::scene::IAnimatedMesh *getPlayer() const;
  bool			addMesh(BlockType::BlockType const &ID,
				std::string const &object);
  bool			addMesh(BlockType::AnimateType const &ID,
				std::string const &object);
private:
  std::map<BlockType::BlockType, irr::scene::IMesh *> mesh;
  std::map<BlockType::AnimateType, irr::scene::IAnimatedMesh *> animatedmesh;
  irr::scene::ISceneManager *smgr;
};

#endif
