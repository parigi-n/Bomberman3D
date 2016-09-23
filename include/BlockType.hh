#ifndef BLOCKTYPE_HH
# define BLOCKTYPE_HH

namespace BlockType
{
  enum BlockType
    {
      LIGHT,
      HARD,
      EMPTY,
      RADIUS_ITEM,
      BOMB,
      BOMB_ITEM,
      SPEED_ITEM,
      SOCLE,
      NOTHING,
      BOMBERMAN
    };
  enum AnimateType
    {
      PLAYER
    };
  enum Texture
    {
      TLIGHT,
      THARD,
      TEND,
      TGRID,
      TPARTICULE1,
      TPARTICULE2
    };
};

namespace Action
{
  enum Action
    {
      UP,
      DOWN,
      LEFT,
      RIGHT,
      ACTION,
      NONE
    };
};

/* Encapsulation */
typedef irr::scene::IAnimatedMeshSceneNode	AnimatedMeshSceneNode;
typedef irr::IrrlichtDevice			Device;
typedef irr::scene::IMeshSceneNode		MeshScene;
typedef irr::scene::IAnimatedMesh		AnimatedMesh;
typedef irr::scene::ICameraSceneNode		CameraScene;
typedef irr::video::IVideoDriver		VideoDriver;
typedef irr::scene::ISceneManager		SceneManager;
typedef irr::scene::ISceneNode			Scene;
typedef irr::core::vector2di			vector2di;
typedef irr::core::vector3di			vector3di;
typedef irr::core::vector2df			vector2df;
typedef irr::core::vector3df			vector3df;
typedef irr::video::ITexture			ITexture;
typedef irr::core::aabbox3d<float>		aabbox3d;
typedef irr::gui::IGUIEnvironment		GUIEnv;
typedef irr::gui::IGUIFont			GUIFont;
typedef irr::core::dimension2d<unsigned>	dimension2d;
typedef irr::core::dimension2d<float>		dimension2f;
typedef irr::scene::IParticleEmitter		ParticleEmitter;
typedef irr::core::stringw			Stringw;
typedef unsigned				u32;
typedef float					f32;

// typedef irr::core::dimension2d<float>		dimension2f;

#endif
