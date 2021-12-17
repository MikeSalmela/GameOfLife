A Qt based implementation for game of life.

Building:
    Run qmake, then make, or use build.sh script
    Requires qt5. On ubuntu the package is called qt5-default.

Usage:
    After building execute GameOfLife -h for help.

Notes:
    First designed the program the way that first came to mind: Looping through all neighbour cells to check if they're living.
    After that started thinking about a less bruteforcy way to keep track of live neighbour cells. In the second algorithm
    the neighbour tracking is the responsibility of the changing cell. When a cell changes, it notifys it's neighbours about it.
    With quick testing it seems that notifying the neighbours when changing is the faster way.
    However, the way I decided to draw the cells with Qt proved to be a terrible choice, so the backend
    algorithm doesn't really matter in this version. It can be tested without UI by setting the NO_UI variable in the .pro file as 1.
    For a decent version, the UI implementation would need to be changed to something else.
