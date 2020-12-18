#ifndef __AVALIACAO_BOLA_INCLUIDO__
#define __AVALIACAO_BOLA_INCLUIDO__

#include <irrlicht.h>
#include <math.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class bola
{
    private:
    IrrlichtDevice * device;
    ISceneManager * smgr;
    IMeshSceneNode * anel1;
    IMeshSceneNode * anel2;
    IMeshSceneNode * esfera;
    f32 raioOrbita;
    f32 velocidade;
    f32 ciclo;
    vector3df posicao;

    public:
    bola(IrrlichtDevice * IrrDevice, f32 raioDaOrbita, f32 veloc);
    void animar();
    f32 distDoPonto(vector3df ponto);
};

#endif
