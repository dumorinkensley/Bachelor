from random import *
from os import *
###############################
#      VARIABLES GLOBALES     #
###############################

#COULEURS
BLANC = 'B'
NOIR  = 'N'
GRIS  = 'G'
VIDE  = 'V'

#JOUEURS
j1="BOB"
j2="PATRICK"
c_j1=NOIR
c_j2=BLANC
IA1=0
IA2=0

#JEU
grille=dict()
for i in range(0,8) :
	grille[i]=dict()
	for j in range(0,8) :
		grille[i][j]=VIDE
test=dict()
for i in range(0,8) :
	test[i]=dict()
	for j in range(0,8) :
		test[i][j]=VIDE

#ERREURS
OK = 0
ERR_SAISIE = -1
ERR_IMPOSSIBLE = -2
ERR = -3


###############################
#          DEFINITION         #
###############################


def Calcul_Test() :
	#Ecrasement de test
	i=0
	while i<8  :
		j=0
		while(j<8) :
			test[i][j] = VIDE
			j=j+1
		i=i+1
   
	i=0
	while(i<8) :
		j=0
		while(j<8) :
			if grille[i][j]!=VIDE or test[i][j]==GRIS  :
				j=j+1
				continue

            #test de posibilite
			shift_lig=-1
			while shift_lig<=1 :
				shift_col=-1
				while shift_col<=1  :
					#(shift_lig,shift_col) représente la direction de l'analyse
					#(-1,-1) = en haut à gauche
					#(-1,0) = en haut
					#(-1,1) = en haut à droite
					#(0,-1) = à gauche
					#(0,1) = à droite
					#(1,-1) = en bas à gauche
					#(1,0) = en bas
					#(1,1) = en bas à droite

					#Cas à exclure
					if shift_lig==0 and shift_col==0 : 
						shift_col=shift_col+1
						continue
					if i+shift_lig <0 or i+shift_lig>=8 : 
						shift_col=shift_col+1
						continue
					if j+shift_col <0 or j+shift_col>=8 :
						shift_col=shift_col+1
						continue

					a=grille[i+shift_lig][j+shift_col];

					#S'il n'y a pas de pion à coté on passe à autre chose
					if a==VIDE : 
						shift_col=shift_col+1
						continue

					#Inversion des couleurs
					if a==BLANC :
						b=NOIR
					if a==NOIR : 
						b=BLANC

					k=1
					#Une fois la direction choisi on va voir si on croise un jeton de couleur différente
					while i+shift_lig*k>=0 and i+shift_lig*k<8 and j+shift_col*k>=0 and j+shift_col*k<8 and grille[i+shift_lig*k][j+shift_col*k]==a :
						k=k+1

					#Si on est sortie de la boucle parce qu'on a rencontré un jeton de couleur différente (b) alors le placement est possible
					if i+shift_lig*k>=0 and i+shift_lig*k<8 and j+shift_col*k>=0 and j+shift_col*k<8 and grille[i+shift_lig*k][j+shift_col*k]==b :
						if test[i][j]==a :  
							test[i][j]=GRIS
						else :
							test[i][j]=b

					shift_col=shift_col+1
				shift_lig=shift_lig+1
			j=j+1
		i=i+1


def Init() :
	i=0
	while(i<8):
		j=0
		while(j<8):
			grille[i][j]=VIDE
			j=j+1
		i=i+1
	grille[3][3]=BLANC
	grille[3][4]=NOIR
	grille[4][3]=NOIR
	grille[4][4]=BLANC
	
	Calcul_Test()


def Compte_Couleur(c) :
	i=0
	res=0
	while (i<8) :
		j=0
		while (j<8) :
			if (grille[i][j] == c) :
				res = res + 1;
			j=j+1
		i=i+1
	return res

def Plateau() :

	luc='+'    	#left up corner
	ruc='+' 	#right up corner
	lbc='+'    	#left bottom corner
	rbc='+'    	#right bottom corner
	hl='-'    	#horizontal line
	vl='|'     	#vertical line
	tu='-'     	#t up
	tb='-'     	#t bottom
	tl='|'     	#t left
	tr='|'     	#t right
	tm='+'     	#t middle
	esp=' '  	#espace
	tab='\t' 	#tabulation
	sdl='\n'	#Saut de ligne
	plat = sdl

	plat+=tab+esp
	for i in range(0,8) :
		plat+= esp+chr(ord('A')+i)+esp+esp
	plat+=sdl+sdl

	plat+=tab+luc;
	for i in range(0,8) : 
		plat+=hl+hl+hl+tu
	plat+="\b"+ruc
	plat+= tab+" .:REVERSI:."+sdl;

	for i in range(0,8) : 
		plat+=esp+esp+esp+str(i+1)+tab
		for j in range(0,8) :
			plat+= vl+esp
			if grille[i][j]==BLANC :
				plat+=chr(2)
			elif grille[i][j]==NOIR :
				plat+=chr(1)
			else :
				plat+= esp
			plat+= esp
		plat+= vl+sdl

		plat+=tab
		plat+=tl
		for j in range(0,8) : 
			plat+= hl+hl+hl+tm
		plat+="\b"+tr;

		if i==0 : 
			plat+= tab+chr(1)+"  IUT - S2R  "
		elif i==2 :
			plat+= tab+chr(1)+" : "+str(Compte_Couleur(NOIR))
			plat+= tab+chr(2)+" : "+str(Compte_Couleur(BLANC))
		elif i==4 :
			if c_j1 == NOIR :
				plat+= tab+chr(1)+esp+j1
			else :
				plat+= tab+chr(1)+esp+j2
		elif i==5 :
			if c_j1 == NOIR :
				plat+= tab+chr(2)+esp+j2
			else :
				plat+= tab+chr(2)+esp+j1

		if i!=7 : 
			plat+=sdl

	plat+= "\r"
	plat+= tab+lbc
	for i in range(0,8) :
		plat+= hl+hl+hl+tb 
	plat+= "\b"+rbc+tab

	print(plat)

def Fin() :
	i=0
	while i<8 :
		j=0
		while j<8 :
			if (test[i][j]!=VIDE) :
				return False
			j=j+1
		i=i+1
	return True

def Test_Tour(c) :
	i=0
	while (i<8) :
		j=0
		while (j<8) :
			if (test[i][j]==c or test[i][j]==GRIS) :
				return True
			j=j+1
		i=i+1;
	return FALSE

def Placer(c,IA) :

	if IA==1 : #NOETHER IA FACILE
		#On choisi une place au hasard parmi les places possibles

		#On compte le nombre de case true pour la couleur c
		cmpt=0;

		for i in range(0,8) :
			for j in range(0,8) :
				if test[i][j]==c or test[i][j]==GRIS :
					cmpt=cmpt+1
		if cmpt==0 : 
			return ERR_IMPOSSIBLE

		#On choisi une case true au hasard
		t=randint(0, cmpt-1)
		cmpt=0
		
		i=0
		b=False;
		while i<8 and b==False :
			j=0
			while j<8 and b==False :
				if test[i][j]==c or test[i][j]==GRIS :
					cmpt=cmpt+1
				if cmpt>t :
					b=True
					lig = i
					col = j
				j=j+1
			i=i+1
					
	elif IA==2 :#ABEL IA MOYEN
		#On choisi la place qui fait gagner le plus de point

		#On créer une copie de grille et de test
		grille_sav1 = dict()
		test_sav1 = dict()
		for i in range(0,8) :
			grille_sav1[i]=dict()
			test_sav1[i]=dict()
			for j in range(0,8) :
				grille_sav1[i][j]=grille[i][j]
				test_sav1[i][j]=test[i][j]

		#Pour chaque case possible on place et on calcul les points
		t=0
		for i in range(0,8) :
			for j in range(0,8) :
				if test[i][j]==c or test[i][j]==GRIS :
					Placement(i, j, c)
					if Compte_Couleur(c)>t :
						lig=i
						col=j
						t=Compte_Couleur(c)

					#On remet la grille en l'etat
					for i1 in range(0,8) :
						for j1 in range(0,8) :
							grille[i1][j1] = grille_sav1[i1][j1]
							test[i1][j1] = test_sav1[i1][j1]
	elif IA==3 :#GROTHENDIECK IA DIFFICILE
		#On choisi la place qui fait gagner le plus de point au joueur et le moins de point a l'autre

		#On créer une copie de grille et de test
		grille_sav1 = dict()
		test_sav1 = dict()
		for i in range(0,8) :
			grille_sav1[i]=dict()
			test_sav1[i]=dict()
			for j in range(0,8) :
				grille_sav1[i][j]=grille[i][j]
				test_sav1[i][j]=test[i][j]


		if c==NOIR :
			d=BLANC
		else :
			d=NOIR

		b=False
		t=-64
		for i in range(0,8) :
			for j in range(0,8) :
				if test[i][j]==c or test[i][j]==GRIS :
					Placement(i, j, c)

					#Création d'une nouvelle copie
					grille_sav2=dict()
					test_sav2=dict()
					for i1 in range(0,8) :
						grille_sav2[i1]=dict()
						test_sav2[i1]=dict()
						for j1 in range(0,8) :
							grille_sav2[i1][j1]=grille[i1][j1]
							test_sav2[i1][j1]=test[i1][j1]

					for i1 in range(0,8) :
						for j1 in range(0,8) :
							if test[i1][j1]==d or test[i1][j1]==GRIS :
								Placement(i1,j1,d)
								b=True
								if Compte_Couleur(c)-Compte_Couleur(d)>t :
									t = Compte_Couleur(c)-Compte_Couleur(d)
									lig = i
									col = j
									
								#On remet la grille a l'état d'avant
								for i2 in range(0,8) :
									for j2 in range(0,8) :
										grille[i2][j2]=grille_sav2[i2][j2]
										test[i2][j2]=test_sav2[i2][j2]

					#On remet la grille a l'état d'avant
					for i1 in range(0,8) :
						for j1 in range(0,8) :
							grille[i1][j1]=grille_sav1[i1][j1]
							test[i1][j1]=test_sav1[i1][j1]
							
		if b==False : 
			return Placer(c,2);

		#Les coins sont stratégiques
		if test[0][0]==c or test[0][0]==GRIS :
			lig=0
			col=0
		if test[0][7]==c or test[0][7]==GRIS :
			lig=0
			col=7
		if test[7][0]==c or test[7][0]==GRIS :
			lig=7
			col=0
		if test[7][7]==c or test[7][7]==GRIS :
			lig=7
			col=7
	else : 
		place = input("\t\tSaisir la position :")

		if len(place)!=2 :
			return ERR_SAISIE
		col=ord(place[0])-ord('A')
		lig=ord(place[1])-ord('1')
		
	if not(lig<8 and lig>=0 and col<8 and col>=0) :
		return ERR_SAISIE;
	if not(test[lig][col]==c or test[lig][col]==GRIS) :
		return ERR_IMPOSSIBLE;

	Placement(lig, col, c)
	return OK

def Placement(lig,col,c) :

	#Positionnement du pion
	grille[lig][col] = c

	#Retournement des pions
	#Le principe des deux shift est le même que pour la fonction calcul_test
	shift_lig=-1
	while shift_lig<=1 :
		shift_col=-1
		while shift_col<=1 :

			if shift_lig==0 and shift_col==0 : 
				shift_col=shift_col+1
				continue
			if lig+shift_lig <0 or lig+shift_lig>=8 : 
				shift_col=shift_col+1
				continue
			if col+shift_col <0 or col+shift_col>=8 : 
				shift_col=shift_col+1
				continue

			a=grille[lig+shift_lig][col+shift_col]
			if a==c or a==VIDE : 
				shift_col=shift_col+1
				continue
				
			k=1
			while lig+shift_lig*k>=0 and lig+shift_lig*k<8 and col+shift_col*k>=0 and col+shift_col*k<8 and grille[lig+shift_lig*k][col+shift_col*k]==a : 
				k=k+1

			if lig+shift_lig*k>=0 and lig+shift_lig*k<8 and col+shift_col*k>=0 and col+shift_col*k<8 and grille[lig+shift_lig*k][col+shift_col*k]==c : 
				k=1
				while grille[lig+shift_lig*k][col+shift_col*k]!=c :
					grille[lig+shift_lig*k][col+shift_col*k]=c
					k=k+1
			shift_col=shift_col+1
		shift_lig=shift_lig+1
		
	#Calcul des la feuille de test
	Calcul_Test()

###############################
#     FONCTION PRINCIPALE     #
###############################

Plateau()