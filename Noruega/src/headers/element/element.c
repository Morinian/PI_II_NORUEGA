#include <stdio.h>
#include "element.h"

const int ELEMENTS_AMOUNT = 15;

enum MIX_RESULTS mixElements(enum CHEMICAL_ELEMENTS elem1,
	enum CHEMICAL_ELEMENTS elem2)
{
    printf_s("\nNumeros dos elementos da mistura %i e %i --- ", elem1, elem2);
    // Incompatibilidade Ácida-Base
    if ((elem1 == HCl && elem2 == NaOH) || (elem1 == NaOH && elem2 == HCl) ||
        (elem1 == HCl && elem2 == H2SO4) || (elem1 == H2SO4 && elem2 == HCl) ||
        (elem1 == HCl && elem2 == HNO3) || (elem1 == HNO3 && elem2 == HCl) ||
        (elem1 == H2SO4 && elem2 == NaOH) || (elem1 == NaOH && elem2 == H2SO4) ||
        (elem1 == H2SO4 && elem2 == HNO3) || (elem1 == HNO3 && elem2 == H2SO4) ||
        (elem1 == NaOH && elem2 == HNO3) || (elem1 == HNO3 && elem2 == NaOH) ||
        (elem1 == HCl && elem2 == NH3) || (elem1 == NH3 && elem2 == HCl) ||
        (elem1 == H2SO4 && elem2 == NH3) || (elem1 == NH3 && elem2 == H2SO4)) {
        printf_s("Mix do tipo ACID_BASE");
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
        printf_s("Mix do tipo REDOX");
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
        printf_s("Mix do tipo WATER_REACTIVITY");
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
        printf_s("Mix do tipo TOXIC_COMPOUND_FORMATION");
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
        printf_s("Mix do tipo METAL_REACTIVITY");
        return METAL_REACTIVITY;
    }
    // Combinações sem incompatibilidade
    else {
        printf_s("Mix do tipo COMPATIBLE");
        return COMPATIBLE;
    }
}