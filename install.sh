#!/usr/bin/env bash
PYTHON3=`which python3`

################################################################################
# Configuration
################################################################################
PYVENV_PATH=.pyvenv
CLANG_VERSION=10
CPP_VERSION=17

# FIXME: Should we add scons here?
APT_PKGS="
	clang-tools-${CLANG_VERSION} \
        cmake llvm-${CLANG_VERSION} \
        graphviz \
        libgraphviz-dev \
        libjpeg-dev \
        libprotobuf-dev \
        protobuf-compiler \
        python3-pip \
        zlib1g-dev
	"

PYTHON_PKGS="
	image \
	numpy \
	pep8 \
	scons \
	torch
	"

################################################################################
# Main
################################################################################
VIRTUAL=

install_apt() {
	echo "To run 'janncy', the following (apt) packages needs to be installed:"
	echo "  $(echo ${APT_PKGS})"
	while true; do
		read -p "sudo access is required, continue? [y/n] " yn
		case $yn in
			[Yy]* ) sudo apt update && sudo apt install -y ${APT_PKGS}; break;;
			[Nn]* ) break;;
			* ) echo "Please answer 'y' or 'n'.";;
		esac
	done
}

install_pip() {
	if [[ -z "${PYTHON3}" ]]
	then
		      echo "ERROR: python3 not installed"
		      exit
	fi

	if [[ "${VIRTUAL}" == "y" ]]
	then
		PYTHON_PKGS="${PYTHON_PKGS} virtualenv"
		if [[ -d ${PYVENV_PATH} ]]
		then
			echo "${PYVENV_PATH} exist, reusing the enviroment"
			source ${PYVENV_PATH}/bin/activate
		else
			echo "Setting up virtual enviroment in ${PYVENV_PATH}"
			echo "${PYTHON3}"
			${PYTHON3} -m virtualenv -p ${PYTHON3} ${PYVENV_PATH}
			source ${PYVENV_PATH}/bin/activate
		fi
	else
		echo "Virtual enviroment NOT chosen, pip packages will be installed to the host system."
		IFS=
		read -r -p "Waiting 10 seconds, press any key to abort ... " -t 10 -n 1 -s stop
		if [[ ! -z "${stop}" ]] || [[ ${stop} == "" ]]
		then
			exit
		fi
	fi
	pip install ${PYTHON_PKGS}
	pip list
}

help() {
	echo "Usage:"
	echo "  install.sh -h           Display this help message"
	echo "  install.sh -v           Setup a virtual python enviroment"
}

while getopts "hv" flag
do
	case "${flag}" in
		h) help; exit;;
		v) VIRTUAL=y;;
		\?) echo "ERROR: Unknown option provided"; help; exit;;
	esac
done

install_apt
install_pip
