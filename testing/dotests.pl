#! /perl5/bin/perl.exe
#
# Copyright (c) 2001, 2002 Sun Microsystems
# Copyright (c) 2007 Menteith Consulting Ltd
#
# Perl script to run test scripts
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
# Global variables

%gDiffIgnore = (
		log => [ '[^.]+\.pl (started|ended) at', 'composite' ],
		err => [ 'does not have' ],
		);

############################################################
# Main program

&GetOptions("verbose" => \$gVerbose);

$gVerboseSwitch = $gVerbose? ' -v': '';

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

@lTestDirs = sort(grep(-d && !/^\.+/ && !/^(autom4te\.cache|config)$/, readdir(TESTS)));

if ($gVerbose) {
    print STDERR "Test directories::", join(":", @lTestDirs), ":\n";
}

TESTDIR:
foreach $gTestDir (@lTestDirs) {
    local($lRefFileCount);
    local($lChangeFileCount);

    if ($gVerbose) {
	print STDERR "Processing test dir: '", $gTestDir, "'\n";
    }

    # Check if the directory is both readable and writable
    if (!-r $gTestDir || !-w _) {
	warn "Could not read and/or write to \"$gTestDir\" directory." .
	    "  Skipping \"$gTestDir\".\n";
	next TESTDIR;
    }
    # Check if has "test.sh" file that we can use
    if (!-e "$gTestDir/test.sh" || !-f _ || !-r _) {
	# Couldn't find the test script file
	warn "\"$gTestDir/test.sh\" does not exist or could not" .
	    " be read.  Skipping \"$gTestDir\".\n";
	next TESTDIR;
    }
    # Check we have the reference file directory
    if (-e "$gTestDir/ref") {
	if (!-d _) {
	    warn "\"$gTestDir/ref\" is not a directory." .
		"  Skipping \"$gTestDir\".\n";
	    next TESTDIR;
	}
    } else {
	mkdir("$gTestDir/ref", 0777) ||
	    warn "Could not create reference file directory".
		" \"$gTestDir/ref\".  Skipping \"$gTestDir\".\n",
		next TESTDIR;
    }

    # Check we have the differences file directory
    if (-e "$gTestDir/diff") {
	if (!-d _) {
	    warn "\"$gTestDir/diff\" is not a directory." .
		"  Skipping \"$gTestDir\".\n";
	    next TESTDIR;
	}
    } else {
	mkdir("$gTestDir/diff", 0777) ||
	    warn "Could not create differences file directory" .
		" \"$gTestDir/diff\".  Skipping \"$gTestDir\".\n",
		next TESTDIR;
    }

    # Check we have the stereo file directory
    if (-e "$gTestDir/stereo") {
	if (!-d _) {
	    warn "\"$gTestDir/stereo\" is not a directory." .
		"  Skipping \"$gTestDir\".\n";
	    next TESTDIR;
	}
    } else {
	mkdir("$gTestDir/stereo", 0777) ||
	    warn "Could not create stereo file directory" .
		" \"$gTestDir/stereo\".  Skipping \"$gTestDir\".\n",
		next TESTDIR;
    }

    warn "Running test \"$gTestDir\".\n";
    # Only now do we try running the script
    chdir $gTestDir;
    system("bash $gVerboseSwitch < test.sh > test.out") == 0 ||
	warn "Test execution error:$?\n";


#    opendir(REF, "ref") ||
#	warn "Couldn't open reference file directory \"$gTestDir/ref\"" .
#	    " for reading.  Cannot continue.\n", chdir "..", next TESTDIR;
#
#REFFILE:
#    foreach $lFile (sort(grep(-e && -f && -r, readdir(REF)))) {
#	$lRefFileCount++;
#
#	if (-e "diff/$lFile" && (!-f _ || !-w _)) {
#	    warn "Cannot write diff output for \"$lFile\".  Skipping file.\n";
#	    next REFFILE;
#	}
#
#	if (!-e $lFile || !-r _) {
#	    warn "\"$lFile\" does not exist or cannot be read for diff." .
#		"  Skipping \"$lFile\".\n";
#	    next REFFILE;
#	}
#
#	if (-e "ref/$lFile") {
#	    system "diff ref/$lFile $lFile 1>diff/$lFile 2>>diff/$lFile";
#	    if ($? >> 8 > 2) {
#		warn "Diff failed for \"$lFile\".\n";
#	    }
#	} else {
#	    system("echo 'new output' > diff/$lFile");
#	}
#
#	if (!-z "diff/$lFile") {
#	    local($lSuffix) = $lFile;
#	    $lSuffix =~ s/.+\.([^.]+)$/$1/;
#
#	    $lChangeFileCount++;
#
#	    if (defined($gDiffIgnore{$lSuffix})) {
#		local($lNotIgnore) = 'false';
#		local($lEvalString) = <<'EndOfWhileStart';
#while (<DIFFFILE>) {
#    if (/^\s*(<|>)/) {
#EndOfWhileStart
#
#		open (DIFFFILE, "diff/$lFile");
#
#		foreach $lString (@{$gDiffIgnore{$lSuffix}}) {
#		    $lEvalString .= "next if /$lString/;\n";
#		}
#
#		$lEvalString .= "\$lNotIgnore = 'true';\nlast;\n}\n}\n";
#
#		eval($lEvalString);
#
#		close DIFFFILE;
#
#		if ($lNotIgnore eq 'true') {
#		    warn "    \"$lFile\" changed.\n";
#		} else {
#		    warn "    \"$lFile\" changed.  Diffs ignorable\n";
#		}
#	    } else {
#		warn "    \"$lFile\" changed.\n";
#	    }
#	}
#    }
#
#    closedir REF;
#
#    warn "    No reference files.\n" unless $lRefFileCount;
#    warn "    No differences found.\n" unless $lChangeFileCount;
    chdir "..";
}

closedir TESTS;


