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
    IAnimatedMesh * naveMesh = smgr->getMesh("nave.x");
    IMeshSceneNode * nave = smgr->addMeshSceneNode(naveMesh);
    nave->setPosition(vector3df(6.0f, 0.0f, 0.0f));

    ///FAZ A NAVE FICAR DETECTÁVEL
    ITriangleSelector * seletor = smgr->createTriangleSelector(naveMesh, nave);
    nave->setTriangleSelector(seletor);

    ///POSIÇÃO INICIAL
    f32 navePos = 6.0f;
    f32 catraca = 0.0f;
    f32 posRaioEmissor = emissor->getPosition().Z;

    f32 tamanhoTotalLaser = posRaioEmissor - receptor->getPosition().Z;
    f32 tamanhoLaser, escala;

    while(device->run())
    {
        ///TRAÇAR O RAIO
        line3d<f32> raio;

        /// LASER CORTANDO NAVE
        raio.start = emissor->getPosition();
        raio.start.Y += 0.7f;
        raio.end = receptor->getPosition();
        raio.end.Y += 0.7f;

        ///DETECTAR COLISÃO
        static vector3df pontoAtingido;
        triangle3df faceAtingida;
        ISceneNode * objetoAtingido = 0;
        ISceneCollisionManager * detectorColisao;//DETECTOR DE COLISÃ0

        detectorColisao = smgr->getSceneCollisionManager();//DETECTOR DE COLISÃO
        objetoAtingido = detectorColisao->getSceneNodeAndCollisionPointFromRay(raio, pontoAtingido, faceAtingida, 0, 0);

        laser->setScale(vector3df(1.0f));//O TAMANHO DO LASER ANTES DA COLISÃO
        laser->setPosition(vector3df(0.0f));//POSIÇÃO QUE O LASER VAI FICAR DE ACORDO COM O LIGHTWAVE

        if(objetoAtingido)
        {
            ///LASER CORTANDO NAVE
            tamanhoLaser = posRaioEmissor - pontoAtingido.Z;//O TAMANHO DA POSIÇÃO DO EMISSOR ATÉ O PONTO ATINGIDO DO TRIANGULO DA NAVE
            escala = tamanhoLaser / tamanhoTotalLaser;//TAMANHO QUE O LASER VAI FICAR QUANDO O ABJETO FOI ATINGIDO
            laser->setScale(vector3df(1.0f, 1.0f, escala));//O TAMANHO DO LASER ELE VAI MUDAR NO COMPRIMENTO EM Z (escala)
            laser->setPosition(vector3df(0.0f, 0.0f, posRaioEmissor - tamanhoLaser / 2));//POSIÇÃO QUE O LASER IRA FICAR EM Z

            ///GIRAR CATRACA
            catraca -= 0.5f;//VELOCIDADE GIRAR CATRACA
            rotacao->setRotation(vector3df(0.0f, catraca, 0.0f));//GIRAR CATRACA EM Y
        }

        ///MOVER A NAVE
        navePos -= 0.01f;//VELOCIDADE DA NAVE

        if (navePos <= -6.0f)
            navePos = 6.0f;

        nave->setPosition(vector3df(navePos, 0.0f, 0.0f));

        ///RENDERIZAR A CENA NO IRRLICHT
        driver->beginScene(true, true, SColor(0,50,50,50));

        ///DESENHAR O RAIO NA TELA
        //driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
        //driver->draw3DLine(raio.start, raio.end, SColor(0, 255, 25, 255));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}

