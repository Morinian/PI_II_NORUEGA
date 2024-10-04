#ifndef TUTORIAL_H  

    #define TUTORIAL_H  

    typedef struct TUTORIAL TUTORIAL;

    struct TUTORIAL
    {
        ALLEGRO_BITMAP* cardTutorial1;
        ALLEGRO_BITMAP* cardTutorial2;
        ALLEGRO_BITMAP* cardTutorial3;

        void (*cardDraw)(int, int, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*,int);
        void (*destroyMap)(TUTORIAL*);
    };

    TUTORIAL * initTutorial();

#endif // !tutorial

