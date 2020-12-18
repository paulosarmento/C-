#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 32, false, false, false, 0);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNode(0, vector3df(6,6,-12), vector3df(0,0,0));

    ///GERAR UMA FONTE DE LUZ
    ILightSceneNode * luz = smgr->addLightSceneNode(0, vector3df(0.0f, 10.0f, -12.0f), SColor(255,255,255,255), 20.0f, 0);

    ///CARREGANDO OS MODELOS NO CENÁRIO
    //laser
    IMeshSceneNode * laser = smgr->addMeshSceneNode(smgr->getMesh("laser.x"));
    laser->setMaterialFlag(EMF_LIGHTING, false);

    //receptor (base)
    IMeshSceneNode * receptor = smgr->addMeshSceneNode(smgr->getMesh("receptor.x"));
    receptor->setPosition(vector3df(0.0f, 0.0f, -6.0f));

    //emissor
    IMeshSceneNode * emissor = smgr->addMeshSceneNode(smgr->getMesh("emissor.x"));
    emissor->setPosition(vector3df(0.0f, 0.0f, 6.0f));

    //rotacao
    IMeshSceneNode * rotacao = smgr->addMeshSceneNode(smgr->getMesh("rotacao.x"));
    rotacao->setParent(receptor);

    //nave
    IMeshSceneNode * nave = smgr->addMeshSceneNode(smgr->getMesh("nave.x"));
    nave->setPosition(vector3df(6.0f, 0.0f, 0.0f));

    ///DEIXA A NAVE DETECTAVEL
    ITriangleSelector * seletor = smgr->createTriangleSelector(nave->getMesh(), nave);
    nave->setTriangleSelector(seletor);


    f32 navePos = 6.0f;
    line3d<f32> raio;
    f32 catraca = 6.0f;

    while(device->run())
    {
        ///MOVER A NAVE
        navePos -= 0.01f;

        if (navePos <= -6.0f)
            navePos = 6.0f;

        nave->setPosition(vector3df(navePos, 0.0f, 0.0f));

        ///MOVER A CATRACA
        static vector3df pontoAtingido; //coordenada do ponto que foi atingido pelo raio
        triangle3df faceAtingida; //face que foi atingida (poderia ser uma mina, lava ... entendeu a malícia?)
        ISceneNode * objetoAtingido = 0; //objeto atingido é sempre falso (se acertar, mais abaixo, deixa de sê-lo)

        objetoAtingido = smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(raio,pontoAtingido, faceAtingida, 0, 0);

        if(objetoAtingido)
        {
            catraca -= 0.4f;
            rotacao->setRotation(vector3df(0.0f,catraca,0.0f));
        }

        ///RENDERIZAR A CENA NO IRRLICHT
        driver->beginScene(true, true, SColor(0,50,50,50));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}

