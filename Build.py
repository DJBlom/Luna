##########################################################################
# Contents: Python Build Script
# Author: Dawid Blom
# Date: July 7, 2023
#
#
# NOTE: 
# There are two key variables in this script that requires accurate
# information.
#
# Variable 1: boardType = "This specifies the board type you want to use"
# Variable 2: confFiles = "This specifies the .conf file/s"
#
# IMORTANT: 
# When specifying multiple .conf files, please just add them behind the
# existing confFiles string, like so: 
#
# confFiles = "path/to/prj.conf path/to/another.conf path/to/another.conf" 
#
# Ensure that they are apart of the same string but seperated by spaces
##########################################################################
import subprocess

def BuildZephyrProject():
    boardType = "mimxrt1060_evkb"
    confFiles = "prj.conf"

    subprocess.run(["west", "build", "--pristine=always", "-b", boardType,  "--", "-DCONF_FILE=", confFiles], check=True)


if __name__ == "__main__":
    BuildZephyrProject()
