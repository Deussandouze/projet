#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
char tab[1000];
int diff;
int err_frappe;
}motproche;

char lettres_proches[26][7] = //def des lettres proches
{
    {'&', 'é', 'z', 's', 'q', '\0', '\0'}, //a
    {'v', 'g', 'h', 'n', '\0', '\0', '\0'}, //b
    {'x', 'd', 'f', 'v', '\0', '\0', '\0'}, //c
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
    {'b', 'h', 'j', ',', '\0', '\0', '\0'}, //n
    {'i', 'ç', 'à', 'p', 'm', 'l', 'k'}, //o
    {'o', 'à', ')', '^', 'ù', 'm', 'l'}, //p
    {'a', 'z', 's', 'x', 'w', '<', '\0'}, //q
    {'e', 'd', 'f', 'g', 't', '(', '\''}, //r
    {'q', 'a', 'z', 'e', 'd', 'x', 'w'}, //s
    {'r', 'f', 'g', 'h', 'y', '-', '('}, //t
    {'y', 'h', 'j', 'k', 'i', '_', 'è'}, //u
    {'c', 'f', 'g', 'b', '\0', '\0', '\0'}, //v
    {'<', 'q', 's', 'x', '\0', '\0', '\0'}, //w
    {'w', 's', 'd', 'c', '\0', '\0', '\0'}, //x
    {'t', 'g', 'h', 'j', 'u', 'è', '-'}, //y
    {'a', 'q', 's', 'd', 'e', '"', 'é'} //z
};


motproche erreurFrappe(motproche new_word, char* mot, int* ind, int distancereq)
{
    int find, i, x, j;
    char x2;

    find=0;
    new_word.err_frappe=0;

    if(distancereq<=3)
    {
        for(i=0; i<distancereq; i++)
        {
            x2 = mot[ind[i]];
            if(x2 >= 'A' && x2 <= 'Z')
                x = (int)x2-65;
            else if(x2 >= 'a' && x2 <= 'z')
                x = (int)x2-97;
            else x=-1;

            j = -1;
            while((j<7)&&(new_word.err_frappe==find))
            {
                j = j+1;
                if( (x>0) && (( new_word.tab[ind[i]] ) == ( lettres_proches[x][j] )) )
                {
                    new_word.err_frappe = new_word.err_frappe+1;
                    find = new_word.err_frappe;
                }
            }
        }
    }
    return new_word;
}

void tri_liste(motproche* liste_mots, int nbrMots)
{
    int i=0;
    motproche tmp, tmp2;

    while(i<nbrMots)
    {
        if(liste_mots[i].diff > liste_mots[i+1].diff)
        {
            tmp = liste_mots[i];
            tmp2 = liste_mots[i+1];
            liste_mots[i] = tmp2;
            liste_mots[i+1] = tmp;
            i=-1;
        }
        if( ((liste_mots[i].err_frappe>liste_mots[i+1].err_frappe) || (liste_mots[i].err_frappe==0)) && (liste_mots[i].diff == liste_mots[i+1].diff) &&(liste_mots[i+1].err_frappe>0) )
        {
            tmp = liste_mots[i];
            tmp2 = liste_mots[i+1];
            liste_mots[i] = tmp2;
            liste_mots[i+1] = tmp;
            i=-1;
        }
        i++;
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
    fgets(mot,1000,stdin);
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

void ajouter()
{
    FILE* ptr=NULL;
    char mot[1000];
    ptr=fopen("dico.dic","a");
    if (ptr!=NULL)
    {
        printf("Veuillez saisir le nouveau mot a ajouter au dictionnaire : ");
        fflush(stdin);
        fgets(mot,100,stdin);
        fseek(ptr,0,SEEK_END);
        fprintf(ptr,"%s",mot);
        fclose(ptr);
    }
    else printf("Impossible d'acces");

}

int affichage(int *taille,motproche *tabfinal)
{
    int pos=0,continuer,n=5,posfinal,x,choix;
    printf("%s",tabfinal[pos].tab);
    pos++;
    printf("\nEtes vous satisfait du r\202sultat (OUI=1 , NON=0) : ");
    scanf("%d",&continuer);
    if (continuer==1)
    {
        return 0;
    }
    while(pos<=(*taille) && continuer==0)
    {
        n=n*2;
        while(pos<=(*taille) && pos<=n)
        {
            x=0;
            while((tabfinal[pos].tab[x]!='\n')&&(tabfinal[pos].tab[x]!='/'))
                {
                    printf("%c",tabfinal[pos].tab[x]);
                    x++;
                }
            printf("    position[%d]",pos);
            printf("    (distance = %d |",tabfinal[pos].diff);
            printf(" err_frappe =%d)\n",tabfinal[pos].err_frappe);
            pos++;
        }
        printf("\nEtes vous satisfait d'une des propositons (OUI=1 , NON=0) : ");
        scanf("%d",&continuer);
        if(continuer==1)
        {
            printf("Saisir la position associ\202e au mot choisi : ");
            scanf("%d",&posfinal);
            printf("%s",tabfinal[posfinal].tab);
        }
    }
    if(continuer==0)
    {
        printf("Voulez vous ajouter un nouveau mot au dictionnaire ? (OUI=1 , NON=0) : ");
        scanf("%d",&choix);
        if (choix==1)
        {
            ajouter();
        }
        return -1;
    }
    return posfinal;
}

int correctionmot(char mot[1000],motproche *tabfinal,int *tailletab)
{
    FILE* fichier = NULL;
    char chaine[1000];
    int i,x,z,distance,same=0,taille,taillechaine,distancereq;
    int lettre_doublee,lettre_oublie,imot,ichaine;
    int indicesErrFrappe[3]={0,0,0};

    fichier = fopen("dico.dic","r");
    taille=taillemot(mot);

    deflimite(taille,&distancereq);
    int TAILLE_MAX=strlen(mot)+distancereq;

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
                    if(distance<=distancereq)
                    {
                        indicesErrFrappe[distance] = imot;
                    }
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
                        if(distance<=distancereq)
                        {
                            indicesErrFrappe[distance] = x;
                        }
                        x++;
                        distance++;
                    }
                }

                else if(chaine[ichaine]!='/' && chaine[ichaine]!=' ' && chaine[ichaine]!='\n' ) // test si on est bien arrivé à la fin du mot du dictionnaire récupéré
                {
                    x=ichaine;
                    while(chaine[x]!='/' && chaine[x]!=' ' && chaine[x]!='\n')
                    {
                        if(distance<=distancereq)
                        {
                            indicesErrFrappe[distance] = x;
                        }
                        x++;
                        distance++;
                    }
                }

            if(distance==0) // si le mot est trouvé, renvois le mot du dico
            {
                same=1;

                strcpy(tabfinal[0].tab,chaine);
                printf("Mot trouv\202 : %s",tabfinal[0].tab);
                *tailletab=0;
                return 1;
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
                tabfinal[*tailletab] = erreurFrappe(tabfinal[*tailletab], mot, indicesErrFrappe, distancereq);
                *tailletab=(*tailletab)+1;
            }


        }
        *tailletab=(*tailletab)-1;

        fclose(fichier);

        if (same!=1)
        {
            return 0;
        }
    }
    else
    {
        printf("Impossible d'acces");
    }
    return 0;
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
    char lettre,mottext[1000],motbon[1000];
    int x=0,res,compteur;
    int i;
    if (ptr!=NULL && nouvfichier!=NULL)
    {
        i=0;
        lettre=fgetc(ptr);
        while(feof(ptr)==0)
        {
            compteur=0;
            i=0;
            while(lettre!='.' && lettre!=',' && lettre!=';' && lettre!=' ' && lettre!='ÿ' && lettre!='\n')
            {
                mottext[i]=lettre;
                i++;
                compteur++;
                lettre=fgetc(ptr);
            }
            mottext[i]='\n';
            res=correctionmot(mottext,tabfinal,&tailletab);
            if(res==0)
            {
                x=affichage(&tailletab,tabfinal);
            }
            if (x>=0)
            {
                if(res==1)x=0;
                copiemotfichier(motbon,tabfinal,x);
                copiedansfichier(nouvfichier,motbon);
            }
            else if(x<0 && res==0)
            {
                fseek(ptr,-(compteur+1),SEEK_CUR);
                lettre=fgetc(ptr);
            }
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
    char mot[1000];
    int mode,tailletab,res;
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
    fflush(stdin);
    tabfinal=(motproche*)malloc(sizeof(motproche)*300);
    switch(mode)
    {
        case 1:recupmot(mot);res=correctionmot(mot,tabfinal,&tailletab);tri_liste(tabfinal, tailletab);
        if(res==0)affichage(&tailletab,tabfinal);
        break;                   // correcteur de mot un à un
        case 2:correctionfichier(tabfinal,tailletab);break;   // correction d'un fichier txt
    }

    return 0;
}
