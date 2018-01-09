#! /usr/bin/env python3
# coding: utf-8

import os
import subprocess




def get_folder (path) :
	liste_dossier = []
	for i in os.listdir(path) :
		if os.path.isdir(os.path.join(path,i)) :
			liste_dossier.append(i)
	return (liste_dossier)

def get_file(path) :
	liste_fichier = []
	for i in os.listdir(path) :
		if os.path.isfile(os.path.join(path,i)) :
			if "README" not in i :
				liste_fichier.append(i)
	return liste_fichier 

def exec_arm(nom_fich) :
	print ("j'execute "+nom_fich)
	try : 
		#output = subprocess.check_output(['./../../scripts/mincamlc','nom_fich',-o,'output'])
		output = subprocess.check_output(['cat',nom_fich])
	except subprocess.CalledProcessError as e :
		output = e.output
	print(output)
	return 0


def exec_null(path) :
	print ("Erreur : Le fichier " + path + " n'a pas son jeu de test de defini")




def Error(path) :
	return 0

def test_Exec(path) :
	a = get_file(os.getcwd())
	b = exec_null
	if path == "asml_to_arm" :
		b = exec_arm
	for i in a :
		b(i)
	return 0



def main() : 
	
	repo = os.path.abspath(os.path.join(os.getcwd(),os.pardir)) +'/tests'
	os.chdir(repo)
	liste_dossier_test = get_folder(repo)

	print("Bienvenue dans le Testeur de notre programme ")
	print("Organisation: Tests/Dossier/fichier_test ou Tests/Dossier/Valid/fichier_test : \n")
	for i in liste_dossier_test :
		print("execution des tests de " + i )
		os.chdir(repo+'/'+i)
		liste_dossier = get_folder(os.getcwd())
		if liste_dossier :
			print("Valid-Invalide")
		else :
			test_Exec(i)
			print("Exec")



	
	'''
	chemin = []
	doss = []
	fich = []
	for (dirpath,dirname,nomfich) in os.walk(repo) :
		print("Directory : ")
		print(dirpath)
		chemin.append(dirpath)
		print(" Nomdir : ")
		print(dirname)
		doss.append(dirname)
		print(" Nomfich : ")
		print(nomfich)
		fich.append(nomfich)
		print("\n")

'''





if __name__ == "__main__":
    main()



