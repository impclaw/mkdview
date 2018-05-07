#!/usr/bin/env python2
import shutil, subprocess
import os, sys
USAGE = "Usage: boot.py debug|release"

def touch(fname, times=None):
	with open(fname, 'a'):
		os.utime(fname, times)

def delif(fname):
	if os.path.exists(fname):
		os.remove(fname)

if len(sys.argv) < 2:
	exit(USAGE)

print "Cleaning previous install"
try: 
	subprocess.check_output(["make", "clean"])
except:
	pass

mode = sys.argv[1] if len(sys.argv) > 1 else "release"
cflags = ['-std=c++11', '-Wno-deprecated']
args = ["-project", 'QT += widgets', 'QMAKE_CXX = clang++', 'QMAKE_LIBS += -lmarkdown', 'OBJECTS_DIR = obj', 'MOC_DIR = obj']
if mode.lower() == "release":
	args.append('CONFIG += silent')
	cflags += ['-O2']
elif mode.lower() == "debug":
	args.append('CONFIG += silent debug')
	cflags += ['-DDEBUG -g']
else:
	exit(USAGE)
qmake_cxxflags = 'QMAKE_CXXFLAGS += '
for cf in cflags:
	qmake_cxxflags += "%s " % cf

subprocess.check_output(["qmake"] + args + [qmake_cxxflags])

