#ifndef MENU_H  

    #define MENU_H  

    typedef struct MENU MENU;
    struct MENU
    {
        ALLEGRO_BITMAP* backgroundImage;
        void (*dawMenu)(int, int, ALLEGRO_BITMAP*);
        void (*destroyMenu)(MENU*);

    };

    MENU * initMenu();

#endif // !menu

