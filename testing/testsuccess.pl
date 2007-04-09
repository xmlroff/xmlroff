#! /usr/local/bin/perl
#
# Copyright (c) 2001, 2002, 2004 Sun Microsystems
#
# $Id: testsuccess.pl,v 1.3 2006/07/24 16:44:56 tonygraham Exp $
#
# Perl script generate an XML summary of files and sizes.
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
perl $0 TestDir

where:
  TestDir       = Directory containing the test directories
EndOfUsage

############################################################
# Main program

# Die if we don't have any files
if (@ARGV != 1) {
    die $cUsage;
}

$gTestsDir = shift;

# Make sure we have a "tests" directory
if (-e $gTestsDir) {
    -d _ ||
	die "\"$gTestsDir\" exists but is not a directory." .
	    "  Cannot continue.\n";
    -w _ ||
	die "Cannot write to directory \"$gTestsDir\".  Cannot continue.\n";
} else {
    die "Directory \"$gTestsDir\" does not exist.  Cannot continue.\n";
}

opendir(TESTS, "$gTestsDir") ||
    die "Couldn't open directory \"$gTestsDir\" for reading." .
    "  Cannot continue.\n";

chdir $gTestsDir;

@lTestDirs = sort(grep(-d && !/^\.+/ && !/^CVS$/ && !/^autom4te\.cache$/, readdir(TESTS)));

print "<?xml version=\"1.0\"?>\n";
print "<!-- Automatically generated file.  DO NOT EDIT. -->\n";
print "<testsuccess>\n";

TESTDIR:
foreach $gTestDir (@lTestDirs) {
    local(@lPDFFiles);
    local(@lPwdPNGFiles, @lPwdLogFiles);
    local(@lRefPNGFiles, @lRefLogFiles);
    local(@lDiffPNGFiles, @lDiffLogFiles);
    local(@lStereoPNGFiles);

    # Check if the directory is both readable and writable
    if (!-r $gTestDir || !-w _) {
	warn "Could not read and/or write to \"$gTestDir\" directory." .
	    "  Skipping \"$gTestDir\".\n";
    }

    warn "Entering \"$gTestDir\".\n";
    chdir $gTestDir ||
	die "Couldn't change to  directory \"$gTestDir\"." .
	    "  Cannot continue.\n";
    print "<directory name=\"$gTestDir\">\n";

    opendir(PWD, ".") ||
	die "Couldn't open directory \"$gTestDir\" for reading." .
	    "  Cannot continue.\n";
    opendir(REFDIR, "./ref") ||
	die "Couldn't open directory \"$gTestDir/ref\" for reading." .
	    "  Cannot continue.\n";
    opendir(DIFFDIR, "./diff") ||
	die "Couldn't open directory \"$gTestDir/diff\" for reading." .
	    "  Cannot continue.\n";
    opendir(STEREODIR, "./stereo") ||
	die "Couldn't open directory \"$gTestDir/stereo\" for reading." .
	    "  Cannot continue.\n";

    @lPDFFiles = sort (grep (/\.pdf$/, readdir (PWD)));
    rewinddir PWD;
    @lPwdPNGFiles = sort (grep (/\.png$/, readdir (PWD)));
    rewinddir PWD;
    @lPwdLogFiles = sort (grep (/\.log$/, readdir (PWD)));

    @lRefPNGFiles = sort (grep (/\.png$/, readdir (REFDIR)));
    rewinddir REFDIR;
    @lRefLogFiles = sort (grep (/\.log$/, readdir (REFDIR)));

    @lDiffPNGFiles = sort (grep (/\.png$/, readdir (DIFFDIR)));
    rewinddir DIFFDIR;
    @lDiffLogFiles = sort (grep (/\.log$/, readdir (DIFDIR)));
    rewinddir DIFFDIR;
    @lDiffPDFFiles = sort (grep (/\.pdf$/, readdir (DIFDIR)));

    @lStereoPNGFiles = sort (grep (/\.png$/, readdir (STEREODIR)));

    foreach $lPDFFile (@lPDFFiles) {
	local ($lBasename, $lPwdLogFile, $lDiffLogFile, $lRefLogFile);
	local (@lPwdFiles, @lDiffFiles, @lRefFiles, @lStereoFiles);

	print "<pdf name=\"" . $lPDFFile . "\"";
	print " size=\"" . (-s $lPDFFile) . "\"";
	print ">\n";

	$lPDFFile =~ /\.pdf$/;
	$lBasename = $`;

	@lPwdFiles = grep (/^$lBasename\.\d{2}\.png$/, @lPwdPNGFiles);
	($lPwdLogFile) = grep (/^$lBasename\.log$/, @lPwdLogFiles);
	@lRefFiles = grep (/^$lBasename\.\d{2}\.png$/, @lRefPNGFiles);
	($lRefLogFile) = grep (/^$lBasename\.log$/, @lRefLogFiles);
	@lDiffFiles = grep (/^$lBasename\.\d{2}\.png$/, @lDiffPNGFiles);
	($lDiffLogFile) = grep (/^$lBasename\.log$/, @lDiffLogFiles);
	@lStereoFiles = grep (/^$lBasename\.\d{2}\.png$/, @lStereoPNGFiles);

	print "<pwd count=\"" . ($#lPwdFiles + 1) . "\">\n";
	foreach $lPwdFile (@lPwdFiles) {
	    print "<png name=\"$lPwdFile\" size=\"" . (-s $lPwdFile) . "\"/>\n";
	}
	if ($lPwdLogFile) {
	    print "<log name=\"" . $lPwdLogFile . "\" size=\"" . (-s "$lPwdLogFile") . "\"/>\n";
	}
	print "</pwd>\n";

	print "<ref count=\"" . ($#lRefFiles + 1) . "\">\n";
	foreach $lRefFile (@lRefFiles) {
	    print "<png name=\"$lRefFile\" size=\"" . (-s "ref/$lRefFile") . "\"/>\n";
	}
	if ($lRefLogFile) {
	    print "<log name=\"" . $lRefLogFile . "\" size=\"" . (-s "$lRefLogFile") . "\"/>\n";
	}
	print "</ref>\n";

	print "<diff count=\"" . ($#lDiffFiles + 1) . "\">\n";
	foreach $lDiffFile (@lDiffFiles) {
	    print "<png name=\"$lDiffFile\" size=\"" . (-s "diff/$lDiffFile") . "\"/>\n";
	}
	if ($lDiffLogFile) {
	    print "<log name=\"" . $lDiffLogFile . "\" size=\"" . (-s "$lDiffLogFile") . "\"/>\n";
	}
	print "</diff>\n";

	print "<stereo count=\"" . ($#lStereoFiles + 1) . "\">\n";
	foreach $lStereoFile (@lStereoFiles) {
	    print "<png name=\"$lStereoFile\" size=\"" . (-s "stereo/$lStereoFile") . "\"/>\n";
	}
	print "</stereo>\n";

	print "</pdf>\n";
    }

    closedir PWD;
    closedir DIFFDIR;
    closedir REFDIR;

    warn "Leaving \"$gTestDir\".\n";
    print "</directory>\n";
    chdir "..";
}

closedir TESTS;

print "</testsuccess>\n";
