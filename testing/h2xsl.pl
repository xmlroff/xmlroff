#! /usr/local/bin/perl
#
# Copyright (c) 2006 Sun Microsystems
#
# $Id: h2xsl.pl,v 1.1 2006/07/24 16:16:54 tonygraham Exp $
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

open(XSLFILE, ">$gBasename.xsl");


print XSLFILE <<EndOfHeader;
<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
  <!-- $gBasename.xsl.  Generated from $gHeaderFile by $0. -->
EndOfHeader

while (<HEADERFILE>) {
    if (/^$/) {
	print XSLFILE "\n";
    } elsif (/^\/\*(.*)\*\/$/) {
	($lComment = $1) =~ s/--/ - -/g;
	print XSLFILE "  <!--$lComment-->\n";
    } elsif (/^\/\*(.*)/) {
	($lComment = $1) =~ s/--/ - -/g;
	print XSLFILE "  <!--$lComment\n";
    } elsif (/(.*)\*\/$/) {
	($lComment = $1) =~ s/--/ - -/g;
	print XSLFILE "    $lComment-->\n";
    } elsif (/^#define ([^ ]+) 1$/) {
	print XSLFILE "  <xsl:param name=\"$1\" select=\"true()\"/>\n";
    } elsif (/^#define ([^ ]+) 0$/) {
	print XSLFILE "  <xsl:param name=\"$1\" select=\"false()\"/>\n";
    } elsif (/^#define ([^ ]+) (\d+)$/) {
	print XSLFILE "  <xsl:param name=\"$1\" select=\"$2\"/>\n";
    } elsif (/^#define ([^ ]+) \"([^"]*)\"$/) {
	print XSLFILE "  <xsl:param name=\"$1\" select=\"'$2'\"/>\n";
    } else {
	warn "No match for '$_'";
    }
}

print XSLFILE "</xsl:stylesheet>\n";

close(XSLFILE);
close(HEADERFILE);
