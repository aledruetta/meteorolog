#! /usr/bin/env python
# coding: utf-8

import getopt
import sys
from curses import wrapper
import meteoro_CLI


def usage():
    print """
    Usage:
        $ python meteorolog.py --help -h
        $ python meteorolog.py --port=/dev/ttyUSB0
        $ python meteorolog.py --port=/dev/ttyACM0
    """


if __name__ == "__main__":
    try:
        opts, args = getopt.getopt(sys.argv[1:], "p:h",
                                   ["port=", "gui", "help"])
    except getopt.GetoptError as err:
        print "Error:", str(err)
        usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-p", "--port"):
            port = arg
        elif opt == "--gui":
            pass
        elif opt in ("-h", "--help"):
            usage()
            sys.exit(0)

    try:
        wrapper(meteoro_CLI.main, port)       # Call main(stdscr, port)
    except KeyboardInterrupt:
        print "Exit Meteoro Log: Ctrl-C Keyboard Interrupt"
    except OSError as err:
        print err
    except NameError as err:                  # If no port
        print err
        usage()
        sys.exit(2)
