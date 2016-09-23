#include "RunGame.hh"

void runGame(Device *device, GUIEnv* env, VideoDriver* video, SoundManager *soundManager, MyEventReceiver *receiver, SceneManager *smgr, Config conf, TexturePack *texture, MeshPack *mesh, Game game, Score score, Interface menu, GUIFont *font)
{ 
  int lastFPS = -1;
  u32 then = device->getTimer()->getTime();
  irr::s32 oldFps = 0;

  u32 startTime = then;

  Stringw windowCaption;

   while (device->run() && device)
   {
      if (receiver->getInGame() == false)
   {
    displayMenu(&game, env, video, receiver);
    if (receiver->IsKeyDown(irr::KEY_SPACE) == true)
      {
        env->clear();
        device->getTimer()->start();
        receiver->setInGame();
      }
    if (receiver->IsKeyDown(irr::KEY_KEY_Q) == true)
      device->closeDevice();
  }
      else
  {
    const irr::u32 now = device->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f; // Time in seconds

    then = now;
    if (game.getState() == Game::NO)
      {
        startTime = device->getTimer()->getTime();
        device->getTimer()->start();
        game.createMap(receiver->getX(), receiver->getY(), receiver->getPlayers(),
		       receiver->getRandom(), receiver->getGraphism());
        soundManager->playSound(SoundManager::StartBattle);
        game.setState(Game::READY);
      }

    if (game.getState() == Game::READY && now - startTime > 3000)
      {
        game.setState(Game::GO);
      }
    if (game.getState() == Game::GO && now - startTime > 4500)
      {
        soundManager->playBattleMusic();
        game.setState(Game::PLAY);
      }
    //Gestion des touches :Movement
    if (game.getState() == Game::PLAY)
      {
        game.updateMovement(frameDeltaTime);
      }
    if (receiver->IsKeyDown(irr::KEY_ESCAPE) == true)
      {
        device->getTimer()->stop();
        receiver->setInGame();
        menu.setPause(video);
        soundManager->pauseMusic();
      }


    video->beginScene(true, true, irr::video::SColor(255,113,0,255));
    game.effect->update();

    /* A SUPPRIMER AVANT RENDU */
    if (oldFps != video->getFPS())
      {
        windowCaption = L"FPS ";
        windowCaption += video->getFPS();
        oldFps = video->getFPS();
      }
      /* A SUPPRIMER AVANT RENDU */

    font->draw(windowCaption, irr::core::recti(0, 0, 0, 0), irr::video::SColor(255, 248, 216, 56));
    if (game.getState() == Game::READY)
      font->draw(L"READY ?", irr::core::recti(0, 0, conf.screenSize.Width, conf.screenSize.Height), irr::video::SColor(255, 248, 216, 56), true, true);
    if (game.getState() == Game::GO)
      font->draw(L"GO !", irr::core::recti(0, 0, conf.screenSize.Width, conf.screenSize.Height), irr::video::SColor(255, 248, 216, 56), true, true);
    if (game.getState() == Game::FINISHED)
      {
        if (score._playerScore == 0)
          score._playerScore = 100 + (rand() % (int)(1000 - 100)+1);
        score.endScreen(device, env, video, soundManager, receiver, font, &conf.screenSize, menu, &game, then);
      }
    video->endScene();
    }
  }
}
