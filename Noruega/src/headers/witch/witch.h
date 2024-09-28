#ifndef WITCH_H
	#define WITCH_H
	
	extern const int DECK_SIZE;

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
		enum CHEMICAL_ELEMENTS * deck;//Verificar se o compilador identifica essse enum, pois está em outro header
		int health_points;
		int coordinate_x;
		int coordinate_y;
		//-- Funções --// Criar função para mudar a imagem?
		void (*dawWitch)(WITCH*);
		void (*destroyWitch)(WITCH*);
		// atack()
	};

	WITCH* initWitch(char image_name[], int coordinate_x, int coordinate_y);

#endif 

