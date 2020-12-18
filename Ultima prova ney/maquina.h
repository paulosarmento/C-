#ifndef __AVALIACAO_MAQUINA_INCLUIDO__
#define __AVALIACAO_MAQUINA_INCLUIDO__

#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class maquina
{
    private:
    IrrlichtDevice * device;
    IMeshSceneNode * portal;
    bool ligado;
    f32 rotacao;
    f32 velocidade;

    public:
    maquina(IrrlichtDevice * IrrDevice, f32 pos);
    void ligar(f32 veloc);
    void animar();
    void desligar();
};

#endif
