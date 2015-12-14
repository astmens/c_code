#!/usr/bin/python

def call_ex10(argc):
	from subprocess import call
	import os
	import sys
	# set working directory to current script directory:
	os.chdir(sys.path[0])
	#os.chdir('/media/C/Users/Atom/Documents/c_code')
	print os.getcwd()
	
	argv = ""
	for i in range(0, argc):
		argv += "v" + str(i) + " "
	print argv
	
	cmdName = "./ex10" + " " + argv
	print cmdName
	print "Call: "
	# Warning: Using shell=True can be a security hazard. 
	call([cmdName], shell=True)
	
	return
	
import math

#Max number of input arguments is 20310;
call_ex10(20310)

#Call: 
#Traceback (most recent call last):
#  File "ex10.py", line 26, in <module>
#    call_ex10(20311)
#  File "ex10.py", line 21, in call_ex10
#    call([cmdName], shell=True)
#  File "/usr/lib/python2.7/subprocess.py", line 522, in call
#    return Popen(*popenargs, **kwargs).wait()
#  File "/usr/lib/python2.7/subprocess.py", line 710, in __init__
#    errread, errwrite)
#  File "/usr/lib/python2.7/subprocess.py", line 1327, in _execute_child
#    raise child_exception
#OSError: [Errno 7] Argument list too long

