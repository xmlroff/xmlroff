#! /usr/local/bin/perl
#
# Copyright (c) 2001, 2002, 2004 Sun Microsystems
#
# Perl script to create 'stereo' images of PNG files and their
# reference versions.
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
perl $0 [-force] TestDir

where:
 -force         = Force generation of PNG files
  TestDir       = Directory containing the test directories
EndOfUsage

# ImageMagick 'composite' program
$cComposite = "/usr/bin/composite";

############################################################
# Main program

my $force;
$result = GetOptions ("force"  => \$force);  # flag

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

TESTDIR:
foreach $gTestDir (@lTestDirs) {
    local(@lPwdPNGFiles);

    # Check if the test directory is both readable and writable
    if (!-r $gTestDir || !-w _) {
	warn "Could not read and/or write to \"$gTestDir\" directory." .
	    "  Skipping \"$gTestDir\".\n";
    }

    warn "Entering \"$gTestDir\".\n";
    chdir $gTestDir ||
	die "Couldn't change to  directory \"$gTestDir\"." .
	    "  Cannot continue.\n";

    opendir(PWD, ".") ||
	die "Couldn't open directory \"$gTestDir\" for reading." .
	    "  Cannot continue.\n";
    if (! -e "./ref") {
	mkdir("./ref") ||
	    die "Couldn't create directory \"$gTestDir/ref\".  Cannot continue";
    }
    opendir(REFDIR, "./ref") ||
	die "Couldn't open directory \"$gTestDir/ref\" for reading." .
	    "  Cannot continue.\n";
    if (! -e "./diff") {
	mkdir("./diff") ||
	    die "Couldn't create directory \"$gTestDir/diff\".  Cannot continue";
    }
    opendir(DIFFDIR, "./diff") ||
	die "Couldn't open directory \"$gTestDir/diff\" for reading." .
	    "  Cannot continue.\n";
    # Check if the 'stereo' subdirectory is writable
    if (! -e "./stereo") {
	mkdir("./stereo") ||
	    die "Couldn't create directory \"$gTestDir/stereo\".  Cannot continue";
    }
    if (!-w "./stereo") {
	die "Cannot write to directory \"$gTestDir/stereo\".  Cannot continue.\n";
    }

    @lPwdPDFFiles = sort (grep (/\.pdf$/, readdir (PWD)));

    foreach $lPDFFile (@lPwdPDFFiles) {
	local($lBasename);

	$lPDFFile =~ /\.pdf$/;
	$lBasename = $`;

	if (-e "diff/$lPDFFile") {
	    rename "diff/$lPDFFile", "diff/$lPDFFile.bak";
	}

	if (-e "ref/$lPDFFile") {
	    # 'diff' needs to ignore the 'CreationDate' line since
	    # it change each time the test is run.
	    system "diff -N -a -I \"^/ID\" -I \"^/CreationDate\" ref/$lPDFFile $lPDFFile 1>diff/$lPDFFile 2>>diff/$lPDFFile";
	    if ($? >> 8 > 2) {
		$gError++;
		warn("Creating 'diff' of \"$lPDFFile\" failed.");
	    }
	}

	$lCmpRc = 0xffff & system "cmp -s diff/$lPDFFile diff/$lPDFFile.bak";

	if (!-e "$lBasename.00.png" || $lCmpRc != 0) {
	    # The previous run may have produced more pages
	    # than the current run, which can lead to odd results
	    # from a mix of old and new PNG files, so delete
	    # all the old PNG files.
	    if (-e "$lBasename.00.png") {
		unlink(glob("$lBasename.*.png"));
	    }
	    $rc = 0xffff & system "convert -depth 8 -type palette $lPDFFile $lBasename.%02d.png";
	    if ($rc != 0) {
		$gError++;
		warn("Creating PNG of \"$lPDFFile\" failed.");
	    }
	    rewinddir PWD;

	    @lPwdPNGFiles = sort (grep (/^$lBasename\.\d{2}\.png$/, readdir (PWD)));

	    foreach $lPNGFile (@lPwdPNGFiles) {
		system "diff -N $lPNGFile ref/$lPNGFile 1>diff/$lPNGFile 2>>diff/$lPNGFile";
		if ($? >> 8 > 2) {
		    $gError++;
		    warn("Creating 'diff' of \"$lPNGFile\" failed.");
		}
		if (-e "ref/$lPNGFile" &&
		    (!-e "stereo/$lPNGFile" || -M $lPNGFile < -M "stereo/$lPNGFile") &&
		    (!-e "diff/$lPNGFile" || -s _)) {
		    $rc = 0xffff & system "$cComposite -stereo $lPNGFile ref/$lPNGFile stereo/$lPNGFile";
		    if ($rc != 0) {
			$gError++;
			die("Creating 'stereo' of \"$lPNGFile\" failed." .
			    " Cannot continue.");
		    }
		}
	    }
	}
    }

    closedir PWD;
    closedir DIFFDIR;
    closedir REFDIR;

    warn "Leaving \"$gTestDir\".\n";
    chdir "..";
}

closedir TESTS;

