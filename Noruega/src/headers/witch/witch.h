#ifndef WITCH_H
	#define WITCH_H
	
	extern const int DECK_SIZE;

	enum DAMAGE_STRENGTH
	{
		NOT_EFFECTIVE = 15,
		NORMAL = 30,
		SUPER_EFFECTIVE = 45
	};

	enum WITCH_TYPE
	{
		WATER,
		FIRE,
		GROUND
	};

	typedef struct WITCH WITCH;
	struct  WITCH
	{
		//-- Atributos-- //
		enum WITCH_TYPE type;
		ALLEGRO_BITMAP* sprite;
		enum CHEMICAL_ELEMENTS * deck;
		int health_points;
		float damage_received_multiplier;
		int coordinate_x;
		int coordinate_y;
		//-- Funções --// Criar função para mudar a imagem?
		void (*drawWitch)(WITCH*);
		void (*destroyWitch)(WITCH*);
		// atack()
		void (*atack)(WITCH*, WITCH*, enum CHEMICAL_ELEMENTS, enum CHEMICAL_ELEMENTS);
	};

	WITCH* initWitch(char image_path[], int coordinate_x, int coordinate_y, int health_points, enum WITCH_TYPE type);

#endif 

