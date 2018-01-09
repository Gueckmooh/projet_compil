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

def arm_to_exec (outputf) :
	print ("je lance la genereation d'executable ")
	try : 
		output = subprocess.check_output(['arm-none-eabi-as', '../../src/lib_arm/libmincaml.S', '-o', '../../tmp/libmincaml.o'])
		output = subprocess.check_output(['arm-none-eabi-as', '../../tmp/'+outputf+'.s' , '-o', '../../tmp/'+outputf+'.o'])
		output = subprocess.check_output(['arm-none-eabi-ld', '../../tmp/'+outputf+'.o', '../../tmp/libmincaml.o', '-o', '../../tmp/'+outputf+'.out'])
	except subprocess.CalledProcessError as e :
		output = e.output
	return 0


def exec_arm(nom_fich) :
	print ("j'execute "+nom_fich)
	try : 

		output = subprocess.check_output(['./../../scripts/mincamlc',nom_fich,'-o','../../tmp/'+nom_fich+'.s'])
		arm_to_exec (nom_fich)
		#output = subprocess.check_output(['cat',nom_fich])
		print(output)
		output2 = subprocess.check_output(['ocamlc',nom_fich,'-o','../../tmp/base_'+nom_fich+'.out'])
		print(output2)
		output3 = subprocess.check_output(['./../../tmp/'+nom_fich+'.out'])
		output4 = subprocess.check_output(['./../../tmp/base_'+nom_fich+'.out'])

	except subprocess.CalledProcessError as e :
		output3 = e.output
		output4 = ''
	try :
		os.remove(nom_fich.split('.')[0]+'.cmi')
		os.remove(nom_fich.split('.')[0]+'.cmo')
	except OSError :
		pass
	if output3 == output4 :
		print("test de "+nom_fich+" reussi")
		#return 1
	else :
		print("Echec du test de "+nom_fich)
	return 0


def exec_asml(nom_fich) :
	print ( "j'execute "+nom_fich)
	try : 
		output = subprocess.check_output(['./../../scripts/mincamlc',nom_fich,'-i','-o','../../tmp/'+nom_fich+'.s'])
		arm_to_exec(nom_fich)
		print(output)
		output2 = subprocess.check_output(['./../../scripts/asml',nom_fich])
		print(output2)
		output3 = subprocess.check_output(['./../../tmp/'+nom_fich+'.out'])
	except subprocess.CalledProcessError as e :
		output3 = e.output
	if output2 == output3 :
		print("test de "+nom_fich+" reussi")
	else :
		print("Echec du test de "+nom_fich)
	return 0

def gen_asml(nom_fich) :
	print ("Je genere l'asml de "+nom_fich)
	try :
		output=subprocess.check_output(['./../../scripts/mincamlc',nom_fich,'-a','-o','../../tmp/'+nom_fich+'.asml'])
		output2 = subprocess.check_output(['ocamlc',nom_fich,'-o','../../tmp/base_'+nom_fich+'.out'])
		output3 = subprocess.check_output(['./../../scripts/asml','../../tmp/'+nom_fich+'.asml'])
		output4 = subprocess.check_output(['./../../tmp/base_'+nom_fich+'.out'])


	except subprocess.CalledProcessError as e :
		output3 = e.output
		output4 = ''
	try :
		os.remove(nom_fich.split('.')[0]+'.cmi')
		os.remove(nom_fich.split('.')[0]+'.cmo')
	except OSError :
		pass
	if output3 == output4 :
		print("test de "+nom_fich+" reussi")
	else :
		print("Echec du test de "+nom_fich)
	return 0


def exec_typecheck(nom_fich,typee) :
	print ("je test typecheck de "+nom_fich)
	noerr = True 
	try : 
		#output = subprocess.check_output(['ls'])
		output = subprocess.check_output(['./../../scripts/mincamlc',typee+'/'+nom_fich,'-t'])
		#print(output.decode())
	except subprocess.CalledProcessError as e :
		output = e.output
		noerr = False 
	if (noerr and typee == 'valid') or (not(noerr) and typee == 'invalid'):
		print ("TEST typecheck CORRECT") 
	else :
		print ("Test Typecheck Incorrect")
	return 0


def exec_null(path) :
	print ("Erreur : Le fichier " + path + " n'a pas son jeu de test de defini")

def exec_null2(path,nul) :
	print ("Erreur : Le fichier " + path + " de validite " + nul + " n'a pas son jeu de test de defini")



def Error(path) :
	return 0

def test_Exec(path) :
	a = get_file(os.getcwd())
	b = exec_null
	if path == "gen-code" :
		b = exec_arm
	elif path == "asml_to_arm" :
		b = exec_asml
	elif path == "gen-asml" :
		b = gen_asml
	for i in a :
		b(i)

	return 0

def test_VI(path) :
	val = []
	inval = []
	rootdir = os.getcwd()
	b = exec_null2
	if os.path.isdir(rootdir+'/valid') :
		val = get_file(rootdir+'/valid')
	if os.path.isdir(rootdir+'/invalid') :
		inval = get_file(rootdir+'/invalid')
	if path == "typechecking" :
		print("On fait typechecking")
		b = exec_typecheck
	if val :
		for i in val :
			b(i,'valid')
	if inval :
		for j in inval :
			b(j,'invalid')
	return 0

def main() : 
	if not os.path.exists('tmp') :
		os.makedirs('tmp')
	#repo = os.path.abspath(os.path.join(os.getcwd(),os.pardir)) +'/tests'
	repo = os.getcwd()+'/tests'
	os.chdir(repo)
	liste_dossier_test = get_folder(repo)



	print("Bienvenue dans le Testeur de notre programme ")
	print("Organisation: Tests/Dossier/fichier_test ou Tests/Dossier/Valid/fichier_test : \n")
	for i in liste_dossier_test :
		print("execution des tests de " + i )
		os.chdir(repo+'/'+i)
		liste_dossier = get_folder(os.getcwd())
		if liste_dossier :
			test_VI(i)
		else :
			test_Exec(i)


	
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



