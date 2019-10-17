/* ******************************* main.c ***********************************
 *  P�edm�t: Form�ln� jazyky a p�eklada�e (IFJ) - FIT VUT v Brn�
 *  N�zev projektu: Implementace p�eklada�e imperativn�ho jazyka IFJ19
 *  Auto�i: Ber�nek Tom� (xberan46) - vedouc�
 *          Haderka Martin (xhader00)
 *          Slobodn�k �imon (xslobo06)
 *          Klem Richard (xklemr00)
 *  Datum vytvo�en�: 16.10.2019
 * ************************************************************************** */

#include <stdio.h>
#include "scanner/IFJ_scanner.h"

int main (int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr, "Zadejte pouze relativni/absolutni cestu k souboru bez mezer!\n")
        return -1;
    }

    FILE* src_file = fopen(argv[1], "r");
    if (src_file == NULL)
        return -1;

    token_t token = get_token(src_file);
    while (token.type != TOKEN_EOF){


    }

    return 0;
}

/* konec souboru main.c */
