#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void deflimite(int taille,int *req,int *max)
{
    if (taille<=3)
    {
        *req=2;
        *max=4;
    }
    else if (taille<=5)
    {
        *req=3;
        *max=6;
    }
    else if (taille<=8)
    {
        *req=5;
        *max=11;
    }
    else if(taille<=12)
    {
        *req=8;
        *max=15;
    }
    else
    {
        *req=12;
        *max=20;
    }
}

int main()
{
    FILE* fichier = NULL;
    char chaine[50];
    char mot[30];
    int i,check,x,distance,same=0,copie,taille,distancereq,distancemax;
    fichier = fopen("dico.dic","r");
    printf("Sasir mot : ");
    fflush(stdin);
    fgets(mot,30,stdin);
    taille=strlen(mot);
    taille-=1;

    deflimite(taille,&distancereq,&distancemax);

    if (fichier!=NULL)
    {
        while(fgets(chaine,50,fichier) != NULL && same==0)
        {
            copie=0;
            i=0;
            x=0;
            distance=0;
            while( mot[i]==chaine[i] && i<=taille)
            {
                i++;
                if(i>distancereq && copie==0)
                {
                   while(chaine[x]!='/' && chaine[x]!=' ')
                    {
                        x++;
                    }
                    copie=1;
                    printf("%s",chaine);
                    if ((distancemax)-x <0)
                    {
                        printf("\nFaux\n\n");
                    }

                }
            }
            if(mot[i-1]==chaine[i-1] && mot[i]=='\n' && (chaine[i]=='/' ||chaine[i+1]=='p'))
            {
                same=1;
                printf("%s",chaine);
            }

        }
        printf("%d",same);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'acces");
    }
    return 0;
}
