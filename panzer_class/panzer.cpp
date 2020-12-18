#include "panzer.h"
#include "tools.h"

panzer::panzer(const wchar_t * nome, vector3df posicao, IrrlichtDevice * device)
{
    ISceneManager * smgr = device->getSceneManager();
    torreRot = 0.0f;
    velocidade = 0.0f;
    velocidadeFinal = 0.0f;
    rodar = 0;
    atirar = false;

    //configurando o tanque
    stringw end ("3d_obj/");
    end.append (nome);

    pivot = smgr->addEmptySceneNode();

    blindagem = smgr->addMeshSceneNode(smgr->getMesh(end + L"/blindagem.x"));
    blindagem -> setParent(pivot);

    torreta = smgr->addMeshSceneNode(smgr->getMesh(end + L"/torreta.x"));
    torreta -> setPosition(vector3df(0.0f, 1.69f, 0.29f));
    torreta -> setParent(blindagem);

    canhao = smgr->addMeshSceneNode(smgr->getMesh(end + L"/canhao.x"));
    canhao -> setParent(torreta);

    lagarta[0] = smgr->addMeshSceneNode(smgr->getMesh(end + L"/lagarta_esq.x"));
    lagarta[0] -> setPosition(vector3df(0.0f, 0.374f, 0.0f));
    lagarta[0] -> setParent(pivot);

    lagarta[1] = smgr->addMeshSceneNode(smgr->getMesh(end + L"/lagarta_dir.x"));
    lagarta[1] -> setPosition(vector3df(0.0f, 0.374f, 0.0f));
    lagarta[1] -> setParent(pivot);
};

void panzer::rodaTorreta(f32 angulo, bool adicionar)
{
    if(adicionar)
        torreRot += angulo;
    else
        torreRot = angulo;
}

void panzer::girarLagarta(int lagartaNum, float velocidade)
{
    S3DVertex * vertArray = (S3DVertex*)lagarta[lagartaNum]->getMesh()->getMeshBuffer(1)->getVertices();
    for (u8 i = 0; i < lagarta[lagartaNum] -> getMesh()->getMeshBuffer(1)->getVertexCount(); i++)
    {
        vertArray[i].TCoords.Y -= velocidade;

        //resetar as coordenadas da lagarta (tenho muita meda que se não fizer isso, vai dar m* depois de um tempo)
        if(vertArray[0].TCoords.Y > 200.0f)
            vertArray[i].TCoords.Y -= 200.0f;
        else if(vertArray[0].TCoords.Y < -200.0f)
            vertArray[i].TCoords.Y += 200.0f;
    };
}

void panzer::setVelocidade(f32 veloc)
{
    velocidadeFinal = veloc;
}

void panzer::girar(int direcao)
{
    rodar = direcao;
}

void panzer::disparar()
{
    atirar = true;
}

void panzer::animar()
{
    vector3df blindagemRot (0.0f);
    vector3df tanqueRot (0.0f);

    ///animar torreta
    vector3df torretaRotAtual = torreta->getRotation();

    //converter os dois ângulos para positivos menor que 360
    limiteAngulo(&torretaRotAtual.Y);
    limiteAngulo(&torreRot);

    if ((int)(torretaRotAtual.Y * 10) != (int)(torreRot * 10)) //se o angulo coincidir (com tolerância de 0.1f) nao gira
    {
        if (sin((torreRot - torretaRotAtual.Y) * 3.1416f / 180.0f) < 0) //definir para que lado rodar a torreta
            torreta->setRotation(vector3df(0.0f, torretaRotAtual.Y - 0.1f, 0.0f));
        else
            torreta->setRotation(vector3df(0.0f, torretaRotAtual.Y + 0.1f, 0.0f));
    };

    ///acelerar/ desacelerar o tanque
    if((velocidade - velocidadeFinal) < 0) //isso acelera ele
        velocidade += 0.001f;

    if((velocidade - velocidadeFinal) > 0) //isso desacelera ele
        velocidade -= 0.001f;


   //simular o balanco do tanque
    CMatrix4<f32> matriz = blindagem->getAbsoluteTransformation();
    static f32 balancoReto = 0.0f;
    balancoReto += velocidade * 100.0f;
    vector3df balancarReto = vector3df(sin(balancoReto * 3.1416/ 180.0f) * 0.5f, 0.0f,0.0f);

    matriz.rotateVect(balancarReto);
    blindagemRot += balancarReto;

    ///girar o tanque
    static f32 velRotacao = 0.0f;
    if (rodar != 0) //comeca a rodar
    {
        if(velRotacao < 0.1f && velRotacao > -0.1f) //velocidade máxima de rotacao, para um ou outro lado
        {
            if(rodar == 2)
                velRotacao += 0.001f;
            else
                velRotacao -= 0.001f;
        }
    }
    else
    {
        if(velRotacao < 0.0f)
            velRotacao += 0.001f;
        else
            velRotacao -= 0.001f;
    }

    //inverter a rotação das lagartas
    girarLagarta(1,-velRotacao / 2 + velocidade);
    girarLagarta(0,velRotacao / 2 + velocidade);

    //balancar o tanque
    static f32 balanco = 0.0f;
    balanco += 3.0f;
    vector3df balancar = vector3df (sin(balanco * 3.1416/ 180.0f) * 2.0f - 1.0f,
                                    0.0f,
                                    sin(balanco * 3.1416/ 180.0f));

    matriz.rotateVect(balancar);
    balancar *= (velRotacao * 10.0f);

    blindagemRot += balancar;

    f32 tanqueRotacao = pivot->getRotation().Y;
    tanqueRot.Y = tanqueRotacao + velRotacao;
    rodar = 0;

    ///chora o reio alemão!!!
    static u8 recarregar = 0;

    if(atirar && recarregar == 0) //mandou bala!
        canhao -> setPosition(vector3df(0.0f,0.0f,-0.8f));

    if(atirar) //recuperando-se do disparo
    {
        recarregar ++; //começa a contar o tempo de recarga do canhão

        //coice do canhão
        f32 coice = (f32)recarregar / 40.0f - 1.0f; //volta o canhão à posição original
        if(coice < 0.0f)
            canhao -> setPosition(vector3df(0.0f, 0.0f, coice)); //volta o canhão do coice do tiro

        //coice do tanque
        /*PERMITA-ME EXPLICAR O QUE ESTOU PENSANDO QUANDO FIZ ISSO
        recarregar varia de 0 a 180, depois para.

        a conta é essa = sin( pow(180.0f - (f32)(recarregar) , 2.0f)/45.0f * 3.1416/180) * 2;
        pow(180.0f - (f32)(recarregar) , 2.0f): isso vai variar de pow(180,2) até pow(0,2)
            ou seja, vai de 32400 até 0.

        Isso é divido por 45, então vai de 720 até 0.

        Depois é multiplicado por PI/180. Claro, para converter para Radiano (o sin funiona com rad)

        Então, o seno varia de 0 até 0 mesmo, só que, no começo, varia um montão, depois varia devagar.
        Isso reproduz bonito o coice do canhão

        */
        f32 tanqueCoiceRot;
        tanqueCoiceRot = sin( pow(180.0f - (f32)(recarregar) , 2.0f)/45.0f * 3.1416/180) * 2;

        vector3df tanqueCoice (tanqueCoiceRot, 0.0f, 0.0f); //tenho que colocar em X por causa da torreta (não capisco)
        //rodo o vetor na matriz da torreta
        CMatrix4<f32> torretaMatriz = torreta->getAbsoluteTransformation();
        torretaMatriz.rotateVect(tanqueCoice);
        blindagemRot += tanqueCoice;
    }

    if(recarregar == 180) //depois de um dois segundos, pode atirar de novo, tá liberado
    {
        recarregar = 0;
        atirar = false;
    }

    //aplicar as rotacões
    blindagem -> setRotation(blindagemRot);
    pivot -> setRotation(tanqueRot);
}
