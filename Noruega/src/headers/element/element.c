#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "element.h"

const int ELEMENTS_AMOUNT = 15;

enum MIX_RESULTS mixElements(enum CHEMICAL_ELEMENTS elem1,
	enum CHEMICAL_ELEMENTS elem2)
{
    // Incompatibilidade Ácida-Base
    if ((elem1 == HCl && elem2 == NaOH) || (elem1 == NaOH && elem2 == HCl) ||
        (elem1 == HCl && elem2 == H2SO4) || (elem1 == H2SO4 && elem2 == HCl) ||
        (elem1 == HCl && elem2 == HNO3) || (elem1 == HNO3 && elem2 == HCl) ||
        (elem1 == H2SO4 && elem2 == NaOH) || (elem1 == NaOH && elem2 == H2SO4) ||
        (elem1 == H2SO4 && elem2 == HNO3) || (elem1 == HNO3 && elem2 == H2SO4) ||
        (elem1 == NaOH && elem2 == HNO3) || (elem1 == HNO3 && elem2 == NaOH) ||
        (elem1 == HCl && elem2 == NH3) || (elem1 == NH3 && elem2 == HCl) ||
        (elem1 == H2SO4 && elem2 == NH3) || (elem1 == NH3 && elem2 == H2SO4)) {
        return ACID_BASE;
    }
    // Incompatibilidade Redox
    else if ((elem1 == Na && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Na) ||
        (elem1 == Mg && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Mg) ||
        (elem1 == Al && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Al) ||
        (elem1 == KMnO4 && elem2 == H2O2) || (elem1 == H2O2 && elem2 == KMnO4) ||
        (elem1 == Na && elem2 == KMnO4) || (elem1 == KMnO4 && elem2 == Na) ||
        (elem1 == Mg && elem2 == KMnO4) || (elem1 == KMnO4 && elem2 == Mg) ||
        (elem1 == Cl2 && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Cl2) ||
        (elem1 == HNO3 && elem2 == KMnO4) || (elem1 == KMnO4 && elem2 == HNO3)) {
        return REDOX;
    }
    // Incompatibilidade com Reatividade com Água
    else if ((elem1 == Na && elem2 == NaClO) || (elem1 == NaClO && elem2 == Na) ||
        (elem1 == Mg && elem2 == NaClO) || (elem1 == NaClO && elem2 == Mg) ||
        (elem1 == Al && elem2 == NaClO) || (elem1 == NaClO && elem2 == Al) ||
        (elem1 == Fe && elem2 == NaClO) || (elem1 == NaClO && elem2 == Fe) ||
        (elem1 == Na && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Na) ||
        (elem1 == Mg && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Mg) ||
        (elem1 == Al && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Al) ||
        (elem1 == Fe && elem2 == H2O2) || (elem1 == H2O2 && elem2 == Fe) ||
        (elem1 == Cl2 && elem2 == NaClO) || (elem1 == NaClO && elem2 == Cl2)) {
        return WATER_REACTIVITY;
    }
    // Formação de Compostos Tóxicos
    else if ((elem1 == NaClO && elem2 == NH3) || (elem1 == NH3 && elem2 == NaClO) ||
        (elem1 == Cl2 && elem2 == NH3) || (elem1 == NH3 && elem2 == Cl2) ||
        (elem1 == HCl && elem2 == NH3) || (elem1 == NH3 && elem2 == HCl) ||
        (elem1 == NaClO && elem2 == H2O2) || (elem1 == H2O2 && elem2 == NaClO) ||
        (elem1 == HCl && elem2 == H2O2) || (elem1 == H2O2 && elem2 == HCl) ||
        (elem1 == NaClO && elem2 == H2SO4) || (elem1 == H2SO4 && elem2 == NaClO) ||
        (elem1 == H2SO4 && elem2 == NH3) || (elem1 == NH3 && elem2 == H2SO4)) {
        return TOXIC_COMPOUND_FORMATION;
    }
    // Reatividade com Metais
    else if ((elem1 == HCl && elem2 == Al) || (elem1 == Al && elem2 == HCl) ||
        (elem1 == HCl && elem2 == Mg) || (elem1 == Mg && elem2 == HCl) ||
        (elem1 == HCl && elem2 == Fe) || (elem1 == Fe && elem2 == HCl) ||
        (elem1 == H2SO4 && elem2 == Al) || (elem1 == Al && elem2 == H2SO4) ||
        (elem1 == H2SO4 && elem2 == Mg) || (elem1 == Mg && elem2 == H2SO4) ||
        (elem1 == H2SO4 && elem2 == Fe) || (elem1 == Fe && elem2 == H2SO4) ||
        (elem1 == HNO3 && elem2 == Al) || (elem1 == Al && elem2 == HNO3) ||
        (elem1 == HNO3 && elem2 == Mg) || (elem1 == Mg && elem2 == HNO3) ||
        (elem1 == HNO3 && elem2 == Fe) || (elem1 == Fe && elem2 == HNO3)) {
        return METAL_REACTIVITY;
    }
    // Combinações sem incompatibilidade
    else {
        return COMPATIBLE;
    }
}

//-----------------------------------------------
//IMAGENS DE CADA ELEMENTO ----------------------
//-----------------------------------------------
ALLEGRO_BITMAP* initHCl() {
    ALLEGRO_BITMAP* HCl;
    HCl = al_load_bitmap("./images/pocoes/HCL.png");
    must_init(HCl, "Imagem de HCl");
    return HCl;
}

ALLEGRO_BITMAP* initNaOH() {
    ALLEGRO_BITMAP* NaOH;
    NaOH = al_load_bitmap("./images/pocoes/NAOH.png");
    must_init(NaOH, "Imagem de NaOH");
    return NaOH;
}

ALLEGRO_BITMAP* initH2SO4() {
    ALLEGRO_BITMAP* H2SO4;
    H2SO4 = al_load_bitmap("./images/pocoes/HSO.png");
    must_init(H2SO4, "Imagem de H2SO4");
    return H2SO4;
}

ALLEGRO_BITMAP* initKMnO4() {
    ALLEGRO_BITMAP* KMnO4;
    KMnO4 = al_load_bitmap("./images/pocoes/KMNO.png");
    must_init(KMnO4, "Imagem de KMnO4");
    return KMnO4;
}

ALLEGRO_BITMAP* initH2O2() {
    ALLEGRO_BITMAP* H2O2;
    H2O2 = al_load_bitmap("./images/pocoes/HO.png");
    must_init(H2O2, "Imagem de H2O2");
    return H2O2;
}

ALLEGRO_BITMAP* initCl2() {
    ALLEGRO_BITMAP* Cl2;
    Cl2 = al_load_bitmap("./images/pocoes/CL.png");
    must_init(Cl2, "Imagem de Cl2");
    return Cl2;
}

ALLEGRO_BITMAP* initNH3() {
    ALLEGRO_BITMAP* NH3;
    NH3 = al_load_bitmap("./images/pocoes/NH.png");
    must_init(NH3, "Imagem de NH3");
    return NH3;
}

ALLEGRO_BITMAP* initNaClO() {
    ALLEGRO_BITMAP* NaClO;
    NaClO = al_load_bitmap("./images/pocoes/NaClO.png");
    must_init(NaClO, "Imagem de NACLO");
    return NaClO;
}

ALLEGRO_BITMAP* initNa() {
    ALLEGRO_BITMAP* Na;
    Na = al_load_bitmap("./images/pocoes/NA.png");
    must_init(Na, "Imagem de Na");
    return Na;
}

ALLEGRO_BITMAP* initMg() {
    ALLEGRO_BITMAP* Mg;
    Mg = al_load_bitmap("./images/pocoes/MG.png");
    must_init(Mg, "Imagem de Mg");
    return Mg;
}

ALLEGRO_BITMAP* initAl() {
    ALLEGRO_BITMAP* Al;
    Al = al_load_bitmap("./images/pocoes/AL.png");
    must_init(Al, "Imagem de Al");
    return Al;
}

ALLEGRO_BITMAP* initHNO3() {
    ALLEGRO_BITMAP* HNO3;
    HNO3 = al_load_bitmap("./images/pocoes/HNO.png");
    must_init(HNO3, "Imagem de HNO3");
    return HNO3;
}

ALLEGRO_BITMAP* initFe() {
    ALLEGRO_BITMAP* Fe;
    Fe = al_load_bitmap("./images/pocoes/FE.png");
    must_init(Fe, "Imagem de Fe");
    return Fe;
}

ALLEGRO_BITMAP* initCu() {
    ALLEGRO_BITMAP* Cu;
    Cu = al_load_bitmap("./images/pocoes/CU.png");
    must_init(Cu, "Imagem de Cu");
    return Cu;
}

ALLEGRO_BITMAP* initAg() {
    ALLEGRO_BITMAP* Ag;
    Ag = al_load_bitmap("./images/pocoes/AG.png");
    must_init(Ag, "Imagem de Ag");
    return Ag;
}


void destroyElemento(ELEMENTO* elemento)
{
    //Destruir criações
    al_destroy_bitmap(elemento->HCl);
    al_destroy_bitmap(elemento->NaOH);
    al_destroy_bitmap(elemento->H2SO4);
    al_destroy_bitmap(elemento->KMnO4);
    al_destroy_bitmap(elemento->H2O2);
    al_destroy_bitmap(elemento->Cl2);
    al_destroy_bitmap(elemento->NH3);
    al_destroy_bitmap(elemento->NaClO);
    al_destroy_bitmap(elemento->Na);
    al_destroy_bitmap(elemento->Mg);
    al_destroy_bitmap(elemento->Al);
    al_destroy_bitmap(elemento->HNO3);
    al_destroy_bitmap(elemento->Fe);
    al_destroy_bitmap(elemento->Cu);
    al_destroy_bitmap(elemento->Ag);

    free(elemento);
}

ELEMENTO* initElemento()
{
    ELEMENTO* elemento = (ELEMENTO*)malloc(sizeof(ELEMENTO));
    must_init(elemento, "elemento");

    elemento->HCl = initHCl();
    elemento->NaOH = initNaOH();
    elemento->H2SO4 = initH2SO4();
    elemento->KMnO4 = initKMnO4();
    elemento->H2O2 = initH2O2();
    elemento->Cl2 = initCl2();
    elemento->NH3 = initNH3();
    elemento->NaClO = initNaClO();
    elemento->Na = initNa();
    elemento->Mg = initMg();
    elemento->Al = initAl();
    elemento->HNO3 = initHNO3();
    elemento->Fe = initFe();
    elemento->Cu = initCu();
    elemento->Ag = initAg();

    elemento->destroyElemento = destroyElemento;
    return elemento;
}