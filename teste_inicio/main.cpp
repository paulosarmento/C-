/*
O programa vai mostrar como usar o
fundamentos da VideoDriver, o GUIEnvironment ea
SceneManager.

Para utilizar o motor, vamos ter que incluir o arquivo cabe�alho
irrlicht.h, que pode ser encontrado no Irrlicht Engine SDK
diret�rio \ include.
*/
#include <irrlicht.h>
#include <math.h>

/*
Na Irrlicht Engine, tudo pode ser encontrado no namespace
'irr'. Ent�o, se voc� quiser usar uma classe do motor, voc� tem que
escrever um irr:: antes do nome da classe. Por exemplo, para uso
a escrever IrrlichtDevice: irr:: IrrlichtDevice. Para se livrar da
irr:: na frente do nome de cada classe, diremos ao compilador
que usamos namespace que a partir de agora, e n�s n�o ter� que
escrever que "irr::.
*/
using namespace irr;

/*
H� 5 sub namespaces na Irrlicht Engine. D� uma olhada
para eles, voc� pode ler uma descri��o detalhada delas na
documenta��o clicando em 'Lista Namespace' o item do menu superior
ou usar este link: http://irrlicht.sourceforge.net/docu/namespaces.html.
Como o espa�o para nome irr, n�o queremos que estes 5 namespaces sub agora,
para manter este exemplo simples. Por isso dizemos que o compilador novamente
que n�s n�o queremos sempre para escrever os seus nomes:
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
Este � o m�todo principal. Podemos usar void main () em cada plataforma.
Em plataformas Windows, n�s tamb�m podemos usar o m�todo WinMain
se n�s queremos nos livrar da janela do console, que aparece quando
iniciar um programa com main (), mas para manter esse exemplo simples,
usamos main ().
*/

class MyEventReceiver : public IEventReceiver
{
public:
	// Este � o m�todo que temos que implementar
	virtual bool OnEvent(const SEvent& event)
	{
		// Lembre-se cada chave � baixo ou para cima
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// Isto � usado para verificar se uma tecla est� sendo pressionad
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
	// N�s usamos essa matriz para armazenar o estado atual de cada chave
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

bool pulo(IAnimatedMeshSceneNode * node)
{
    static float num = 0.0f;
    if(num >= 20.0f)
        return false;
    num += 0.1f;
    node->setPosition(vector3df(0.0f, num, 0.0f));
    return true;
    if(num <= 20.0f)
    {
        num -= 0.1f;
        node->setPosition(vector3df(0.0f, num, 0.0f));
        return true;
    };
    return false;

};

int main()
{
    MyEventReceiver receiver;//recebe valores do teclado com esta classe

    /*
    A fun��o mais importante do motor � o "CreateDevice '
     fun��o. O dispositivo de Irrlicht pode ser criado com ela, que � o
     objeto raiz para fazer tudo com o motor.
     CreateDevice () tem 7 paramters:
     deviceType: Tipo de dispositivo. Isto pode ser actualmente o dispositivo nulo,
        o dispositivo de Software, DirectX8, DirectX9, ou OpenGL. Neste exemplo, usamos
        EDT_SOFTWARE, mas para testar, voc� pode querer mud�-lo para
        EDT_NULL, EDT_DIRECTX8, EDT_DIRECTX9, ou EDT_OPENGL.
     WindowSize: tamanho da janela ou FullscreenMode a ser criado. nesta
        exemplo, n�s usamos 640x480.
     bits: quantidade de bits por pixel quando em modo de tela cheia. isso deve
        ser de 16 ou 32. Este par�metro � ignorado quando executado em modo janela.
     fullscreen: Especifica se quisermos que o dispositivo para ser executado em modo de tela cheia
        ou n�o.
     stencilbuffer: Especifica se quisermos usar o stencil buffer para sombras de desenho.
     vsync: Especifica se queremos ter vsync ativado, este s� � �til em fullscreen
       modo.
     eventReceiver: um objeto para receber eventos. N�s n�o queremos usar essa
        par�metro aqui, e configur�-lo para 0.
    */

    IrrlichtDevice *device =
        createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 32,//LINHA GERA O DISPOSITIVO 3D
            false, false, false, &receiver);//passa-se um ponteiro para (receiver) para permitir ler teclado

/*---------------------------------
---------------------------------
EDT_SOFTWARE===processamento grafico por software
EDT_OPENGL==processamento grafico por hardware
dimension2d==
<u32>==template
(640, 480)==tamanho da tela
16==bits por pixel
1�false==op��o tela cheia
2�false==
3�false==
0==ponteiro para receber valor do teclado
-------------------
-------------------*/


    /*
    Definir o t�tulo da janela para algum texto legal. Observe que h�
     um 'L' na frente da cadeia. O Irrlicht Engine usa caracteres de largura
     strings ao exibir texto.
    */
    device->setWindowCaption(L"Teste Irrlicht");//coloca titulo na barra

    /*
    Obter um ponteiro para o driver de v�deo, o SceneManager ea
     ambiente de interface gr�fica do usu�rio, de modo que
     que nem sempre tem que escrever device-> getVideoDriver (),
     device-> getSceneManager () e dispositivo-> getGUIEnvironment ().
    */
    IVideoDriver* driver = device->getVideoDriver();//escreve comandos diretamente no driver de video
    ISceneManager* smgr = device->getSceneManager();//SMGR=gerenciador de cenas
    IGUIEnvironment* guienv = device->getGUIEnvironment();//gerenciamento de interface grafica do usuario

    /*
    N�s adicionamos uma etiqueta Ol� mundo para a janela, usando o ambiente de GUI.
    */
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<int>(10,10,200,22), true);

    /*
    Para mostrar algo interessante, vamos carregar um modelo de Quake 2
     e exibi-lo. S� temos que come�ar a malha da cena
     Manager (getMesh ()) e adicionar um SceneNode para exibir a malha.
     (addAnimatedMeshSceneNode ()). Em vez de escrever o nome do arquivo
     sydney.md2, tamb�m seria poss�vel carregar um arquivo de objeto Maya
     (. obj), um mapa completo Quake3 (. bsp) ou um arquivo Milshape (. ms3d).
     By the way, que legal Quake 2 modelo chamado sydney foi modelado
     por Brian Collins.
    */
    IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");//coloca-se objetos 3d animados NA MEMORIA
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );//CONTROLA OBJETOS QUE JA EST�O CARREGADOS NA MEMORIA, NA TELA

    /*
    Para permitir que a malha olhar um pouco mais agrad�vel, mudamos seu material uma
     pouco: N�s desativar ilumina��o, porque n�o temos uma luz din�mica
     aqui, e da malha seria totalmente preto. Ent�o definir o quadro
     loop, para que a anima��o � repetida entre os 0 e 310 frames.
     E, finalmente, n�s aplicamos uma textura para a malha. Sem ele a malha
     seria desenhado usando apenas uma cor.
    */
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setFrameLoop(0, 310);
        node->setMaterialTexture( 0, driver->getTexture("sydney.bmp") );
    }

    /*
    Olhar para a malha, n�s colocamos uma c�mera no espa�o 3D na posi��o
     (0, 30, -40). A c�mera olha de l� para (0,5,0).
    */
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    /*
    Ok, agora temos um conjunto de cena, permite desenhar tudo:
     Corremos o dispositivo em um loop while (), at� que o dispositivo n�o
     quero correr mais. Isso seria quando o usu�rio fechou a janela
     ou pressionado ALT + F4 no windows.
    */

    //vector3df posicao(0.0f);
    //float num;

    float coordX = 0.0f;
    float coordY = 0.0f;
    bool pular = false;

    while(device->run())//aqui come�a a rodar o game
    {

        pulo(node);

        /*if(receiver.IsKeyDown(KEY_KEY_D))
            coordX ++;

        node->setPosition(vector3df(coordX, coordY, 0.0f));

        if(receiver.IsKeyDown(KEY_KEY_A))
            coordX --;

        node->setPosition(vector3df(coordX, coordY, 0.0f));

        if(receiver.IsKeyDown(KEY_KEY_W))
            coordY ++;

        node->setPosition(vector3df(coordX, coordY, 0.0f));

        if(receiver.IsKeyDown(KEY_KEY_S))
            coordY --;

        node->setPosition(vector3df(coordX, coordY, 0.0f));*/

        //float rotacao;
        //num += 0.2f;
        //node->setPosition(posicao);
        //posicao.X += 1.0f;
        //posicao.Y += sin(num);//subir e descer
       //posicao.X += cos(num);
        /*
        Qualquer coisa pode ser feita entre um BeginScene () e um EndScene ()
         chamada. O BeginScene limpa a tela com uma cor e tamb�m a
         buffer de profundidade, se quisesse. Ent�o deixamos o Scene Manager eo
         GUI Ambiente desenhar seu conte�do. Com o EndScene () chamada
         tudo � apresentado na tela.
        */
        driver->beginScene(true, true, SColor(0,200,200,200));

        //node->setRotation(vector3df(0.0f, rotacao, 0.0f));
        //rotacao += 2.0f;
        /*1� true==apaga o rastro do frame anterior
          2�*/
        smgr->drawAll();//desenha os objetos na tela
        guienv->drawAll();//desenha a interface do usuario na tela

        driver->endScene();//encerra a cena
    }

    /*
    Depois que terminar, temos que apagar o dispositivo Irrlicht
     criado antes com CreateDevice (). Na Engine Irrlicht,
     voc� ter� que excluir todos os objetos que voc� criou com um m�todo ou
     fun��o que come�a com 'criar'. O objeto � simplesmente exclu�do
     chamando -> drop ().
     Consulte a documenta��o de
     http://irrlicht.sourceforge.net//docu/classirr_1_1IUnknown.html # a3
     para mais informa��es.
    */
    device->drop();//descarrega a memoria ram

    return 0;
}

