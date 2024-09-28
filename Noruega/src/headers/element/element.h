#ifndef ELEMENT_H

	#define ELEMENT_H
	
	enum MIX_RESULTS
	{
		COMPATIBLE,
		//Cinco tipos de incompatibilidades
		ACID_BASE,
		REDOX,
		WATER_REACTIVITY,
		TOXIC_COMPOUND_FORMATION,
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
