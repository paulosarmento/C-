#ifndef __SENTA_A_PUA_PANZER_INCLUIDO__
#define __SENTA_A_PUA_PANZER_INCLUIDO__

#include <irrlicht.h>
#include <math.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


void limiteAngulo(float * angulo);


class panzer
{
    private:
    bool atirar; //ordem para chorar o reio
    u8 rodar; //0 não roda, 1 roda pra direita, 2 pra esquerda
    f32 torreRot; //rotacao da torre
    f32 velocidade; //velocidade atual do tanque
    f32 velocidadeFinal; //velocidade pretendida (aceleracao plena)

    ISceneNode * pivot; //o tanque é montado em cima disso
    IMeshSceneNode * blindagem;
    IMeshSceneNode * torreta;
    IMeshSceneNode * lagarta[2];
    IMeshSceneNode * canhao;
    void girarLagarta(int lagartaNum, float velocidade);

    public:
    panzer(const wchar_t * nome, vector3df posicao, IrrlichtDevice * device);
    void setVelocidade(f32 veloc);
    void rodaTorreta(f32 angulo, bool adicionar); //angulo, adicionar à rotação atual
    void girar (int direcao);
    void animar();
    void disparar();
};

#endif
