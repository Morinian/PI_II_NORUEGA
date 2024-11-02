#ifndef FASE1_H  

    #define FASE1_H  

    typedef struct FASE1 FASE1;

    struct FASE1
    {
        ALLEGRO_BITMAP* backgroundFase1;

        void (*drawFase1)(int, int, ALLEGRO_BITMAP*);

        void (*destroyFase1)(FASE1*);
    };

    FASE1* initFase1();

#endif // !Fase1

