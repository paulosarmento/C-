#include "panzer.h"
#include "tools.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(320, 240), 16, true, false, false, 0);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    ICameraSceneNode * camera = smgr->addCameraSceneNode(0, vector3df(3.0f,5.0f,6.0f), vector3df(0.0f));
    ILightSceneNode * sol = smgr->addLightSceneNode(0, vector3df(10,10,5), SColor(255,255,255,255), 20.0f, 0);

    panzer * tigerI = new panzer(L"panzer_tiger_I", vector3df(0.0f, 0.0f, 0.0f), device);
    tigerI -> setVelocidade(0.05f);

    int cont = 0;

    CStopWatch hrTimer;
    while(device->run())
    {
        hrTimer.startTimer();

        switch (cont)
        {
            case 1:
                tigerI -> rodaTorreta(45.0f, true);
                break;

            case 200:
                tigerI -> setVelocidade(0.0f);
                break;

            case 600:
                tigerI -> setVelocidade(0.05f);
                break;

            case 800:
                tigerI -> disparar();
                break;

            case 1600:
                cont = 0;
                break;

            default:
            {
                if (cont > 250 && cont < 580)
                    tigerI -> girar(2);

                if (cont > 1250 && cont < 1480)
                    tigerI -> girar(1);
            }
        };

        cont ++;

        tigerI -> animar();

        driver->beginScene(true, true, SColor(0,200,200,200));

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

