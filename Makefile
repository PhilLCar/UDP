# The following variables need to be set prior to including library.mk

# Library name
NAME = udp

# Versioning
include ver/version.mk

# If the project is separated among multiple sub-folders
PROJECT_ROOTS = srv cli com

# Additionnal libraries (ex: -pthread, -lmath, etc)
ADD_LIBRARIES = 

# Additionnal flags for the compiler
ADD_CFLAGS = 

# Include the template
include $(CUT_HOME)CUT/res/library.mk
