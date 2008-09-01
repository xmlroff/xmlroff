#! /usr/local/bin/perl
#
# Copyright (c) 2007-2008 Menteith Consulting Ltd
#
# Write a starter 'testsuite.xml' file for the XML files in
# subdirectories of the specified directory.
#
# See COPYING for the status of this software.

############################################################
# Library modules
use Getopt::Long;
use XML::XPath;
use XML::XPath::XMLParser;

############################################################
# Constants
#
# Usage statement
$cUsage = <<"EndOfUsage";
Usage:
perl $0 [--verbose] [--stylesheet Stylesheet] TestsDir

where:
  Stylesheet    = Filename or URL of stylesheet for all tests
  TestsDir      = Directory containing the tests directories

Write a starter 'testsuite.xml' file for the XML files in
subdirectories of the specified directory.
EndOfUsage

############################################################
# Main program

&GetOptions("verbose" => \$gVerbose,
            "stylesheet:s" => \$gStylesheet);

if (defined($gStylesheet)) {
    $gStylesheetAttr = "\n    xsl=\"$gStylesheet\"";
} else {
    $gStylesheetAttr = "";
}

# Die if we don't have any files
if (@ARGV != 1) {
    die $cUsage;
}

$gTestsDir = shift;

# Make sure we have a test directory
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

@lTestDirs = sort(grep(-d && !/^\.+/ && !/^CVS$/, readdir(TESTS)));

if ($gVerbose) {
    print STDERR "Stylesheet::", $gStylesheet, ":\n";
    print STDERR "Test directories::", join(":", @lTestDirs), ":\n";
}

print << "EndOfTestsuiteStart";
<?xml version="1.0" encoding="utf-8"?>
<testsuite profile="Test Suite">
EndOfTestsuiteStart

TESTDIR:
foreach $gTestDir (@lTestDirs) {
    &ProcessDir($gTestDir);
}


print << "EndOfTestsuiteEnd";
</testsuite>
EndOfTestsuiteEnd

############################################################
# $ProcessDir($pDir)
sub ProcessDir {
    my($pDir) = @_;
    my($lRefFileCount);
    my($lChangeFileCount);

    if ($gVerbose) {
	print STDERR "Processing test dir: '", $gTestDir, "'\n";
    }

    # Check if the directory is readable
    if (!-r $pDir) {
	warn "Could not read \"$pDir\" directory." .
	    "  Skipping \"$pDir\".\n";
	next TESTDIR;
    }

    warn "Entering \"$pDir\".\n";
    chdir $pDir ||
	die "Couldn't change to  directory \"$pDir\"." .
	"  Cannot continue.\n";

    opendir(PWD, ".") ||
	die "Couldn't open directory \"$pDir\" for reading." .
	"  Cannot continue.\n";

    print "<testcases profile=\"$pDir\" base=\"$pDir\">\n";

    my(@lPwdSourceFiles) = sort (grep (/\.(xml)$/, readdir (PWD)));

    if (@lPwdSourceFiles) {
	foreach $lSourceFile (@lPwdSourceFiles) {
	    local($lBasename);

	    $lSourceFile =~ /\.xml$/;
	    $lBasename = $`;

	    my $xp = XML::XPath->new(filename => $lSourceFile);

	    my $info = $xp->findvalue('/testcase/info'); # find info

	    print <<EndOfTest;
<test id="$lBasename"
    xml="$lBasename.fo"$gStylesheetAttr
    results="$lBasename.pdf"
    fo="multiple">$info</test>
EndOfTest

	}
    } else {
	warn "No XML files in \"$pDir\".\n";
    }

    rewinddir PWD;
    my(@lSubDirs) =
	sort(grep(-d && !/^\.+/ && !/^CVS$/, readdir(PWD)));
    closedir PWD;

    foreach $lSubDir (@lSubDirs) {
	&ProcessDir($lSubDir);
    }


    print "</testcases>\n";

    warn "Leaving \"$pDir\".\n";
    chdir "..";
}

