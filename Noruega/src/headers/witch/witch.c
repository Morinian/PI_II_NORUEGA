#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../element/element.h"
#include "../random/random.h"
#include "witch.h"
#include "../general/general.h"

const int DECK_SIZE = 4;

enum DAMAGE_STRENGTH getDamageStrenght(enum MIX_RESULTS chemical_reaction,
        enum WITCH_TYPE witch_type)
{
    if ((witch_type == FIRE && chemical_reaction == ACID_BASE) ||
        (witch_type == WATER && (chemical_reaction == REDOX ||
            chemical_reaction == TOXIC_COMPOUND_FORMATION)))
        return SUPER_EFFECTIVE;
  
    if ((witch_type == WATER && chemical_reaction == ACID_BASE) ||
        (witch_type == FIRE && chemical_reaction == REDOX) ||
        (witch_type == GROUND && chemical_reaction == TOXIC_COMPOUND_FORMATION))
        return NORMAL;

    if ((witch_type == FIRE && chemical_reaction == TOXIC_COMPOUND_FORMATION) ||
        (witch_type == GROUND && (chemical_reaction == ACID_BASE ||
            chemical_reaction == REDOX)))
        return NOT_EFFECTIVE;
}

void atack(WITCH* attacker, WITCH* target, 
        enum CHEMICAL_ELEMENTS chosen_element,
        enum CHEMICAL_ELEMENTS central_element)
{
    enum MIX_RESULTS chemical_reaction = mixElements(chosen_element, central_element);
    
    if (chemical_reaction == COMPATIBLE)
    {
        if (attacker->base_health > attacker->health_points)
        {
            printf_s("\nO Atacante ganhou mais 10 de vida");
            attacker->health_points += 10;
        }
        else
        {
            printf_s("\nA vida do Atacante ja esta no maximo");
        }
    }
    else if (chemical_reaction == METAL_REACTIVITY)
    {
        if (target->damage_received_multiplier <= 1.8)
        {
            printf_s("\nDefesa do oponente diminuida em 20 PORCENTO");
            target->damage_received_multiplier += 0.2;
        }
        else
            printf_s("\nNão é possível abaixar mais a defesa do oponente");
    }
    else if (chemical_reaction == WATER_REACTIVITY)
    {
        if (attacker->damage_received_multiplier >= 0.2)
        {
            printf_s("\nDefesa do atacante aumentada em 20 PORCENTO");
            attacker->damage_received_multiplier -= 0.2;
        }
        else
            printf_s("\nNão é possível aumentar mais a defesa do atacante");
    }
    else
    {
        int damage = getDamageStrenght(chemical_reaction, target->type) * target->damage_received_multiplier;
        target->health_points -= damage;
        printf_s("\nDano causado pelo atacante no oponente: %i", damage);
    }

}


ALLEGRO_BITMAP* initWitchSprite(char image_path[])
{
    // Carregar o sprite da bruxa
    ALLEGRO_BITMAP* sprite;
    sprite = al_load_bitmap(image_path);
    must_init(sprite, "Imagem da Bruxa");
    return sprite;
}

void changeWitchSprite(WITCH * witch, char image_path[])
{
    if (witch->sprite)
        al_destroy_bitmap(witch->sprite);
    witch->sprite = initWitchSprite(image_path);
}

//ANIMAÇÃO bruxa
float frame = 0.f;
void drawWitch(WITCH* witch)
{
    frame += 0.1f;
    if (frame > 2) {
        frame = 0;
    }
    al_draw_bitmap_region(witch->sprite, witch->sprite_frames[0] * (int)frame, 0,
        witch->sprite_frames[0], witch->sprite_frames[1], witch->coordinate_x, witch->coordinate_y, 0);
}

void destroyWitch(WITCH* witch)
{
    al_destroy_bitmap(witch->sprite);
    free(witch->deck);
    free(witch->sprite_frames);
    free(witch);
}


WITCH* initWitch(char image_path[], int coordinate_x, int coordinate_y, int health_points, enum WITCH_TYPE type)
{
    WITCH* witch = malloc(sizeof(WITCH));
    must_init(witch, "WITCH");
    int* sprite_frames = calloc(2, sizeof(int));

    witch->sprite_frames = sprite_frames;
    witch->sprite = initWitchSprite(image_path);
    witch->changeWitchSprite = changeWitchSprite;
    witch->drawWitch = drawWitch;
    witch->destroyWitch = destroyWitch;
    witch->coordinate_x = coordinate_x;
    witch->coordinate_y = coordinate_y;
    witch->damage_received_multiplier = 1.0;
    witch->health_points = health_points;
    witch->base_health = health_points;
    witch->type = type;
    witch->deck = (enum CHEMICAL_ELEMENTS *) generateRandomIntArrayInRange(DECK_SIZE, ELEMENTS_AMOUNT);
    witch->atack = atack;
    return witch;
}