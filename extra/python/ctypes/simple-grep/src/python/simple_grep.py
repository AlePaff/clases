import sys
# Descomentar las lineas relacionadas a cProfile
# o ejecutar python3 -m cProfile ../simple_grep.py <archivo> <expr>
#
#import cProfile

def simple_grep(file, expr):
    #pr = cProfile.Profile()
    #pr.enable()
    n = 0
    for line in file:
        if line.find(expr) != -1:
            print("Line %d: %s" % (n, line))
        n += 1
    #pr.disable()
    #pr.print_stats()


def main():
    if len(sys.argv) < 3:
        print("Uso: %s, <file> <expr>" % sys.argv[0])
    with open(sys.argv[1]) as file:
        simple_grep(file, sys.argv[2])

if __name__ == '__main__':
    main()