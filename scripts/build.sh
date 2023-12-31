#!/usr/bin/env bash

# Copyright (C) 2023 Ashish Kumar
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program in the file: gpl-3.0.text. 
# If not, see <http://www.gnu.org/licenses/>.

CURRENT_DIRECTORY=$(pwd)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

#######################################
# Build the C++ project
# Globals:
#   CURRENT_DIRECTORY
# Arguments:
#   None
# Outputs:
#   Writes the clean steps to the console
#######################################
clean() {
    echo "Clearning the previous builds."
    rm -rf ${CURRENT_DIRECTORY}/build/
}

#######################################
# Build the C++ project
# Globals:
#   CURRENT_DIRECTORY, SCRIPT_DIR
# Arguments:
#   None
# Outputs:
#   Writes the build steps to the console
#######################################
build() 
{
    echo "Building the project"

    # Create the build directory if it doesn't exist
    mkdir -p $CURRENT_DIRECTORY/build

    # Change to the build directory
    cd $CURRENT_DIRECTORY/build

    # Run cmake and make
    cmake $SCRIPT_DIR/..
    make
    cd -

    echo "Build complete"
}

#######################################
# Prepare the system for building
# Globals:
#   None
# Arguments:
#   None
# Outputs:
#   Writes the prepare steps to the console
#######################################
prepare_system()
{
    echo "Installing dependencies."
    sudo apt update -y
    sudo apt install -y make build-essential cmake 
}

#######################################
# The main function
# Globals:
#   None
# Arguments:
#   None
# Outputs:
#   None
#######################################
main() 
{  
  build  
}

for arg in "$@"
do
  if [ "$arg" = "--prereq" ] || [ "$arg" == "-p" ]; then  
    prepare_system
  fi
done

for arg in "$@"
do
  if [ "$arg" = "--clean" ] || [ "$arg" == "-c" ]; then  
    clean
  fi
done

main 

for arg in "$@"
do
  if [ "$arg" = "--install" ] || [ "$arg" == "-i" ]; then  
    install
  fi
done