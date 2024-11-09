#ifndef ELEMENT_H

	#define ELEMENT_H
	
	enum MIX_RESULTS
	{
		//Vida
		COMPATIBLE,
		//Dano
		ACID_BASE,
		REDOX,
		TOXIC_COMPOUND_FORMATION,
		//Status
		WATER_REACTIVITY,
		METAL_REACTIVITY
	};

	enum CHEMICAL_ELEMENTS
	{
		HCl,
		NaOH,
		H2SO4,
		KMnO4,
		H2O2,
		Cl2,
		NH3,
		NaClO,
		Na,
		Mg,
		Al,
		HNO3,
		Fe,
		Cu,
		Ag
	};

	extern const int ELEMENTS_AMOUNT;

	enum MIX_RESULTS mixElements(enum CHEMICAL_ELEMENTS elem1,
		enum CHEMICAL_ELEMENTS elem2);
#endif
