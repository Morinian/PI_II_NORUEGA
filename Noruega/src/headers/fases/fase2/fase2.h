#ifndef FASE2_H  

    #define FASE2_H  

    typedef struct FASE2 FASE2;

    struct FASE2
    {
        ALLEGRO_BITMAP* backgroundFase2;

        void (*drawFase2)(int, int, ALLEGRO_BITMAP*);

        void (*destroyFase2)(FASE2*);
    };

    FASE2* initFase2();

#endif // !Fase2

