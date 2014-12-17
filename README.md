## CyCells

CyCells is a modeling framework to facilitate the creation and use of microbiological agent-based models.

## Usage Example

Run from the command line as follows:

    > ./CyCells -seed [random seed] -def [.def file] -init [.init file] -dur [duration in seconds] -step [step size in seconds] -hist [output file]

## Installation

CyCells is a Qt4 application.  Follow standard Qt installation procedures:

1) Use "qmake" to create a .pro file.

2) Add "QT += opengl" to the .pro file to add support for OpenGL

3) Run "make" to compile QtCyCells

4) Run "make -f Makefile_CyCells" to compile CyCells (command-line version)


## Contributors

CyCells was created by Christina Warrender and is maintained by Drew Levin.

## License

CyCells is licensed by the GNU Public License v3.0

http://www.gnu.org/copyleft/gpl.html
