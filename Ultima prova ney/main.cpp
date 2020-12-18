#include <irrlicht.h>
#include "bola.h"
#include "tools.h"
#include "maquina.h"
#include "fx.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, 0);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNode(0, vector3df(0,10,-20), vector3df(2,-5,0));

    SLight luzSetup;
    luzSetup.AmbientColor = SColor(255,50,50,50);
    ILightSceneNode * light = smgr->addLightSceneNode(0, vector3df(0.0f), SColorf(255,255,240,200), 0.1f, 0);
    light->setLightData(luzSetup);

    ITexture * fundo = driver->getTexture("3d/fundo.jpg");

    bola atomo1 (device, 5, 3);
    bola atomo2 (device, 15, 3);
    maquina portal (device, 15);


    CStopWatch hrTimer;
    while(device->run())
    {
        bool estado;
        reflexoSol(device, light);

        hrTimer.startTimer();

        atomo1.animar();
        portal.animar();
        atomo2.animar();
        //portal.desligar();

        if(atomo2.distDoPonto(vector3df (15.0f, 0.0f, 0.0f)) < 5 )
        {
            if(estado)
            {
               portal.ligar(3);
               estado = false;
            }
          else
            {
                portal.desligar();
                estado = true;
            }


        }

        driver->beginScene(true, true, SColor(0,200,200,200));
        driver->draw2DImage(fundo, position2di(0,0));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();

        hrTimer.stopTimer();
        s16 timeElp = (s16)((0.017 - hrTimer.getElapsedTime())*1000);
        if(timeElp > 0)
            device->sleep(timeElp,false);
    }
    device->drop();

    return 0;
}

