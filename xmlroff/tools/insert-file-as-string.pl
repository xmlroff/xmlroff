#!/usr/bin/perl

# Fo
# insert-file-as-string.pl: Insert a file into a C program as a string
#
# Copyright (C) 2006 Sun Microsystems
#
# $Id: insert-file-as-string.pl,v 1.1 2006/04/16 20:27:09 tonygraham Exp $
#
# See COPYING for the status of this software.
#

# Reads a text file, converts it into a form that is safe to include
# in a C source file, then reads a C source code file and replaces all
# occurrences of a string ('REPLACE_ME' by default) with the string
# form of the text file.  Result is printed to STDOUT.

############################################################
# Library modules
use Getopt::Long;

############################################################
# Constants
#
# Usage statement
$cUsage = <<"EndOfUsage";
Usage:
perl $0 --file <file> <c-file>

where:
  file   = File to insert
  c-file = C source code file into which to insert file
EndOfUsage

############################################################
# Global variables

# File
$gFile = '';
# Token to replace
$gToken = 'REPLACE_ME';


############################################################
# Main program

&GetOptions("file=s" => \$gFile,
	    "token:s"      => \$gToken);

if ($gToken eq '') {
    $gToken = "REPLACE_ME";
}

# Die if we don't have any files
if (@ARGV != 1 || $gFile eq '') {
    die $cUsage;
}

open(FILE, $gFile) or die "Couldn't open file: \"", $gFile, "\"";

undef $/;

$gFileString = <FILE>;

$/ = "\n";
chomp $gFileString;

$gFileString =~ s/"/\\"/g;

$gFileString =~ s/^/"/mg;
$gFileString =~ s/$/\\n"/mg;

#print $gFileString;

while (<>) {
    s/$gToken/$gFileString/g;
    print $_
}
