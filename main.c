#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>


typedef struct{
char tab[100];
int diff;
int err_frappe;
}motproche;


void tri(motproche* tabfinal,int taille)
{
    motproche tmp;
	int en_desordre = 1;
	while (en_desordre)
	{
		en_desordre = 0;
		for (int j = 0; j < taille-1; j++)
		{
			if(tabfinal[j].diff > tabfinal[j+1].diff)
			{
                tmp = tabfinal[j+1];
 				tabfinal[j+1] = tabfinal[j];
 				tabfinal[j] = tmp;
				en_desordre = 1;
 			}
		}
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
        else if (tab[x]==-61 && tab[x+1]==-71) // codage du ù
        {
            tab[x]=-105;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-69) // codage du û
        {
            tab[x]=-106;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-68) // codage du ü
        {
            tab[x]=-127;
            copie(tab,x);
            changer=1;
        }
        else if (tab[x]==-61 && tab[x+1]==-89) // codage du ç
        {
            tab[x]=-121;
            copie(tab,x);
            changer=1;
        }
        x++;
    }
}

void decalage(char tab[], int pos)
{
    int i, x=1;

    while(tab[pos+x]!='\n')
    {
        x++;
    }
    for(i=x; i>=0; i--)
    {
        tab[pos+i+1]=tab[pos+i];
    }
}

void invTrad(char *tab,int t) //Retraduction des accents du fichier avec le même code récupéré en console
{

    int x=0,changer=1;
    while (changer!=0 || x<=t)
    {
        changer=0;
        if (tab[x]==-126) // décodage du è
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-87;
            changer=1;
        }
        else if (tab[x]==-118) // décodage du è
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-88;
            changer=1;
        }
        else if (tab[x]==-119) // décodage du ë
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-85;
            changer=1;
        }
        else if (tab[x]==-120) // décodage du ê
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-86;
            changer=1;
        }
        else if (tab[x]==-116) // décodage de î
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-82;
            changer=1;
        }
        else if (tab[x]==-117) // décodage de ï
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-81;
            changer=1;
        }
        else if (tab[x]==-109) // décodage du ô
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-76;
            changer=1;
        }
        else if (tab[x]==-108) // décodage du ö
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-92;
            changer=1;
        }
        else if (tab[x]==-125) // décodage du â
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-94;
            changer=1;
        }
        else if (tab[x]==-124) // décodage du ä
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-92;
            changer=1;
        }
        else if (tab[x]==-123) // décodage du à
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-96;
            changer=1;
        }
        else if (tab[x]==-105) // décodage du ù
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-71;
            changer=1;
        }
        else if (tab[x]==-106) // décodage du û
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-69;
            changer=1;
        }
        else if (tab[x]==-127) // décodage du ü
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-68;
            changer=1;
        }
        else if (tab[x]==-121) // décodage du ç
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-89;
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

void ajouter()
{
    FILE* ptr=NULL;
    char mot[100];
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
    int pos=0,continuer,n=5,posfinal,x=0,choix;
    printf("\nPremier mot propos\202 :\n");
    while(tabfinal[pos].tab[x]!=' ' && tabfinal[pos].tab[x]!='/' && tabfinal[pos].tab[x]!='\n')
    {
        printf("%c",tabfinal[pos].tab[x]);
        x++;
    }
    pos++;
    printf("\nEtes vous satisfait du r\202sultat (OUI=1 , NON=0) : ");
    scanf("%d",&continuer);
    while(continuer!=1 && continuer!=0)
    {
        printf("Veuillez saisir 0 ou 1 :");
        fflush(stdin);
        scanf("%d",&continuer);
    }

    if (continuer==1)
    {
        return 0;
    }
    while(pos<=(*taille) && continuer==0)
    {
        printf("\nMots propos\202s :\n");
        n=n*2;
        while(pos<=(*taille) && pos<=n)
        {
            x=0;
            while(tabfinal[pos].tab[x]!=' ' && tabfinal[pos].tab[x]!='/' && tabfinal[pos].tab[x]!='\n')
                {
                    printf("%c",tabfinal[pos].tab[x]);
                    x++;
                }
            printf("    position[%d]\n",pos);
            pos++;
        }
        printf("\nEtes vous satisfait d'une des propositons (OUI=1 , NON=0) : ");
        scanf("%d",&continuer);
        while(continuer!=1 && continuer!=0)
        {
            printf("Veuillez saisir 0 ou 1 :");
            scanf("%d",&continuer);
        }
        if(continuer==1)
        {
            printf("Saisir la position associ\202e au mot choisi : ");
            scanf("%d",&posfinal);
        }
    }
    if(continuer==0)
    {
        printf("Voulez vous ajouter un nouveau mot au dictionnaire ? (OUI=1 , NON=0) : ");
        scanf("%d",&choix);
        while(choix!=1 && choix!=0)
        {
            printf("Veuillez saisir 0 ou 1 :");
            scanf("%d",&choix);
        }
        if (choix==1)
        {
            ajouter();
        }
        return -1;
    }

}

int correctionmot(char mot[30],motproche *tabfinal,int *tailletab)
{
    FILE* fichier = NULL;
    char chaine[100];
    int i,x,z,compteur,distance,same=0,taille,taillechaine,distancereq;
    int lettre_doublee,lettre_oublie,imot,ichaine;
    int TAILLE_MAX=100;

    fichier = fopen("dico.dic","r");
    taille=taillemot(mot);
    mot[taille+2]='\n';
    mot[taille+3]='\n';
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
                if (imot<taille-1 && ichaine<taille-1) // permet de corriger les fautes avec un taux de vérification important
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
                        lettre_oublie++;
                    }
                    else if(mot[imot+2]==chaine[ichaine+1] && mot[imot+3]==chaine[ichaine+2] && mot[imot]!=chaine[ichaine] && chaine[ichaine]=='f') // correction du ph à la place du f
                    {
                        lettre_doublee++;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='e' && mot[imot+1]=='a' && mot[imot+2]=='u') // correction de o à la place du eau ex: véleau <=> vélo
                    {
                        lettre_doublee+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='a' && mot[imot+1]=='u') // correction de o à la place du au ex: vélau <=> vélo
                    {
                        lettre_doublee+=1;
                    }
                    else if(mot[imot]!=chaine[ichaine] && mot[imot]=='o' && chaine[ichaine]=='e' && chaine[ichaine+1]=='a' && chaine[ichaine+2]=='u') // correction de o à la place du eau ex: bato => bateau
                    {
                        lettre_oublie+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] &&  mot[imot]=='o' && chaine[ichaine]=='a' && chaine[ichaine+1]=='u') // correction de eau à la place du o ex:  hot => haut
                    {
                        lettre_oublie++;
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
                        lettre_oublie++;
                    }
                    else if(mot[imot+2]==chaine[ichaine+1] && mot[imot]!=chaine[ichaine] && chaine[ichaine]=='f')
                    {
                        lettre_doublee++;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='e' && mot[imot+1]=='a' && mot[imot+2]=='u') // correction de o à la place du eau ex: véleau <=> vélo
                    {
                        lettre_doublee+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='a' && mot[imot+1]=='u') // correction de o à la place du au ex: vélau <=> vélo
                    {
                        lettre_doublee+=1;
                    }
                    else if(mot[imot]!=chaine[ichaine] && mot[imot]=='o' && chaine[ichaine]=='e' && chaine[ichaine+1]=='a' && chaine[ichaine+2]=='u') // correction de o à la place du eau ex: bato => bateau
                    {
                        lettre_oublie+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] &&  mot[imot]=='o' && chaine[ichaine]=='a' && chaine[ichaine+1]=='u') // correction de eau à la place du o ex:  hot => haut
                    {
                        lettre_oublie++;
                    }
                }


                i++;
                ichaine=i+lettre_oublie;
                imot=i+lettre_doublee;
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
                compteur=0;
                printf("\nMot trouv\202 :");

                while(tabfinal[0].tab[compteur]!=' ' && tabfinal[0].tab[compteur]!='/' && tabfinal[0].tab[compteur]!='\n')
                {
                    printf("%c",tabfinal[0].tab[compteur]);
                    compteur++;
                }
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
        fputc(tab[i], ptr);
        i++;
    }
}

void correctionfichier(motproche *tabfinal,int tailletab)
{
    setlocale( LC_ALL, "fr_FR.UTF-8" );
    FILE *ptr=NULL,*nouvfichier=NULL;
    ptr=fopen("texte.txt","r");
    nouvfichier=fopen("textecorrige.txt","w");
    char lettre,mottext[30],motbon[30];
    int x=0,res,taille,compteur;
    int i;
    if (ptr!=NULL && nouvfichier!=NULL)
    {
        i=0;
        lettre=fgetc(ptr);
        while(feof(ptr)==0)
        {
            compteur=0;
            i=0;
            while(lettre!='.' && lettre!=',' && lettre!=';' && lettre!=' ' && lettre!='ÿ' && lettre!='\n' && lettre!='-' && lettre!='?')
            {
                mottext[i]=lettre;
                i++;
                compteur++;
                lettre=fgetc(ptr);
            }
            mottext[i]='\n';
            mottext[i+1]='\n';
            mottext[i+2]='\n';
            taille=taillemot(mottext);
            trad(mottext,taille);
            res=correctionmot(mottext,tabfinal,&tailletab);
            if(res==0)
            {
                tri(tabfinal,tailletab);
                x=affichage(&tailletab,tabfinal);
            }
            if (x>=0)
            {
                if(res==1)x=0;
                copiemotfichier(motbon,tabfinal,x);
                invTrad(motbon, tailletab);
                copiedansfichier(nouvfichier,motbon);
            }
            else if(x<0 && res==0)
            {
                fseek(ptr,-(compteur+1),SEEK_CUR);
                lettre=fgetc(ptr);
            }
            while((lettre=='.' || lettre==',' || lettre==';' || lettre==' '|| lettre=='\n' || lettre=='-' || lettre=='?')&& lettre!='ÿ')
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
    tabfinal=(motproche*)malloc(sizeof(motproche)*300);
    switch(mode)
    {
        case 1:recupmot(mot);res=correctionmot(mot,tabfinal,&tailletab);tri(tabfinal,tailletab);
        if(res==0)affichage(&tailletab,tabfinal);
        break;                   // correcteur de mot un à un
        case 2:correctionfichier(tabfinal,tailletab);break;   // correction d'un fichier txt
    }

    return 0;
}
