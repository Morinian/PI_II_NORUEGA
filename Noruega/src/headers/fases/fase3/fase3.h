#ifndef FASE3_H  

    #define FASE3_H  

    typedef struct FASE3 FASE3;

    struct FASE3
    {
        ALLEGRO_BITMAP* backgroundFase3;

        void (*drawFase3)(int, int, ALLEGRO_BITMAP*);

        void (*destroyFase3)(FASE3*);
    };

    FASE3* initFase3();

#endif // !Fase3

