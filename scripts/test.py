#! /usr/bin/env python3
# coding: utf-8

import os
import subprocess

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

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
	try : 
		output = subprocess.check_output(['arm-none-eabi-as', '../../src/lib_arm/libmincaml.S', '-o', '../../tmp/libmincaml.o'])
		output = subprocess.check_output(['arm-none-eabi-as', '../../tmp/'+outputf+'.s' , '-o', '../../tmp/'+outputf+'.o'])
		output = subprocess.check_output(['arm-none-eabi-ld', '../../tmp/'+outputf+'.o', '../../tmp/libmincaml.o', '-o', '../../tmp/'+outputf+'.out'])
	except subprocess.CalledProcessError as e :
		output = e.output
		printf(bcolors.FAIL + "--- Echec generation executable" + bcolors.ENDC)
	return 0


def exec_arm(nom_fich) :
	#print ("j'execute "+nom_fich)
	try : 

		output = subprocess.check_output(['./../../scripts/mincamlc',nom_fich,'-n','-o','../../tmp/'+nom_fich+'.s'])
		arm_to_exec (nom_fich)
		#output = subprocess.check_output(['cat',nom_fich])
		output2 = subprocess.check_output(['ocamlc',nom_fich,'-o','../../tmp/base_'+nom_fich+'.out'])
		output3 = subprocess.check_output(['./../../tmp/'+nom_fich+'.out'])
		output4 = subprocess.check_output(['./../../tmp/base_'+nom_fich+'.out'])

	except subprocess.CalledProcessError as e :
		output3 = e.output
		output4 = ''
		print(bcolors.FAIL +"--- Probleme fonctionnement du Test de "+nom_fich+ bcolors.ENDC)
		return 0
	try :
		os.remove(nom_fich.split('.')[0]+'.cmi')
		os.remove(nom_fich.split('.')[0]+'.cmo')
	except OSError :
		pass
	if output3 == output4 :
		print(bcolors.OKGREEN +"--- Test de "+nom_fich+" reussi"+ bcolors.ENDC)
		#return 1
	else :
		print(bcolors.WARNING + "--- Echec du test de "+nom_fich+ bcolors.ENDC)
		print(bcolors.WARNING + "    Output programme : " + output3.decode() + "\n    Output du programme etalon : " + output4.decode() + bcolors.ENDC)
		try : 
			outputmin = subprocess.check_output(['cat',nom_fich])
			print (bcolors.WARNING +"    Lecture du fichier minml originel \n" + outputmin.decode() + bcolors.ENDC)
		except subprocess.CalledProcessError as e :
			outputmin = e.output
			print(bcolors.FAIL+"    Echec ouverture fichier minml"+bcolors.ENDC)
		try :
			output5=subprocess.check_output(['./../../scripts/mincamlc',nom_fich,'-a','-o','../../tmp/'+nom_fich+'.asml'])
			output6 = subprocess.check_output(['cat','../../tmp/'+nom_fich+'.asml'])
			print(bcolors.WARNING + "    Generation du fichier ASML \n " + output6.decode() + bcolors.ENDC)
		except subprocess.CalledProcessError as e :
			output5 = e.output
			print (bcolors.FAIL+ "    Echec generation du fichier ASML pour verifier difference output pour "+nom_fich+bcolors.ENDC)

	return 0


def exec_asml(nom_fich) :
	#print ( "j'execute "+nom_fich)
	try : 
		output = subprocess.check_output(['./../../scripts/mincamlc',nom_fich,'-i','-o','../../tmp/'+nom_fich+'.s'])
		arm_to_exec(nom_fich)
		output2 = subprocess.check_output(['./../../scripts/asml',nom_fich])
		output3 = subprocess.check_output(['./../../tmp/'+nom_fich+'.out'])
	except subprocess.CalledProcessError as e :
		output3 = e.output
		output2 = ''
		print(bcolors.FAIL +"--- Probleme fonctionnement du Test de "+nom_fich+ bcolors.ENDC)
		return 0
	if output2 == output3 :
		print(bcolors.OKGREEN +"--- Test de "+nom_fich+" reussi"+ bcolors.ENDC)
	else :
		print(bcolors.WARNING +"--- Echec du test de "+nom_fich+ bcolors.ENDC)
		print(bcolors.WARNING + "    Output programme : " + output3.decode() + "\n    Output du programme etalon : " + output2.decode() + bcolors.ENDC)

	return 0

def gen_asml(nom_fich) :
	#print ("Je genere l'asml de "+nom_fich)
	try :
		output=subprocess.check_output(['./../../scripts/mincamlc',nom_fich,'-a','-o','../../tmp/'+nom_fich+'.asml'])
		output2 = subprocess.check_output(['ocamlc',nom_fich,'-o','../../tmp/base_'+nom_fich+'.out'])
		output3 = subprocess.check_output(['./../../scripts/asml','../../tmp/'+nom_fich+'.asml'])
		output4 = subprocess.check_output(['./../../tmp/base_'+nom_fich+'.out'])


	except subprocess.CalledProcessError as e :
		output3 = e.output
		output4 = ''
		print(bcolors.FAIL +"--- Probleme fonctionnement du Test de "+nom_fich + bcolors.ENDC)
		return 0
	try :
		os.remove(nom_fich.split('.')[0]+'.cmi')
		os.remove(nom_fich.split('.')[0]+'.cmo')
	except OSError :
		pass
	if output3 == output4 :
		print(bcolors.OKGREEN +"--- Test de "+nom_fich+" reussi"+ bcolors.ENDC)
	else :
		print(bcolors.WARNING +"--- Echec du test de "+nom_fich+ bcolors.ENDC)
		print(bcolors.WARNING + "    Output programme : " + output3.decode() + "\n    Output du programme etalon : " + output4.decode() + bcolors.ENDC)

	return 0


def exec_typecheck(nom_fich,typee) :
	#print ("je test typecheck de "+nom_fich)
	noerr = True 
	try : 
		#output = subprocess.check_output(['ls'])
		output = subprocess.check_output(['./../../scripts/mincamlc',typee+'/'+nom_fich,'-t'])
		#print(output.decode())
	except subprocess.CalledProcessError as e :
		output = e.output
		noerr = False 	
	if (noerr and typee == 'valid') or (not(noerr) and typee == 'invalid'):
		print (bcolors.OKGREEN +"--- Test typecheck Correct pour "+ nom_fich + bcolors.ENDC) 
	else :
		print (bcolors.FAIL +"--- Test Typecheck Incorrect pour "+ nom_fich + bcolors.ENDC)
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



	print(bcolors.HEADER + "Bienvenue dans le Testeur de notre programme " + bcolors.ENDC)
	print(bcolors.HEADER + "Organisation: Tests/Dossier/fichier_test ou Tests/Dossier/Valid/fichier_test : \n"+ bcolors.ENDC)
	for i in liste_dossier_test :
		print(bcolors.HEADER +" \n Execution des tests de " + i + "\n" + bcolors.ENDC )
		os.chdir(repo+'/'+i)
		liste_dossier = get_folder(os.getcwd())
		if liste_dossier :
			test_VI(i)
		else :
			test_Exec(i)


if __name__ == "__main__":
    main()



