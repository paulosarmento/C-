#include"vaivem.h"

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

    smgr->addCameraSceneNode(0, vector3df(0,12,12), vector3df(0.0f)); //adicionando câmera
    smgr->addLightSceneNode(0, vector3df(10,10,5), SColor(255,255,255,255), 20.0f, 0); //adicionando luz

    IMeshSceneNode * seta = smgr->addMeshSceneNode(smgr->getMesh("seta.x")); //carregando a seta
    IMeshSceneNode * bolinha = smgr->addMeshSceneNode(smgr->getMesh("bolinha.x")); //carregando a bolinha
    vector3df bolPosicao (0.0f, 0.0f, -6.0f); //posicao da bolinha com relacao ao 0,0,0 do cenário
    //vector3df bolPosTransf; //vetor que vai receber a transformacao

    //f32 rotacao = 0.0f; //float para fazer a setinha girar (nada de misterioso aqui)
    f32 vai; //posição inicial da bolinha
    bool vv = true;    //condição da bolinha

    while(device->run())
    {
        bola topera (0.3, bolinha, 0.8f , 0);

        topera.SetTamanho(0.7);
        topera.SetPosZ(0.0f);
        if(vv)
        {
            vai -= 0.01;
            topera.SetPosZ(vai);
            if(vai <= -12.0f)
            vv = false;
        }
       // bolinha.SetPos(5.0f);
//        if(vv)  //aqui a bolinha vai
//        {
//            vaivem -= 0.01;
//            bolPosicao = vector3df (0.0f, 0.0f, vaivem);
//            if(vaivem <= -6.0f)
//                vv = false;
//        }
//        else    //aqui a bolinha vem
//        {
//            vaivem += 0.01;
//            bolPosicao = vector3df(0.0f, 0.0f, vaivem);
//            if(vaivem >= -2.5f)
//                vv = true;
//        }
//
//        rotacao += 0.1f; //rodando a seta
//        seta->setRotation(vector3df(0.0f,rotacao,0.0f));
//        seta->setPosition(vector3df(0.0f, sin(rotacao * 3.1416/ 180), 0.0f)); //movendo pra cima e pra baixo (só pra dar efeito)
//        CMatrix4<f32> matriz = seta->getAbsoluteTransformation(); //obtendo a MATRIZ DE TRANSFORMAÇÃO da seta
//        matriz.transformVect(bolPosTransf, bolPosicao); //transformando 'bolPosicao' em 'bolPosTransf'
//
//
//        bolinha->setPosition(bolPosTransf); //setando na bolinha

        //DAQUI PRA FRENTE, TUDO CONHECIDO

        driver->beginScene(true, true, SColor(0,200,200,200));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}

