/*
O programa vai mostrar como usar o
fundamentos da VideoDriver, o GUIEnvironment ea
SceneManager.

Para utilizar o motor, vamos ter que incluir o arquivo cabeçalho
irrlicht.h, que pode ser encontrado no Irrlicht Engine SDK
diretório \ include.
*/
#include <irrlicht.h>
#include <math.h>

/*
Na Irrlicht Engine, tudo pode ser encontrado no namespace
'irr'. Então, se você quiser usar uma classe do motor, você tem que
escrever um irr:: antes do nome da classe. Por exemplo, para uso
a escrever IrrlichtDevice: irr:: IrrlichtDevice. Para se livrar da
irr:: na frente do nome de cada classe, diremos ao compilador
que usamos namespace que a partir de agora, e nós não terá que
escrever que "irr::.
*/
using namespace irr;

/*
Há 5 sub namespaces na Irrlicht Engine. Dê uma olhada
para eles, você pode ler uma descrição detalhada delas na
documentação clicando em 'Lista Namespace' o item do menu superior
ou usar este link: http://irrlicht.sourceforge.net/docu/namespaces.html.
Como o espaço para nome irr, não queremos que estes 5 namespaces sub agora,
para manter este exemplo simples. Por isso dizemos que o compilador novamente
que nós não queremos sempre para escrever os seus nomes:
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
Este é o método principal. Podemos usar void main () em cada plataforma.
Em plataformas Windows, nós também podemos usar o método WinMain
se nós queremos nos livrar da janela do console, que aparece quando
iniciar um programa com main (), mas para manter esse exemplo simples,
usamos main ().
*/

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
    A função mais importante do motor é o "CreateDevice '
     função. O dispositivo de Irrlicht pode ser criado com ela, que é o
     objeto raiz para fazer tudo com o motor.
     CreateDevice () tem 7 paramters:
     deviceType: Tipo de dispositivo. Isto pode ser actualmente o dispositivo nulo,
        o dispositivo de Software, DirectX8, DirectX9, ou OpenGL. Neste exemplo, usamos
        EDT_SOFTWARE, mas para testar, você pode querer mudá-lo para
        EDT_NULL, EDT_DIRECTX8, EDT_DIRECTX9, ou EDT_OPENGL.
     WindowSize: tamanho da janela ou FullscreenMode a ser criado. nesta
        exemplo, nós usamos 640x480.
     bits: quantidade de bits por pixel quando em modo de tela cheia. isso deve
        ser de 16 ou 32. Este parâmetro é ignorado quando executado em modo janela.
     fullscreen: Especifica se quisermos que o dispositivo para ser executado em modo de tela cheia
        ou não.
     stencilbuffer: Especifica se quisermos usar o stencil buffer para sombras de desenho.
     vsync: Especifica se queremos ter vsync ativado, este só é útil em fullscreen
       modo.
     eventReceiver: um objeto para receber eventos. Nós não queremos usar essa
        parâmetro aqui, e configurá-lo para 0.
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
1ºfalse==opção tela cheia
2ºfalse==
3ºfalse==
0==ponteiro para receber valor do teclado
-------------------
-------------------*/


    /*
    Definir o título da janela para algum texto legal. Observe que há
     um 'L' na frente da cadeia. O Irrlicht Engine usa caracteres de largura
     strings ao exibir texto.
    */
    device->setWindowCaption(L"Teste Irrlicht");//coloca titulo na barra

    /*
    Obter um ponteiro para o driver de vídeo, o SceneManager ea
     ambiente de interface gráfica do usuário, de modo que
     que nem sempre tem que escrever device-> getVideoDriver (),
     device-> getSceneManager () e dispositivo-> getGUIEnvironment ().
    */
    IVideoDriver* driver = device->getVideoDriver();//escreve comandos diretamente no driver de video
    ISceneManager* smgr = device->getSceneManager();//SMGR=gerenciador de cenas
    IGUIEnvironment* guienv = device->getGUIEnvironment();//gerenciamento de interface grafica do usuario

    /*
    Nós adicionamos uma etiqueta Olá mundo para a janela, usando o ambiente de GUI.
    */
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<int>(10,10,200,22), true);

    /*
    Para mostrar algo interessante, vamos carregar um modelo de Quake 2
     e exibi-lo. Só temos que começar a malha da cena
     Manager (getMesh ()) e adicionar um SceneNode para exibir a malha.
     (addAnimatedMeshSceneNode ()). Em vez de escrever o nome do arquivo
     sydney.md2, também seria possível carregar um arquivo de objeto Maya
     (. obj), um mapa completo Quake3 (. bsp) ou um arquivo Milshape (. ms3d).
     By the way, que legal Quake 2 modelo chamado sydney foi modelado
     por Brian Collins.
    */
    IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");//coloca-se objetos 3d animados NA MEMORIA
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );//CONTROLA OBJETOS QUE JA ESTÃO CARREGADOS NA MEMORIA, NA TELA

    /*
    Para permitir que a malha olhar um pouco mais agradável, mudamos seu material uma
     pouco: Nós desativar iluminação, porque não temos uma luz dinâmica
     aqui, e da malha seria totalmente preto. Então definir o quadro
     loop, para que a animação é repetida entre os 0 e 310 frames.
     E, finalmente, nós aplicamos uma textura para a malha. Sem ele a malha
     seria desenhado usando apenas uma cor.
    */
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setFrameLoop(0, 310);
        node->setMaterialTexture( 0, driver->getTexture("sydney.bmp") );
    }

    /*
    Olhar para a malha, nós colocamos uma câmera no espaço 3D na posição
     (0, 30, -40). A câmera olha de lá para (0,5,0).
    */
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    /*
    Ok, agora temos um conjunto de cena, permite desenhar tudo:
     Corremos o dispositivo em um loop while (), até que o dispositivo não
     quero correr mais. Isso seria quando o usuário fechou a janela
     ou pressionado ALT + F4 no windows.
    */

    //vector3df posicao(0.0f);
    //float num;

    float coordX = 0.0f;
    float coordY = 0.0f;
    bool pular = false;

    while(device->run())//aqui começa a rodar o game
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
         chamada. O BeginScene limpa a tela com uma cor e também a
         buffer de profundidade, se quisesse. Então deixamos o Scene Manager eo
         GUI Ambiente desenhar seu conteúdo. Com o EndScene () chamada
         tudo é apresentado na tela.
        */
        driver->beginScene(true, true, SColor(0,200,200,200));

        //node->setRotation(vector3df(0.0f, rotacao, 0.0f));
        //rotacao += 2.0f;
        /*1º true==apaga o rastro do frame anterior
          2º*/
        smgr->drawAll();//desenha os objetos na tela
        guienv->drawAll();//desenha a interface do usuario na tela

        driver->endScene();//encerra a cena
    }

    /*
    Depois que terminar, temos que apagar o dispositivo Irrlicht
     criado antes com CreateDevice (). Na Engine Irrlicht,
     você terá que excluir todos os objetos que você criou com um método ou
     função que começa com 'criar'. O objeto é simplesmente excluído
     chamando -> drop ().
     Consulte a documentação de
     http://irrlicht.sourceforge.net//docu/classirr_1_1IUnknown.html # a3
     para mais informações.
    */
    device->drop();//descarrega a memoria ram

    return 0;
}

