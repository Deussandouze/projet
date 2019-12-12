#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
char tab[100];
int diff;
int err_frappe;
}motproche;



void tri_liste(motproche new_word, char* mot, motproche* liste_mots, unsigned* ind, int distancereq)
{
    int find, debut, fin, x, j;
    char x2;
    int i=-1;
    while(find==0)
    {
        i = i+1;
        if(i==new_word.diff)
        {
            debut=i;
            while(find==0)
            {
                i = i+1;
                if(i==(new_word.diff+1))
                {
                    fin = i;
                    find = 1;
                }
            }
        }
    }

    char lettres_proches[26][7] = //def des lettres proches
    {
        {'&', 'é', 'z', 's', 'q'}, //a
        {'v', 'g', 'h', 'n'}, //b
        {'x', 'd', 'f', 'v'}, //c
        {'s', 'z', 'e', 'r', 'f', 'c', 'x'}, //d
        {'z', '"', '\'', 'r', 'f', 'd', 's'}, //e
        {'d', 'e', 'r', 't', 'g', 'v', 'c'}, //f
        {'f', 'r', 't', 'y', 'h', 'b', 'v'}, //g
        {'g', 't', 'y', 'u', 'j', 'n', 'b'}, //h
        {'u', '_', 'ç', 'o', 'l', 'k', 'j'}, //i
        {'h', 'y', 'u', 'i', 'k', ',', 'n'}, //j
        {'j', 'u', 'i', 'o', 'l', ';', ','}, //k
        {'k', 'i', 'o', 'p', 'm', ':', ';'}, //l
        {'l', 'o', 'p', '^', 'ù', '!', ':'}, //m
        {'b', 'h', 'j', ','}, //n
        {'i', 'ç', 'à', 'p', 'm', 'l', 'k'}, //o
        {'o', 'à', ')', '^', 'ù', 'm', 'l'}, //p
        {'a', 'z', 's', 'x', 'w', '<'}, //q
        {'e', 'd', 'f', 'g', 't', '(', '\''}, //r
        {'q', 'a', 'z', 'e', 'd', 'x', 'w'}, //s
        {'r', 'f', 'g', 'h', 'y', '-', '('}, //t
        {'y', 'h', 'j', 'k', 'i', '_', 'è'}, //u
        {'c', 'f', 'g', 'b'}, //v
        {'<', 'q', 's', 'x'}, //w
        {'w', 's', 'd', 'c'}, //x
        {'t', 'g', 'h', 'j', 'u', 'è', '-'}, //y
        {'a', 'q', 's', 'd', 'e', '"', 'é'}, //z
    };

    find=0;
    new_word.err_frappe=0;

    for(i=0; i<distancereq; i++)
    {
        x2 = mot[ind[i]];
        if(x2 >= 'A' && x2 <= 'Z')
            x = (int)x2-65;
        else if(x2 >= 'a' && x2 <= 'z')
            x = (int)x2-97;

        j = -1;
        while((j<7)&&(new_word.err_frappe==find))
        {
            j = j+1;
            if(( new_word.tab[ind[i]] ) == ( lettres_proches[x2][j] ))
            {
                new_word.err_frappe = new_word.err_frappe+1;
                find = new_word.err_frappe;
            }
        }
    }

    find=0;
    x=0;
    while(find==0)
    {
        x = fin-debut;
        if((x%2)==1)
            x = x+1;

        if((new_word.err_frappe < liste_mots[x/2].err_frappe)&&(new_word.err_frappe > liste_mots[(x/2)-1].err_frappe))
        {
            x = x/2;
            for(i=300; i>x; i--)
            {
                liste_mots[i] = liste_mots[i-1];
            }
            liste_mots[x] = new_word;
        }
        else if(new_word.err_frappe > liste_mots[x/2].err_frappe)
            debut = x/2;
        else if(new_word.err_frappe < liste_mots[x/2].err_frappe)
            fin = x/2;
    }
}

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

void recupmot(char *mot)
{
    printf("\nBienvenue dans le correcteur de mot.\n");
    printf("\nVeuillez saisir un mot  corriger : ");
    fflush(stdin);
    fgets(mot,30,stdin);
}

int taillemot(char *mot)
{
    int t=0;
    while(mot[t]!='\n')
    {
        t++;
    }
    return t;
}

void correctionmot(char mot[30],motproche *tabfinal,int *tailletab)
{
    FILE* fichier = NULL;
    char chaine[100];
    int i,x,test,z,distance,same=0,taille,taillechaine,distancereq;
    int lettre_doublee,lettre_oublie,imot,ichaine;
    int TAILLE_MAX=100;
    unsigned indices_err_frappe[3];

    fichier = fopen("dico.dic","r");
    taille=taillemot(mot);

    deflimite(taille,&distancereq);

    if (fichier!=NULL)
    {
        *tailletab=0;
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
                    else if(mot[imot+1]==chaine[ichaine+2] && mot[imot+2]==chaine[ichaine+3] && mot[imot]!=chaine[ichaine] && mot[imot]=='f') // correction du f à la place de ph, éléfant / éléphant
                    {
                        lettre_oublie+=2;
                        lettre_doublee++;
                    }
                    else if(mot[imot+2]==chaine[ichaine+1] && mot[imot+3]==chaine[ichaine+2] && mot[imot]!=chaine[ichaine] && chaine[ichaine]=='f') // correction du ph à la place du f
                    {
                        lettre_oublie++;
                        lettre_doublee+=2;
                    }
                }
                else // même mode de correction mais avec une précision moins élevée
                {
                    if(mot[imot+1]==chaine[ichaine] && mot[imot]!=chaine[ichaine])
                    {
                        lettre_doublee++;
                    }
                    else if(mot[imot]==chaine[ichaine+1] && mot[imot]!=chaine[ichaine])
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot+1]==chaine[ichaine+2]  && mot[imot]!=chaine[ichaine] && mot[imot]=='f')
                    {
                        lettre_oublie+=2;
                        lettre_doublee++;
                    }
                    else if(mot[imot+2]==chaine[ichaine+1] && mot[imot]!=chaine[ichaine] && chaine[ichaine]=='f')
                    {
                        lettre_oublie++;
                        lettre_doublee+=2;
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

                strcpy(tabfinal[0].tab,chaine);
                printf("%s",tabfinal[0].tab);
                *tailletab=0;
            }
            else if(distance<=distancereq) //Copie dus mots proche du dico dans un tableau de struct
            {

                tabfinal[*tailletab].diff=distance;
                z=0;
                while(chaine[z]!='\n')
                {
                    tabfinal[*tailletab].tab[z]=chaine[z];
                    z++;
                }
                tabfinal[*tailletab].tab[z]=chaine[z];
                *tailletab=(*tailletab)+1;
            }


        }
        *tailletab=(*tailletab)-1;

        if (same!=1)
        {
            for(i=0;i<=*tailletab;i++) // affichage de toutes les possibilitées à l'écran
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

void copiemotfichier(char *tab,motproche *tabfinal,int x)
{
    int i=0;
    while(tabfinal[x].tab[i]!='/' && tabfinal[x].tab[i]!=' ' && tabfinal[x].tab[i]!='\n')
    {
        tab[i]=tabfinal[x].tab[i];
        i++;
    }
    tab[i]='\n';
}

void copiedansfichier(FILE* ptr,char *tab)
{
    int i=0;
    while(tab[i]!='\n')
    {
        fputc(tab[i],ptr);
        i++;
    }
}

void correctionfichier(motproche *tabfinal,int tailletab)
{
    FILE *ptr=NULL,*nouvfichier=NULL;
    ptr=fopen("texte.txt","r");
    nouvfichier=fopen("textecorrige.txt","w");
    char lettre,mottext[30],motbon[30];
    int x=0;
    motproche motcorrige[300];
    int i;
    if (ptr!=NULL && nouvfichier!=NULL)
    {
        i=0;
        lettre=fgetc(ptr);
        while(feof(ptr)==0)
        {
            i=0;
            while(lettre!='.' && lettre!=',' && lettre!=';' && lettre!=' ' && lettre!='ÿ' && lettre!='\n')
            {
                mottext[i]=lettre;
                i++;
                lettre=fgetc(ptr);
            }
            mottext[i]='\n';
            correctionmot(mottext,tabfinal,&tailletab);
            copiemotfichier(motbon,tabfinal,x);
            copiedansfichier(nouvfichier,motbon);
            while((lettre=='.' || lettre==',' || lettre==';' || lettre==' '|| lettre=='\n' )&& lettre!='ÿ')
            {
                fprintf(nouvfichier,"%c",lettre);
                lettre=fgetc(ptr);
            }

        }


        fclose(ptr);
        fclose(nouvfichier);
    }
    else
    {
        printf("Impossible d'acces");
    }
}

int main()
{
    char mot[30];
    int mode,tailletab;
    motproche* tabfinal;
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
    tabfinal=(motproche*)malloc(sizeof(motproche)*300);
    switch(mode)
    {
        case 1:recupmot(mot);correctionmot(mot,tabfinal,&tailletab);break;                   // correcteur de mot un à un
        case 2:correctionfichier(tabfinal,tailletab);break;   // correction d'un fichier txt
    }

    return 0;
}
