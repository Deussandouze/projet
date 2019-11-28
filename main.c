#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char tab[100];
int diff;
}motproche;


void deflimite(int taille,int *req) //reglage de la distance limite par rapport à la taille d'un mot
{
    if (taille<=3)
    {
        *req=1;
    }
    else if (taille>3 && taille<=7)
    {
        *req=2;
    }
    else if (taille>7)
    {
        *req=3;
    }

}

void copie(char tab[],int pos) //permet la copie d'un tableau, utile pour la traduction d'un mot
{
    int i=1;
    while(tab[pos+i]!='\n')
            {
                tab[pos+i]=tab[pos+1+i];
                i++;
            }
}

void trad(char *tab,int t) //Traduction des accents du fichier avec le même code récupéré en console
{

    int x=0,changer=1;
    while (changer!=0 || x<=t)
    {
        changer=0;
        if (tab[x]==-61 && tab[x+1]==-87) // codage du è
        {
            tab[x]=-126;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-88) // codage du è
        {
            tab[x]=-118;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-85) // codage du ë
        {
            tab[x]=-119;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-86) // codage du ê
        {
            tab[x]=-120;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-82) // codage de î
        {
            tab[x]=-116;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-81) // codage de ï
        {
            tab[x]=-117;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-76) // codage du ô
        {
            tab[x]=-109;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-92) // codage du ö
        {
            tab[x]=-108;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-94) // codage du â
        {
            tab[x]=-125;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-92) // codage du ä
        {
            tab[x]=-124;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-96) // codage du à
        {
            tab[x]=-123;
            copie(tab,x);
            changer=1;
        }
        x++;
    }


}

void correctionmot()
{
    FILE* fichier = NULL;
    char chaine[100];
    char mot[30];
    motproche tabfinal[300];
    int i,y,x,z,distance,same=0,taille,taillechaine,distancereq;
    int lettre_doublee,lettre_oublie,imot,ichaine;
    int TAILLE_MAX=100;

    fichier = fopen("dico.dic","r");
    printf("\nBienvenue dans le correcteur de mot.\n");
    printf("\nVeuillez saisir un mot  corriger : ");
    fflush(stdin);
    fgets(mot,30,stdin);
    taille=strlen(mot);
    taille-=1;

    deflimite(taille,&distancereq);

    if (fichier!=NULL)
    {
        y=0;
        while(fgets(chaine,TAILLE_MAX,fichier) != NULL && same==0)
        {
            taillechaine=strlen(chaine);
            trad(chaine,taillechaine);
            i=0;
            distance=0;
            lettre_doublee=0;
            lettre_oublie=0;
            imot=0;
            ichaine=0;
            while( mot[imot]!='\n' && chaine[ichaine]!='/' && chaine[ichaine]!=' ' && chaine[ichaine]!='\n' )
            {
                if (mot[imot]!=chaine[ichaine])
                {
                    distance+=1;
                }
                if (imot<taille-1 && ichaine<taille-1)
                {
                    if(mot[imot+1]==chaine[ichaine] && mot[imot+2]==chaine[ichaine+1] && mot[imot]!=chaine[ichaine])  // correction des lettre insérées en doubles, ex : perssonne
                    {
                        lettre_doublee++;
                    }
                    else if(mot[imot]==chaine[ichaine+1] && mot[imot+1]==chaine[ichaine+2] && mot[imot]!=chaine[ichaine]) // double lettre oubliees ex : persone
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot+1]==chaine[ichaine+2] && mot[imot+2]==chaine[ichaine+3] && mot[imot]!=chaine[ichaine]) // correction du f à la place de ph, éléfant / éléphant
                    {
                        lettre_oublie+=2;
                        lettre_doublee++;
                    }
                }
                else
                {
                    if(mot[imot+1]==chaine[ichaine] && mot[imot]!=chaine[ichaine])
                    {
                        lettre_doublee++;
                    }
                    else if(mot[imot]==chaine[ichaine+1] && mot[imot]!=chaine[ichaine])
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot+1]==chaine[ichaine+2]  && mot[imot]!=chaine[ichaine])
                    {
                        lettre_oublie+=2;
                        lettre_doublee++;
                    }
                }


                i++;
                imot=i+lettre_doublee;
                ichaine=i+lettre_oublie;
            }

            if(mot[imot]!='\n') // test si on est bien arrivé à la fin du mot saisie
                {
                    x=imot;
                    while(mot[x]!='\n')
                    {
                        x++;
                        distance++;
                    }
                }

                else if(chaine[ichaine]!='/' && chaine[ichaine]!=' ' && chaine[ichaine]!='\n' ) // test si on est bien arrivé à la fin du mot du dictionnaire récupéré
                {
                    x=ichaine;
                    while(chaine[x]!='/' && chaine[x]!=' ' && chaine[x]!='\n')
                    {
                        x++;
                        distance++;
                    }
                }

            if(distance==0) // si le mot est trouvé, renvois le mot du dico
            {
                same=1;
                printf("%s",chaine);
            }
            else if(distance<=distancereq) //Copie dus mots proche du dico dans un tableau de struct
            {
                tabfinal[y].diff=distance;
                z=0;
                while(chaine[z]!='\n')
                {
                    tabfinal[y].tab[z]=chaine[z];
                    z++;
                }
                tabfinal[y].tab[z]=chaine[z];
                y++;
            }

        }
        y=y-1;

        if (same!=1)
        {
            for(i=0;i<=y;i++) // affichage de toutes les possibilitées à l'écran
            {
                x=0;
                printf("\n");
                while(tabfinal[i].tab[x]!='\n')
                {
                    printf("%c",tabfinal[i].tab[x]);
                    x++;
                }
                 printf("   %d",tabfinal[i].diff);
            }
        }


        printf("\n\nMot trouv\202 : %d",same); // affichage si le mot àbien été trouvé
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'acces");
    }
}

int main()
{
    int mode;
    printf("Quel mode souahitez vous utiliser ?");
    printf("\n1- Mode correction de mot.\n2- Mode correction de texte.");
    printf("Veuillez entrer le mode d\202sir\202 : ");
    scanf("%d",&mode);
    while(mode!=1 && mode!=2)
    {
        printf("Saisie du mode incorrecte.\n Veuillez r\202essayer : ");
        fflush(stdin);
        scanf("%d",&mode);
    }
    switch(mode)
    {
        case 1:correctionmot();break;                   // correcteur de mot un à un
        case 2:printf("Pas encore cr\202\202");break;   // correction d'un fichier txt
    }

    return 0;
}
