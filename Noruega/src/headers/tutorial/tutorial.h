#ifndef TUTORIAL_H  

    #define TUTORIAL_H  

    typedef struct TUTORIAL TUTORIAL;

    struct TUTORIAL
    {
        ALLEGRO_BITMAP* cardTutorial1;
        ALLEGRO_BITMAP* cardTutorial2;
        ALLEGRO_BITMAP* cardTutorial3;

        ALLEGRO_BITMAP* cardEntidade1;
        ALLEGRO_BITMAP* cardEntidade3;
        ALLEGRO_BITMAP* cardEntidade4;
        ALLEGRO_BITMAP* cardEntidade5;

        ALLEGRO_BITMAP* book;
        ALLEGRO_BITMAP* bookAnima;

        void (*cardDraw)(int, int, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*,int);
        void (*loreDraw)(int, int, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, int);
        void (*bookDraw)(ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, int*, int, int, int, int, int);
        void (*destroyMap)(TUTORIAL*);
    };

    TUTORIAL * initTutorial();

#endif // !tutorial

