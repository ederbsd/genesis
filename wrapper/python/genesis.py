import sys

from ctypes import *
lib = cdll.LoadLibrary('./lib/libproxy_genesis.so')

class genesis(object):
    def __init__(self):
        self.obj = lib.proxy_genesis_new()

    def printf(self, format, *args):
        sys.stdout.write(format % args)

    def details(self):
        lib.proxy_genesis_details(self.obj)

    def compute_geodist(self, lat1, lon1, lat2, lon2, unit):
        lib.proxy_genesis_compute_geodist(self.obj, c_double(lat1), c_double(lon1), 
                                          c_double(lat2), c_double(lon2), c_char_p(unit))

    def print_geodist(self):
        d_val = c_double(lib.proxy_genesis_print_geodist(self.obj))
        self.printf("distance = %f\n", d_val.value)

    def set_value(self, s1):
        lib.proxy_genesis_set_value(self.obj, c_char_p(s1))

    def print_value(self):
        c_str = c_char_p(lib.proxy_genesis_print_value(self.obj))
        print c_str.value

    def add_usage(self, desc):
        lib.proxy_genesis_add_usage(self.obj, desc)

    def print_usage(self):
        lib.proxy_genesis_print_usage(self.obj)

#
# Main
#
g = genesis()

# Show details build.
g.details()

# Compute geometry distance.
g.compute_geodist(-23.32, -46.38, -22.54, -43.12, "K")
g.print_geodist()

# Test message.
g.set_value("TEST")
g.print_value()

# Add usage command line.
g.add_usage( "Description:" );
g.add_usage( "   This application xxx kkk oppop popopo klklkl..\n" );
g.add_usage( "Usage: " );
g.add_usage( "   [<OPTIONS>] [<OPT1>] [<OPT21>] [<OPT3>] [<OPT4>]\n" );
g.add_usage( "Options:" );
g.add_usage( "      --version | -v       Display version information." );
g.add_usage( "      --help | -h          Prints this usage message." );
g.print_usage()


