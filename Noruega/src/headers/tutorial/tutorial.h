#ifndef TUTORIAL_H  

    #define TUTORIAL_H  

    typedef struct TUTORIAL TUTORIAL;

    struct TUTORIAL
    {
        ALLEGRO_BITMAP* cardTutorial1;
        ALLEGRO_BITMAP* cardTutorial2;
        ALLEGRO_BITMAP* cardTutorial3;
        ALLEGRO_BITMAP* cardTutorial4;
        ALLEGRO_BITMAP* cardTutorial5;

        ALLEGRO_BITMAP* cardEntidade1;
        ALLEGRO_BITMAP* cardEntidade3;
        ALLEGRO_BITMAP* cardEntidade4;
        ALLEGRO_BITMAP* cardEntidade5;

        ALLEGRO_BITMAP* book1;
        ALLEGRO_BITMAP* book2;
        ALLEGRO_BITMAP* book3;
        ALLEGRO_BITMAP* book4;
        ALLEGRO_BITMAP* book5;
        ALLEGRO_BITMAP* bookAnimaR;
        ALLEGRO_BITMAP* bookAnimaL;

        void (*cardDraw)(int, int, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*,int);
        void (*loreDraw)(int, int, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, int);
        void (*bookDraw)(ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, int*, int, int, int, int, int);
        void (*destroyMap)(TUTORIAL*);
    };

    TUTORIAL * initTutorial();

#endif // !tutorial

