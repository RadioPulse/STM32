# STM32
This is ST platform based project by RadioPulse.

### Tool Installation

If you don't have a build environment, run `configure.sh` script.

> $ ./configure.sh

### Build

If you want to build a project with Makefile, follow this guide.

1. Build all projects

> $ make

2. Build specific project

> $ make <project_name>
>
> Ex) $ make stm32f401re-nucleo

### Run

The binary files are in `/projects/bin` directory.

You can program your board with binary file.

### Support

- Host System

  - Tested on Ubuntu 4.4.0

- Target System

  - Tested on STM32F401RE-Nucleo board
