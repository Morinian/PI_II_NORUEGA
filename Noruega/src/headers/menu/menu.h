#ifndef MENU_H  

    #define MENU_H  

    typedef struct MENU MENU;

    struct MENU
    {
        ALLEGRO_BITMAP* backgroundImage;
        ALLEGRO_BITMAP* setaImage;

        void (*dawMenu)(int, int, ALLEGRO_BITMAP*);
        void (*drawSeta)(int, int, ALLEGRO_BITMAP*);

        void (*destroyMenu)(MENU*);
    };

    MENU * initMenu();

#endif // !menu

