#ifndef MAPA_H  

    #define MAPA_H  

    typedef struct MAPA MAPA;

    struct MAPA
    {
        ALLEGRO_BITMAP* backgroundMap;

        void (*drawMap)(int, int, ALLEGRO_BITMAP*);

        void (*destroyMap)(MAPA*);
    };

    MAPA * initMapa();

#endif // !mapa

