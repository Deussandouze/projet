#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void deflimite(int taille,int *req,int *max)
{
    if (taille<=3)
    {
        *req=1;
        *max=4;
    }
    else if (taille<=5)
    {
        *req=2;
        *max=6;
    }
    else if (taille<=8)
    {
        *req=3;
        *max=11;
    }
    else if(taille<=12)
    {
        *req=4;
        *max=15;
    }
    else
    {
        *req=5;
        *max=20;
    }
}

void trad(char *tab,int t)
{
    int i=0,x=0,y=0,changer=1;
    while (changer!=0 || x<=t)
    {
        changer=0;
        if (tab[x]==-61 && tab[x+1])
        {
            tab[x]=-126;
            i=1;
            while(tab[x+i]!='\n')
            {
                tab[x+i]=tab[x+1+i];
                i++;
            }
            changer=1;
        }
        else
        {

        }
        x++;
    }
    tab[x+1]='\n';


}

void correctionmot()
{
    FILE* fichier = NULL;
    char chaine[100],car;
    char mot[30];
    char tab[100][100];
    int i,y,x,z,distance,same=0,copie,taille,distancereq,distancemax;
    int lettre_doublee,lettre_oublie,imot,ichaine;
    int TAILLE_MAX=100;

    fichier = fopen("dico.dic","r");

    printf("Saisir mot : ");
    fflush(stdin);
    fgets(mot,30,stdin);
    taille=strlen(mot);
    taille-=1;

    deflimite(taille,&distancereq,&distancemax);

    if (fichier!=NULL)
    {
        y=0;
        while(fgets(chaine,TAILLE_MAX,fichier) != NULL && same==0)
        {
            trad(chaine,TAILLE_MAX);
            i=0;
            distance=0;
            lettre_doublee=0;
            lettre_oublie=0;
            imot=0;
            ichaine=0;
            while( mot[imot]!='\n' && chaine[ichaine]!='/' && chaine[ichaine]!=' ' && chaine[ichaine]!='\n')
            {
                if (mot[imot]!=chaine[ichaine])
                {
                    distance+=1;
                }
                if(mot[imot+1]==chaine[ichaine] && mot[imot]!=chaine[ichaine])
                {
                    lettre_doublee++;
                }
                if(mot[imot]==chaine[ichaine+1] && mot[imot]!=chaine[ichaine])
                {
                    lettre_oublie++;
                }

                i++;
                imot=i+lettre_doublee;
                ichaine=i+lettre_oublie;
            }

            if(mot[imot]!='\n')
                {
                    x=imot;
                    while(mot[x]!='\n')
                    {
                        x++;
                        distance++;
                    }
                }

                else if(chaine[ichaine]!='/' && chaine[ichaine]!=' ' && chaine[ichaine]!='\n' )
                {
                    x=i;
                    while(chaine[x]!='/' && chaine[x]!=' ' && chaine[x]!='\n')
                    {
                        x++;
                        distance++;
                    }
                }

            if(distance==0)
            {
                same=1;
                printf("%s",chaine);
            }
            else if(distance<distancereq)
            {

                z=0;
                while(chaine[z]!='\n')
                {
                    tab[y][z]=chaine[z];
                    z++;
                }
                tab[y][z]=chaine[z];
                y++;
            }


        }
        y=y-1;
        if (same!=1)
        {
            for(i=0;i<=y;i++)
            {
                x=0;
                printf("\n");
                while(tab[i][x]!='\n')
                {
                    printf("%c",tab[i][x]);
                    x++;
                }
            }
        }


        printf("\n\nMot trouv\202 : %d",same);
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'acces");
    }
}

int main()
{
    int mode=0;
    printf("Quel mode souahitez vous utiliser ?");
    printf("\n1- Mode correction de mot.\n2- Mode correction de texte.");
    printf("Veuillez entrer le mode d\202sir\202 : ");
    scanf("%d",&mode);
    while(mode!=1 && mode!=2)
    {
        printf("Saisie du mode incorrecte.\n Veuillez r\202essayer : ");
        scanf("%d",&mode);
    }
    switch(mode)
    {
        case 1:correctionmot();break;
        case 2:printf("Pas encore cr\202\202");break;
    }

    return 0;
}
