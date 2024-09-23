#ifndef WITCH_H
	#define WITCH_H
	
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
		enum CHEMICAL_ELEMENTS deck[4];//Verificar se o compilador identifica essse enum, pois est� em outro header
		int health_points;
		int coordinate_x;
		int coordinate_y;
		//-- Fun��es --// Criar fun��o para mudar a imagem?
		void (*dawWitch)(WITCH*);
		void (*destroyWitch)(WITCH*);
		// atack()
	};

	WITCH* initWitch(char image_name[]);

#endif 
