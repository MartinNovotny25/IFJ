#include "symtable.h"
#include <string.h>
#include "IFJ_error.h"

void symtable_init(tBSTNodePtr *RootPtr) {
    if (RootPtr == NULL)
        error_exit(ERROR_INTERNAL);
    *RootPtr = NULL;
}

int symtable_search(tBSTNodePtr RootPtr, char * K, Record *Content)	{
    if(RootPtr == NULL)
        return 0;
    else {
        if (!strcmp(RootPtr->Key, K)) {
            if (Content != NULL) {
                *Content = RootPtr->BSTNodeCont;
                return 1;
            }
            else {
                fprintf(stderr, "WARNING: Funkce BSTSearch nalezla uzel se zadanym klicem, ale jeho hodnota"
                                "nelze ulozit, protoze Content == NULL !\n");
                return 1;
            }
    }
	if (strcmp(RootPtr->Key, K) < 0)
        return symtable_search(RootPtr->RPtr, K, Content);
	else
	    return symtable_search(RootPtr->LPtr, K, Content);
    }
}

void symtable_insert(tBSTNodePtr* RootPtr, char * K, Record Content)	{
	if (RootPtr == NULL)
        error_exit(ERROR_INTERNAL);

	if (*RootPtr == NULL){ //jsme v koncovem uzlu, vytvorime zde novy uzel
        tBSTNodePtr new = (tBSTNodePtr)malloc(sizeof(struct tBSTNode));

        if (new == NULL)
            error_exit(ERROR_INTERNAL);

        new->Key = K;
		//nastveni hodnot
		new->BSTNodeCont = Content;
		new->LPtr = NULL;
		new->RPtr = NULL;
		*RootPtr = new;
		return;
	}
	else{
		if (!strcmp((*RootPtr)->Key,K)){ //narazili jsme na uzel se shodnym klicem, aktualizujeme
			(*RootPtr)->BSTNodeCont = Content;
			return;
		}
		else{
			if (strcmp((*RootPtr)->Key, K) < 0) //pokud je klic v pravem podstromu
				symtable_insert(&(*RootPtr)->RPtr, K, Content);
			else
				symtable_insert(&(*RootPtr)->LPtr, K, Content);
		}
	}
}

void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr) {
    if (RootPtr == NULL || *RootPtr == NULL)
        error_exit(ERROR_INTERNAL);

    if ((*RootPtr)->RPtr != NULL) //pokud ma uzel praveho syna
        ReplaceByRightmost(PtrReplaced, &(*RootPtr)->RPtr); //hledame prvek k vymene v pravem podstromu
    else { //nasli jsme nejpravejsi prvek
        PtrReplaced->Key = (*RootPtr)->Key;
        PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
        symtable_delete(RootPtr, (*RootPtr)->Key); //smazeme prvek
    }
}

void symtable_delete(tBSTNodePtr *RootPtr, char * K) {
    if (RootPtr == NULL)
        return; //zde pouze vypisi warning, ale mohlo by byt brano i jako error

    if (*RootPtr == NULL) //dorazili jsme na konec a nic se nenaslo, nedelame nic
        return;

    if (strcmp((*RootPtr)->Key, K) > 0) {
        symtable_delete(&(*RootPtr)->LPtr, K); //pokracujeme v hledani v levem podstromu
        return;
    }
    else if (strcmp((*RootPtr)->Key, K) < 0) {
        symtable_delete(&(*RootPtr)->RPtr, K); //pokracujeme v hledani v pravem podstromu
        return;
    }
    else { //nasli jsme uzel ke smazani
        if ((*RootPtr)->LPtr == NULL && (*RootPtr)->RPtr == NULL) { //pokud uzel nema syny
            free(*RootPtr);
            *RootPtr = NULL;
            return;
        }
        else if ((*RootPtr)->LPtr == NULL) { //pokud uzel nema leveho syna
            tBSTNodePtr del = *RootPtr;
            *RootPtr = (*RootPtr)->RPtr; //napojime jeho praveho syna na jeho otce
            free(del);
            return;
        }
        else if ((*RootPtr)->RPtr == NULL) { //pokud uzel nema praveho syna
            tBSTNodePtr del = *RootPtr;
            *RootPtr = (*RootPtr)->LPtr; //napojime jeho leveho syna na jeho otce
            free(del);
            return;
        }
        else { //uzel ma oba syny
            ReplaceByRightmost((*RootPtr), &(*RootPtr)->LPtr); //nahradime hodnotou z leveho podstromu
            return;
        }
    }
}

void symtable_dispose(tBSTNodePtr *RootPtr) {
    if (RootPtr != NULL && *RootPtr != NULL) {
        symtable_dispose(&((*RootPtr)->LPtr));
        symtable_dispose(&((*RootPtr)->RPtr));
        free(*RootPtr);
        symtable_init(RootPtr);
    }
}