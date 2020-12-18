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
	// Este é o método que temos que implementar
	virtual bool OnEvent(const SEvent& event)
	{
		// Lembre-se cada chave é baixo ou para cima
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// Isto é usado para verificar se uma tecla está sendo pressionad
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
	// Nós usamos essa matriz para armazenar o estado atual de cada chave
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main()
{
    MyEventReceiver receiver;//recebe valores do teclado com esta classe

    IrrlichtDevice *device =  createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNode(0, vector3df(110,80,-170), vector3df(0,0,-60));

    //adicionando pecas
    IMesh * fuselagemMesh = smgr->getMesh("modelo/fuselagem.x");
    IMeshSceneNode * fuselagem = smgr->addMeshSceneNode(fuselagemMesh);
    fuselagem->setMaterialFlag(EMF_LIGHTING, false);

    IMesh * asaSDMesh = smgr->getMesh("modelo/asa_supDir.x");
    IMeshSceneNode * asaSD = smgr->addMeshSceneNode(asaSDMesh);
    asaSD->setMaterialFlag(EMF_LIGHTING, false);
    asaSD->setRotation(vector3df(0.0f, 0.0f, -15.0f));

    IMesh * asaSEMesh = smgr->getMesh("modelo/asa_supEsq.x");
    IMeshSceneNode * asaSE = smgr->addMeshSceneNode(asaSEMesh);
    asaSE->setMaterialFlag(EMF_LIGHTING, false);
    asaSE->setRotation(vector3df(0.0f, 0.0f, 15.0f));

    IMesh * asaIDMesh = smgr->getMesh("modelo/asa_infDir.x");
    IMeshSceneNode * asaID = smgr->addMeshSceneNode(asaIDMesh);
    asaID->setMaterialFlag(EMF_LIGHTING, false);
    asaID->setRotation(vector3df(0.0f, 0.0f, 15.0f));

    IMesh * asaIEMesh = smgr->getMesh("modelo/asa_infEsq.x");
    IMeshSceneNode * asaIE = smgr->addMeshSceneNode(asaIEMesh);
    asaIE->setMaterialFlag(EMF_LIGHTING, false);
    asaIE->setRotation(vector3df(0.0f, 0.0f, -15.0f));

    float num = -15.0f;
    float num1 = 15.0f;
    float num2 = 15.0f;
    float num3 = -15.0f;
    float desloc = 0.05f;
    bool fechar = false;
    bool abrir = false;

    while(device->run())
    {
        if(receiver.IsKeyDown(KEY_SPACE))
        {
            if(num <= -15)
            {
                fechar = true;
                abrir = false;
            };
            if(num >= 0)
            {
                abrir = true;
                fechar = false;
            };
        };

        if(fechar && num <= 0)
        {
            num += desloc;
            asaSD->setRotation(vector3df(0.0f, 0.0f, num));
            num1 -= desloc;
            asaSE->setRotation(vector3df(0.0f, 0.0f, num1));
            num2 -= desloc;
            asaID->setRotation(vector3df(0.0f, 0.0f, num2));
            num3 += desloc;
            asaIE->setRotation(vector3df(0.0f, 0.0f, num3));
            if(num >= -2)
            {
                desloc = 0.01f;
            }

        }
        else
        {
            fechar = false;
        };
        if(abrir && num >= -15)
        {
            desloc = 0.05f;
            num -= desloc;
            asaSD->setRotation(vector3df(0.0f, 0.0f, num));
            num1 += desloc;
            asaSE->setRotation(vector3df(0.0f, 0.0f, num1));
            num2 += desloc;
            asaID->setRotation(vector3df(0.0f, 0.0f, num2));
            num3 -= desloc;
            asaIE->setRotation(vector3df(0.0f, 0.0f, num3));
        }
        else
            abrir = false;


        driver->beginScene(true, true, SColor(0,200,200,200));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}

