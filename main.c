/*!
 * \file main.c
 * \brief Ce programme permet de corriger les fautes de fran�ais d'un texte ou d'un mot.
 */

 /*!
 * \mainpage Projet de NF05 : Correcteur orthographique et dictionnaire.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
char tab[100];
int diff;
int err_frappe;
}motproche;


void tri(motproche* tabfinal,int taille)
{
    /*!
    * \brief Cette fonction permet de trier le tableau de mot qui peuvent possiblement correspondre au mot qui a ete entre, le tri s'effectue selon le nombre de caractere de difference entre le mot original et la correction possible.
    */
    motproche tmp;
	int en_desordre = 1;
	while (en_desordre)
	{
		en_desordre = 0;
		for (int j = 0; j <= taille-1; j++)
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



void deflimite(int taille,int *req) //reglage de la distance limite par rapport � la taille d'un mot
{
    /*!
    * \brief Fonction qui permet de definir le nombre max de caracteres differents entre le mot a corriger et les mots du dictionnaire pour que ceux-ci puissent etre considere comme des corrections possibles.
    */
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

void copie(char tab[],int pos)
{
    /*!
    * \brief Copie un tableau de caracteres, fonction utilisee dans la traduction des mots.
    */
    int i=1;
    while(tab[pos+i]!='\n')
            {
                tab[pos+i]=tab[pos+1+i];
                i++;
            }
}

void trad(char *tab,int t)
{
    /*!
    * \brief Traduction des accents des fichier de la meme maniere que dans la console ex : representation de la lettre e avec accent grave, Fichier : A majuscule accent tilde + Copyright Console : virgule . Cette fonction traduit egalement les lettres majuscules en minuscules.
    */

    int x=0;
    while (x<=t)
    {
        if (tab[x]==-61 && tab[x+1]==-87) // codage du �
        {
            tab[x]=-126;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-88) // codage du �
        {
            tab[x]=-118;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-85) // codage du �
        {
            tab[x]=-119;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-86) // codage du �
        {
            tab[x]=-120;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-82) // codage de �
        {
            tab[x]=-116;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-81) // codage de �
        {
            tab[x]=-117;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-76) // codage du �
        {
            tab[x]=-109;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-92) // codage du �
        {
            tab[x]=-108;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-94) // codage du �
        {
            tab[x]=-125;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-92) // codage du �
        {
            tab[x]=-124;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-96) // codage du �
        {
            tab[x]=-123;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-71) // codage du �
        {
            tab[x]=-105;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-69) // codage du �
        {
            tab[x]=-106;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-68) // codage du �
        {
            tab[x]=-127;
            copie(tab,x);
            t--;
        }
        else if (tab[x]==-61 && tab[x+1]==-89) // codage du �
        {
            tab[x]=-121;
            copie(tab,x);
            t--;
        }
        else if(tab[x]>64 && tab[x]<91)
        {
            tab[x]+=32;
        }
        x++;
    }
}

void decalage(char tab[], int pos)
{
    /*!
    * \brief Fonction de copie d'un tableau. La copie s'effectue en decalant chaque caract�res d'une place sur la droite, utilise dans la fonction invTrad.
    */

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

void invTrad(char *tab,int t)
{
    /*!
    * \brief Traduction des accents du code console au code fichier, pour obtenir des caracteres avec accents dans les fichiers.
    */

    int x=0;
    while (x<=t)
    {
        if (tab[x]==-126) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-87;
            t++;
        }
        else if (tab[x]==-118) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-88;
            t++;
        }
        else if (tab[x]==-119) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-85;
            t++;
        }
        else if (tab[x]==-120) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-86;
            t++;
        }
        else if (tab[x]==-116) // d�codage de �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-82;
            t++;
        }
        else if (tab[x]==-117) // d�codage de �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-81;
            t++;
        }
        else if (tab[x]==-109) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-76;
            t++;
        }
        else if (tab[x]==-108) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-92;
            t++;
        }
        else if (tab[x]==-125) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-94;
            t++;
        }
        else if (tab[x]==-124) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-92;
            t++;
        }
        else if (tab[x]==-123) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-96;
            t++;
        }
        else if (tab[x]==-105) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-71;
            t++;
        }
        else if (tab[x]==-106) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-69;
            t++;
        }
        else if (tab[x]==-127) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-68;
            t++;
        }
        else if (tab[x]==-121) // d�codage du �
        {
            tab[x]=-61;
            decalage(tab,x+1);
            tab[x+1]=-89;
            t++;
        }
        x++;
    }
}

void recupmot(char *mot)
{
    /*!
    * \brief Fonction qui permet de simplement recuperer un mot saisi par l'utilisateur dans un tableau de caracteres.
    */
    printf("\nBienvenue dans le correcteur de mot.\n");
    printf("\nVeuillez saisir un mot  corriger : ");
    fflush(stdin);
    fgets(mot,30,stdin);
}

int taillemot(char *mot)
{
    /*!
    * \brief Fonction qui calcul la taille d'un mot saisi dans un tableau de caracteres.
    */
    int t=0;
    while(mot[t]!='\n')
    {
        t++;
    }
    return t;
}

void ajouter()
{
    /*!
    * \brief Fonction qui a pour but de rentrer un mot a la fin du dictionnaire.
    */
    FILE* ptr=NULL;
    char mot[100];
    int taille;
    ptr=fopen("dico.dic","a");
    if (ptr!=NULL)
    {
        printf("Veuillez saisir le nouveau mot a ajouter au dictionnaire : ");
        fflush(stdin);
        fgets(mot,100,stdin);
        taille=taillemot(mot);
        invTrad(mot, taille);
        fseek(ptr,0,SEEK_END);
        fprintf(ptr,"%s",mot);
        fclose(ptr);
    }
    else printf("Impossible d'acc�s");

}

int affichage(int *taille,motproche *tabfinal)
{
    /*!
    * \brief Fonction permettant d'afficher les differents mots pouvant correspondre au mot a corriger, si aucun mot ne convient a l'utilisateur alors il a la possibilite de faire appel a la fonction ajouter(), pour ajouter un nouveau mot au dictionnaire.
    */
    int pos=0,continuer,n=5,posfinal,x=0,choix;
    printf("\n\nPremier mot propos\202 :\n");
    while(tabfinal[pos].tab[x]!=' ' && tabfinal[pos].tab[x]!='/' && tabfinal[pos].tab[x]!='\n')
    {
        printf("%c",tabfinal[pos].tab[x]);
        x++;
    }

    pos++;
    printf("\n\nEtes vous satisfait du r\202sultat (OUI=1 , NON=0) : ");
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
        printf("\n\nEtes vous satisfait d'une des propositons (OUI=1 , NON=0) : ");
        scanf("%d",&continuer);
        while(continuer!=1 && continuer!=0)
        {
            printf("\nVeuillez saisir 0 ou 1 :");
            fflush(stdin);
            scanf("%d",&continuer);
        }
        if(continuer==1)
        {
            printf("\nSaisir la position associ\202e au mot choisi : ");
            scanf("%d",&posfinal);
        }
    }
    if(continuer==0)
    {
        printf("\nVoulez vous ajouter un nouveau mot au dictionnaire ? (OUI=1 , NON=0) : ");
        scanf("%d",&choix);
        while(choix!=1 && choix!=0)
        {
            printf("Veuillez saisir 0 ou 1 :");
            fflush(stdin);
            scanf("%d",&choix);
        }
        if (choix==1)
        {
            ajouter();
        }
        return -1;
    }
    return posfinal;

}

int correctionmot(char mot[30],motproche *tabfinal,int *tailletab)
{
    /*!
    * \brief Fonction principale du programme, celle-ci permet de recuperer les mots du dictionnaire et de les comparer au mot saisi par l'utilisateur, de plus elle integre chaque mot qui pourrait correspondre a la correction recherchee dans un tableau qui sera ensuite trie et propose a l'utilisateur.
    */
    FILE* fichier = NULL;
    char chaine[100];
    int i,x,z,compteur,distance,same=0,taille,taillechaine,distancereq;
    int lettre_doublee,lettre_oublie,imot,ichaine;
    int TAILLE_MAX=100;

    fichier = fopen("dico.dic","r");
    taille=taillemot(mot);
    trad(mot,taille);
    mot[taille+2]='\n'; // ces op�rations permettent de rajouter  des s�curit�s sur les conditions d'arr�ts
    mot[taille+3]='\n';
    mot[taille+4]='\n';
    deflimite(taille,&distancereq);

    if (fichier!=NULL)
    {
        *tailletab=0;
        while(fgets(chaine,TAILLE_MAX,fichier) != NULL && same==0) // permet de couvrir l'int�gralit� du fichier
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
                if (imot<taille-1 && ichaine<taille-1) // permet de corriger les fautes avec un taux de v�rification important
                {
                    if(mot[imot+1]==chaine[ichaine] && mot[imot+2]==chaine[ichaine+1] && mot[imot]!=chaine[ichaine])  // correction des lettre ins�r�es en doubles, ex : perssonne
                    {
                        lettre_doublee++;
                    }
                    else if(mot[imot]==chaine[ichaine+1] && mot[imot+1]==chaine[ichaine+2] && mot[imot]!=chaine[ichaine]) // double lettre oubliees ex : persone
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot+1]==chaine[ichaine+2] && mot[imot+2]==chaine[ichaine+3] && mot[imot]!=chaine[ichaine] && mot[imot]=='f') // correction du f � la place de ph, �l�fant / �l�phant
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot+2]==chaine[ichaine+1] && mot[imot+3]==chaine[ichaine+2] && mot[imot]!=chaine[ichaine] && chaine[ichaine]=='f') // correction du ph � la place du f
                    {
                        lettre_doublee++;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='e' && mot[imot+1]=='a' && mot[imot+2]=='u') // correction de o � la place du eau ex: v�leau <=> v�lo
                    {
                        lettre_doublee+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='a' && mot[imot+1]=='u') // correction de o � la place du au ex: v�lau <=> v�lo
                    {
                        lettre_doublee+=1;
                    }
                    else if(mot[imot]!=chaine[ichaine] && mot[imot]=='o' && chaine[ichaine]=='e' && chaine[ichaine+1]=='a' && chaine[ichaine+2]=='u') // correction de o � la place du eau ex: bato => bateau
                    {
                        lettre_oublie+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] &&  mot[imot]=='o' && chaine[ichaine]=='a' && chaine[ichaine+1]=='u') // correction de eau � la place du o ex:  hot => haut
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot]!=chaine[ichaine] &&  mot[imot]=='a' && mot[imot+1]=='u' && chaine[ichaine]=='e' && chaine[ichaine+1]=='a' && chaine[ichaine+2]=='u') // correction de au � la place du eau ex: batau =>bateau
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='a' && chaine[ichaine+1]=='u' && mot[imot]=='e' && mot[imot+1]=='a' && mot[imot+2]=='u') // correction de eau � la place du au ex: beaume => baume
                    {
                        lettre_doublee+=2;
                    }
                }
                else // m�me mode de correction mais avec une pr�cision moins �lev�e
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
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='e' && mot[imot+1]=='a' && mot[imot+2]=='u') // correction de o � la place du eau ex: v�leau <=> v�lo
                    {
                        lettre_doublee+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='o' && mot[imot]=='a' && mot[imot+1]=='u') // correction de o � la place du au ex: v�lau <=> v�lo
                    {
                        lettre_doublee+=1;
                    }
                    else if(mot[imot]!=chaine[ichaine] && mot[imot]=='o' && chaine[ichaine]=='e' && chaine[ichaine+1]=='a' && chaine[ichaine+2]=='u') // correction de o � la place du eau ex: bato => bateau
                    {
                        lettre_oublie+=2;
                    }
                    else if(mot[imot]!=chaine[ichaine] &&  mot[imot]=='o' && chaine[ichaine]=='a' && chaine[ichaine+1]=='u') // correction de eau � la place du o ex:  hot => haut
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot]!=chaine[ichaine] &&  mot[imot]=='a' && mot[imot+1]=='u' && chaine[ichaine]=='e' && chaine[ichaine+1]=='a' && chaine[ichaine+2]=='u') // correction de au � la place du eau ex: batau =>bateau
                    {
                        lettre_oublie++;
                    }
                    else if(mot[imot]!=chaine[ichaine] && chaine[ichaine]=='a' && chaine[ichaine+1]=='u' && mot[imot]=='e' && mot[imot+1]=='a' && mot[imot+2]=='u') // correction de eau � la place du au ex: beaume => baume
                    {
                        lettre_doublee+=2;
                    }
                }


                i++;
                ichaine=i+lettre_oublie;
                imot=i+lettre_doublee;
            }

            if(mot[imot]!='\n') // test si on est bien arriv� � la fin du mot saisie
                {
                    x=imot;
                    while(mot[x]!='\n')
                    {
                        x++;
                        distance++;
                    }
                }

                else if(chaine[ichaine]!='/' && chaine[ichaine]!=' ' && chaine[ichaine]!='\n' ) // test si on est bien arriv� � la fin du mot du dictionnaire r�cup�r�
                {
                    x=ichaine;
                    while(chaine[x]!='/' && chaine[x]!=' ' && chaine[x]!='\n')
                    {
                        x++;
                        distance++;
                    }
                }

            if(distance==0) // si le mot est trouv�, renvois le mot du dico
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
            else if(distance<=distancereq)
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
    return 0;
}

void copiemotfichier(char *tab,motproche *tabfinal,int x)
{
    /*!
    * \brief Dans le mode correction de fichier, cette fonction permet de recuperer le mot choisi dans la fonction affichage et de le copier dans un tableau de caractere utilise par la fonction copiedansfichier.
    */
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
    /*!
    * \brief Dans le mode correction de fichier, cette fonction permet de copier le mot choisi dans le fichier de texte corrige.
    */
    int i=0;

    while(tab[i]!='\n')
    {
        fputc(tab[i], ptr);
        i++;
    }
}

void correctionfichier(motproche *tabfinal,int tailletab)
{
    /*!
    * \brief Cette fonction est la fonction principale du mode de correction de fichier.Elle permet de recuperer les mots dans le fichier de texte a corriger et la ponctuation. Puis elle retourne le texte corrige dans un nouveau fichier.
    */

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
            while(lettre!='.' && lettre!=',' && lettre!=';' && lettre!=' ' && lettre!='�' && lettre!='\n' && lettre!='-' && lettre!='?')
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
                taille=taillemot(motbon);
                invTrad(motbon, taille);
                copiedansfichier(nouvfichier,motbon);
            }
            else if(x<0 && res==0)
            {
                fseek(ptr,-(compteur+1),SEEK_CUR);
                lettre=fgetc(ptr);
            }
            while((lettre=='.' || lettre==',' || lettre==';' || lettre==' '|| lettre=='\n' || lettre=='-' || lettre=='?')&& lettre!='�')
            {
                fprintf(nouvfichier,"%c",lettre);
                lettre=fgetc(ptr);
            }

        }
        printf("\nVotre texte est corrig\202 dans le fichier textecorrige.txt");

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
    /**
    * \brief la fonction main permet de choisir le mode desire.
    */
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
        break;                   // correcteur de mot un � un
        case 2:correctionfichier(tabfinal,tailletab);break;   // correction d'un fichier txt
    }

    return 0;
}
