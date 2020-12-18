#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main()
{
    MyEventReceiver receiver;
    ///configura��o do irrlicht
    IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, true, &receiver);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    ///configura��o da c�mera
    ICameraSceneNode * camera = smgr->addCameraSceneNode(0, vector3df(-4,7,-4), vector3df(0,0,0));
   // camera->setProjectionMatrix(camera->getProjectionMatrix(),true); //camera ortogonal: n�o tem efeito de perspectiva!

    ///coloca��o do cen�rio
    IAnimatedMesh * chaoMesh = smgr->getMesh("chao.lwo"); //CARREGAR O OBJETO 3D (ATEN��O � CONFIGURA��O DO CODE::BLOCKS)
    IMeshSceneNode * chao = smgr->addMeshSceneNode(chaoMesh); //COLOCAR NA TELA
    chao->setMaterialFlag(EMF_LIGHTING,false); //FAZER EMITIR LUZ (REMOVA ISSO QUANDO SIMULAR UMA LUZ EXTERNA)
    chao->setMaterialFlag(EMF_WIREFRAME,true); //FAZER O CEN�RIO ARAMADO (PARA VER O RELEVO)

    ///criando um seletor de tri�ngulos:
    /*
    Um seletor de triangulo � o que detecta tra�ado de raios. Repare que o nosso raio n�o detecta o
    personagem. Isso porque o seletor n�o est� associado ao personagem. No caso de tomar dano, voc�
    tem de criar um outro seletor para o personagem. A� voc� pode controlar quais colis�es ser�o
    detectadas por qual objeto.
    */
    ITriangleSelector * seletor = smgr->createTriangleSelector(chaoMesh, NULL);
    chao->setTriangleSelector(seletor);

    ///coloca��o do personagem
    IMesh * personagemMesh = smgr->getMesh("personagem.lwo");
    IMeshSceneNode * personagem = smgr->addMeshSceneNode(personagemMesh);
    personagem -> setMaterialFlag(EMF_LIGHTING,false);
    vector3df position (0,5,0); // posicao inicial do carinha que mora logo ali

    while(device->run())
    {
        driver->beginScene(true, true, SColor(0,100,100,100));
        vector3df movimento = personagem->getPosition();

        ///CONTROLE
        if(receiver.IsKeyDown(KEY_KEY_A))
            movimento.X -= 0.01f;

        if(receiver.IsKeyDown(KEY_KEY_D))
            movimento.X += 0.01f;

        if(receiver.IsKeyDown(KEY_KEY_W))
            movimento.Z += 0.01f;

        if(receiver.IsKeyDown(KEY_KEY_S))
            movimento.Z -= 0.01f;

        ///tra�ar o raio do carinha para baixo.
        line3d<f32> raio;

        raio.start = personagem->getPosition();
        raio.start.Y += 25.0f;
        raio.end = personagem->getPosition();
        raio.end.Y -= 25.0f;

        ///ver se acertou alguma coisa ...
        static vector3df pontoAtingido; //coordenada do ponto que foi atingido pelo raio
        triangle3df faceAtingida; //face que foi atingida (poderia ser uma mina, lava ... entendeu a mal�cia?)
        ISceneNode * objetoAtingido = 0; //objeto atingido � sempre falso (se acertar, mais abaixo, deixa de s�-lo)

        objetoAtingido = smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(raio,pontoAtingido, faceAtingida, 0, 0);
        personagem -> setPosition(vector3df(movimento.X, pontoAtingido.Y, movimento.Z));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}

