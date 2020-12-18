#include "bola.h"

bola::bola(IrrlichtDevice * IrrDevice, f32 raioDaOrbita, f32 veloc)
{
    device = IrrDevice;
    smgr = device->getSceneManager();

    esfera = smgr->addMeshSceneNode(smgr->getMesh("3d/esfera.x"));
    anel1 = smgr->addMeshSceneNode(smgr->getMesh("3d/aneis.x"));
    anel1 -> setMaterialFlag(EMF_LIGHTING, false);
    anel1 -> setMaterialFlag(EMF_BACK_FACE_CULLING, false);
    anel1 -> setParent(esfera);
    anel2 = smgr->addMeshSceneNode(smgr->getMesh("3d/aneis.x"));
    anel2 -> setMaterialFlag(EMF_LIGHTING, false);
    anel2 -> setMaterialFlag(EMF_BACK_FACE_CULLING, false);
    anel2 -> setRotation(vector3df(0.0f, 90.0f, 0.0f));
    anel2 -> setParent(esfera);

    raioOrbita = raioDaOrbita;

    esfera -> setPosition(vector3df(0.0f, 0.0f, raioOrbita));
    velocidade = veloc;
    ciclo = 0.0f;
};

void bola::animar()
{
    ciclo += velocidade;

    //posicionando a esfera
    posicao.X = sin(ciclo * 3.1416f / 180.0f) * raioOrbita;
    posicao.Y = 0.0f;
    posicao.Z = cos(ciclo * 3.1416f / 180.0f) * raioOrbita;

    esfera->setPosition(posicao);

    //rodando anel 1
    anel1 -> setRotation(vector3df(0.0f, ciclo * 2, ciclo * 4));
    anel2 -> setRotation(vector3df(ciclo * 4, 0.0f, ciclo * 0));

    if (ciclo > 360.0f)
        ciclo -= 360.0f;
};

f32 bola::distDoPonto(vector3df ponto)
{
    line3df dist(ponto, posicao);
    return dist.getLength();
};
