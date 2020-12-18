#include "maquina.h"

maquina::maquina(IrrlichtDevice * IrrDevice, f32 pos)
{
    device = IrrDevice;
    rotacao = 0.0f;
    velocidade = 0.0f;
    ligado = false;

    ISceneManager * smgr = device->getSceneManager();

    portal = smgr->addMeshSceneNode(smgr->getMesh("3d/maquina.x"));
    portal -> setPosition(vector3df (pos, 0.0f, 0.0f));
    portal -> setRotation(vector3df (0.0f, 90.0f, 0.0f));
};


void maquina::animar()
{
    rotacao += velocidade;
    portal -> setRotation (vector3df (00.0f, 90.0f, rotacao));

    if(rotacao > 360.0f)
        rotacao -= 360.0f;
};

void maquina::desligar()
{
    velocidade = 0.0f;
    ligado = false;
};

void maquina::ligar(f32 veloc)
{
    velocidade = veloc;
   // portal -> setRotation(vector3df(0.0f, 0.0f, veloc);

    ligado = true;
};

