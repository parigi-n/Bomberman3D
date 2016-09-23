#include "Pack.hh"

TexturePack::TexturePack(VideoDriver *_driver) : driver(_driver)
{
}

bool	 TexturePack::addTexture(BlockType::Texture const &ID,
				 std::string const &file)
{
  try
    {
      if ((texture[ID] = driver->getTexture(file.c_str())) == NULL)
	throw (file.c_str());
    }
  catch (char const *file)
    {
      openError(file);
      return (false);
    }
  return (true);
}

irr::video::ITexture *TexturePack::getTexture(const BlockType::Texture &textureName) const
{
  std::map<BlockType::Texture, ITexture *>::const_iterator it;

  try
    {
      it = texture.find(textureName);
      if (it != texture.end())
	return (it->second);
      else
	throw ("Texture requested not found");
    }
  catch (char const *file)
    {
      openError(file);
      return (NULL);
    }
}

MeshPack::MeshPack(SceneManager *_smgr) : smgr(_smgr)
{
}

bool			MeshPack::addMesh(BlockType::BlockType const &ID,
					  std::string const &object)
{
  try
    {
      if ((mesh[ID] = smgr->getMesh(object.c_str())) == NULL)
	throw (object.c_str());
    }
  catch (char const *file)
    {
      openError(file);
      return (false);
    }
  return (true);
}

bool			MeshPack::addMesh(BlockType::AnimateType const &ID,
					  std::string const &object)
{
  try
    {
      if ((animatedmesh[ID] = smgr->getMesh(object.c_str())) == NULL)
	throw (object.c_str());
    }
  catch (char const *file)
    {
      openError(file);
      return (false);
    }
  return (true);
}

irr::scene::IMesh	*MeshPack::getMesh(const BlockType::BlockType &objectName) const
{
  std::map<BlockType::BlockType, irr::scene::IMesh *>::const_iterator it;

  try
    {
      it = mesh.find(objectName);
      if (it != mesh.end())
	return (it->second);
      else
	throw ("Mesh requested not found");
    }
  catch (char const *file)
    {
      openError(file);
      return (NULL);
    }
}

AnimatedMesh	*MeshPack::getMesh(const BlockType::AnimateType &objectName) const
{
  std::map<BlockType::AnimateType, AnimatedMesh *>::const_iterator it;

  try
    {
      it = animatedmesh.find(objectName);
      if (it != animatedmesh.end())
	return (it->second);
      else
	throw ("Mesh requested not found");
    }
  catch (char const *file)
    {
      openError(file);
      return (NULL);
    }
}
