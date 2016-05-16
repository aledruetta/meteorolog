#! /usr/bin/env python
# coding: utf-8

import getopt
import sys
from curses import wrapper
import meteoro_CLI


def usage():
    pass


if __name__ == "__main__":
    try:
        opts, args = getopt.getopt(sys.argv[1:], "p:", ["port=", "gui"])
    except getopt.GetoptError as err:
        print "Error:", str(err)
        usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-p", "--port"):
            port = arg
        elif opt == "--gui":
            pass

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
