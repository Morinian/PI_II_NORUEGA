#ifndef MAPA_H  

    #define MAPA_H  

    typedef struct MAPA MAPA;

    struct MAPA
    {
        ALLEGRO_BITMAP* backgroundMap;
        ALLEGRO_BITMAP* unlockedPhase2Image;
        ALLEGRO_BITMAP* unlockedPhase3Image;

        void (*drawMap)(int, int, ALLEGRO_BITMAP*);
        void (*drawShadowPhase)(int, int, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, int);

        void (*destroyMap)(MAPA*);
    };

    MAPA * initMapa();

#endif // !mapa

