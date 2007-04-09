#! /usr/local/bin/perl
#
# Copyright (c) 2006 Sun Microsystems
#
# $Id: h2pl.pl,v 1.3 2007/04/09 20:18:27 menteith Exp $
#
# Perl script to create 'config.xsl' from 'config.h'.
#
# See COPYING for the status of this software.

############################################################
# Library modules
use Getopt::Long;

############################################################
# Constants
#
# Usage statement
$cUsage = <<"EndOfUsage";
Usage:
perl $0 HeaderFile

where:
  HeaderFile    = Header file created by configure, e.g., 'config.h'.
EndOfUsage

############################################################
# Main program

# Die if we don't have any files
if (@ARGV != 1) {
    die $cUsage;
}

$gHeaderFile = shift;

# Make sure we have a header file.
if (-e $gHeaderFile) {
    -f _ ||
	die "\"$gHeaderFile\" exists but is not a file." .
	    "  Cannot continue.\n";
    -r _ ||
	die "Cannot read \"$gHeaderFile\".  Cannot continue.\n";
} else {
    die "Directory \"$gHeaderFile\" does not exist.  Cannot continue.\n";
}

open(HEADERFILE, "$gHeaderFile") ||
    die "Couldn't open file \"$gTestsDir\" for reading." .
    "  Cannot continue.\n";

$gHeaderFile =~ /\.h$/;
$gBasename = $`;

open(PERLFILE, ">$gBasename.pl");


print PERLFILE "# Generated from $gHeaderFile by $0.\n";

while (<HEADERFILE>) {
    if (/^$/) {
	print PERLFILE "\n";
    } elsif (/^\/\*(.*)\*\/$/) {
	print PERLFILE "#$1\n";
    } elsif (/^\/\*(.*)/) {
	print PERLFILE "#$1\n";
    } elsif (/(.*)\*\/$/) {
	print PERLFILE "#$1\n";
    } elsif (/^#define ([^ ]+) 1$/) {
	print PERLFILE "\$$1=\"true\";\n";
    } elsif (/^#define ([^ ]+) 0$/) {
	print PERLFILE "\$$1=\"false\";\n";
    } elsif (/^#define ([^ ]+) (\d+)$/) {
	print PERLFILE "\$$1=$2;\n";
    } elsif (/^#define ([^ ]+) \"([^"]*)\"$/) {
	print PERLFILE "\$$1=\"$2\";\n";
    } else {
	warn "No match for '$_'";
    }
}

print PERLFILE "1;\n";

close(PERLFILE);
close(HEADERFILE);
