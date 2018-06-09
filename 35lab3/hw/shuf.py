#!/usr/bin/python3


import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename=None, arglist=None):
        if filename == '-':
            self.lines = sys.stdin.readlines()
        elif arglist:
            self.lines = arglist
        elif not filename and not arglist:
            self.lines = sys.stdin.readlines()
        else:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

    def chooseline(self, count=1, repeat=False, echo=False):
        result = []
        if repeat:
            return list(self.lines)
            #random.shuffle(self.lines)
        else:
            result = list(set(self.lines))
        return result

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Write a random permutation of the input lines to standard output.

With no FILE, or when FILE is -, read standard input.

Mandatory arguments to long options are mandatory for short options too."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-e", "--echo",
                      action="store_true", dest="echo", default=False,
                      help="treat each ARG as an input line")
    parser.add_option("-n", "--headline",
                      action="store", dest="count", default=1,
                      help="output at most COUNT lines")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="repeat", default=False,
                      help="output lines can be repeated")
    
    options, args = parser.parse_args(sys.argv[1:])
    print(options)
    print(args)
    try:
        numlines = int(options.count)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.count))
    arglines = []
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    elif options.echo == True:
        for arg in args:
            arglines.append(arg)
        numlines = len(arglines)
    elif len(args) > 1 and options.echo == False:
        parser.error("wrong number of operands")
    
    input_file = args[0]
    try:
        generator = randline(input_file,arglines)
        lines = generator.chooseline(numlines,options.repeat,options.echo)
        for i in range(numlines):
            sys.stdout.write(lines[i])
    except IOError as e:
            errno = e.errno
            strerror = e.strerror
            parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
