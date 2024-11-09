#ifndef MENU_H  

    #define MENU_H  

    typedef struct MENU MENU;

    struct MENU
    {
        ALLEGRO_BITMAP* backgroundImage;
        ALLEGRO_BITMAP* arrowImage;
        ALLEGRO_BITMAP* bookMenuImage;

        void (*drawMenu)(int, int, ALLEGRO_BITMAP*);
        void (*drawArrow)(int, int, ALLEGRO_BITMAP*);
        void (*drawBookMenu)(int, int, ALLEGRO_BITMAP*);

        void (*destroyMenu)(MENU*);
    };

    MENU * initMenu();

#endif // !menu

