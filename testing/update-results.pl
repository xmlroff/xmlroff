#! /usr/bin/perl
#
# Copyright (c) 2001, 2002, 2004 Sun Microsystems
# Copyright (c) 2007-2009 Menteith Consulting Ltd
#
# Perl script to run xsltproc to update one result in 'testresults.xml'.
#
# Variables in UPPERCASE are from 'config.pl' in this directory.
#
# See COPYING for the status of this software.

#use CGI;
use CGI qw/:standard/;
use File::Copy;
require("config.pl");

$cWorkingDir = '.';
$cResultsXML = "$cWorkingDir/$TEST_RESULTS";
$cTestResultsBase = "/$PROJECT_NAME/$BASENAME";
$cTopBase = param('top-base');
$cId = param('id');
$cRefreshDelay = 1;

$gError = 0;
@gBody = ();

$gUseComment = param('comment');
$gUseComment =~ s/\`/\\`/g; #`
$gUseComment =~ s/"/\\"/g; #'

$gXsltprocCommand =
    join ('',
	  "$XSLTPROC --novalid",
	  " --stringparam id ", param('id'), 
	  " --stringparam top-base ", param('top-base'),
	  " --stringparam agreement ", param('agreement'),
	  " --stringparam futuresupport \"",  param('futuresupport'), "\"",
	  " --stringparam specproblem ", param('specproblem'),
	  " --stringparam testproblem ", param('testproblem'),
	  " --stringparam comment \"", $gUseComment, "\"",
	  " -o ${cResultsXML}.out $cWorkingDir/update-result.xsl $cResultsXML"
	  );

############################################################
# Do the work and save the error and status messages in @gBody
#

push(@gBody,
     h1("Updating \"" . param('path') . "/" . param('id') . "\""));

push(@gBody,
     table({-border=>1},
	   # Has to be 'Tr' because 'tr' is a Perl function
            Tr({-align=>CENTER,-valign=>TOP},
             [
               td(['Agreement:'     , param('agreement')]),
	       td(['Future support:', param('futuresupport') . "&#160;"]),
	       td(['Spec problem:'  , param('specproblem')]), 
	       td(['Test problem:'  , param('testproblem')]),
	       td(['Comment:'       , param('comment')])
	       ]
	      )
        ));
push(@gBody,
     hr);
push(@gBody,
     h2("Updating results file \"$cResultsXML\""));
push(@gBody,
     p("Running command:"));
push(@gBody,
     p($gXsltprocCommand));

if (!-e $cResultsXML || !-r _) {
    push(@gBody,
	 p("\"$cResultsXML\" does not exist or cannot be read." .
	   " Cannot continue\n"));
    $gError++;
}

if (!$gError && -e "${cResultsXML}.out" && (!-f _ || !-w _)) {
    push(@gBody,
	 p("Cannot write output XML file: \"${cResultsXML}.out\"." .
	   " Cannot continue.\n"));
    $gError++;
}

if (!$gError && -e "${cResultsXML}.out") {
    if (unlink("${cResultsXML}.out") != 1) {
	push(@gBody,
	     p("Cannot unlink existing output XML file: \"${cResultsXML}.out\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    $rc = 0xffff & system $gXsltprocCommand;
    if ($rc != 0) {
	$gError++;
	push(@gBody,
	     p("XSLT transformation of \"$cResultsXML\" failed." .
	       " Cannot continue.\n"));
    } else {
	push(@gBody,
	     p("XSLT transformation completed."));
    }
}

if (!$gError) {
    if (! -e "${cResultsXML}.out") {
	$gError++;
	push(@gBody,
	     p("\"${cResultsXML}.out\" was not created." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (chmod(0666, "${cResultsXML}.out") != 1) {
	$gError++;
	push(@gBody,
	     p("<tt>chmod</tt> of \"${cResultsXML}.out\" failed." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (link("$cResultsXML", "${cResultsXML}.bak") != 1) {
	$gError++;
	push(@gBody,
	     p("Move of \"$cResultsXML\" to \"${cResultsXML}.bak\" failed." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (unlink("$cResultsXML") != 1) {
	push(@gBody,
	     p("Cannot unlink results XML file: \"$cResultsXML\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (link("${cResultsXML}.out", "$cResultsXML") != 1) {
	$gError++;
	push(@gBody,
	     p("Move of \"${cResultsXML}.out\" to \"$cResultsXML\" failed." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (unlink("${cResultsXML}.out") != 1) {
	push(@gBody,
	     p("Cannot unlink output results XML file: \"${cResultsXML}.out\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (unlink("${cResultsXML}.bak") != 1) {
	push(@gBody,
	     p("Cannot unlink backup results XML file: \"${cResultsXML}.bak\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    push(@gBody,
	 p({-style=>"color: white; background-color: green"},
	   "Update completed without error."));
} else {
    push(@gBody,
	 p({-style=>"color: white; background-color: red"},
	   "Update failed. Results are indeterminate."));
}

############################################################

if (!$gError) {
    push(@gBody,
	 h1("Replacing \"" .
	    param('top-base') .
	    "/" . param('id') .
	    "\" Reference PNG Files"));
}

if (!$gError) {
    if (!chdir $cWorkingDir) {
	push(@gBody,
	     p("Couldn't chdir to \"$cWorkingDir\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (!chdir $cTopBase) {
	push(@gBody,
	     p("Couldn't chdir to \"$cWorkingDir/$cTopBase\"." .
	       "  Cannot Continue.\n"));
	$gError++;
    }
}


if (!$gError) {
    if (!opendir(PWD, ".")) {
	push(@gBody,
	     p("Couldn't open directory \"$cWorkingDir/$cTopBase\" for reading." .
	       "  Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (!opendir(DIFFDIR, "./diff")) {
	push(@gBody,
	     p("Couldn't open directory \"$cWorkingDir/$cTopBase/diff\" for reading." .
	       "  Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (!opendir(REFDIR, "./ref")) {
	push(@gBody,
	     p("Couldn't open directory \"$cWorkingDir/$cTopBase/ref\" for reading." .
	       "  Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (!opendir(STEREODIR, "./stereo")) {
	push(@gBody,
	     p("Couldn't open directory \"$cWorkingDir/$cTopBase/stereo\" for reading." .
	       "  Cannot continue.\n"));
	$gError++;
    }
}

#print "$cWorkingDir/$cTopBase<p>";

#print readdir(PWD), p;
#print "<p>";
#rewinddir PWD;
if (!$gError) {
    @gPwdFiles = grep (/^$cId(\.\d{2})?\.(pdf|png|log)$/, readdir(PWD));
    @gRefFiles = grep (/^$cId(\.\d{2})?\.(pdf|png|log)$/, readdir(REFDIR));
    @gDiffFiles = grep (/^$cId(\.\d{2})?\.(pdf|png|log)$/, readdir(DIFFDIR));
    @gStereoFiles = grep (/^$cId(\.\d{2})?\.png$/, readdir(STEREODIR));

#    print "PwdFiles: ", @gPwdFiles, p;
#    print $#gPwdFiles, p;

    if ($#gPwdFiles == -1) {
	push(@gBody,
	     p("No \"$cTopBase/$cId\" PDF or PNG or log files to copy to reference directory." .
	       "  Cannot continue.\n"));
	$gError++;
    }

    if (!$gError) {
	if ($#gRefFiles != -1) {
	    push(@gBody,
		 p("Unlinking existing \"$cTopBase/$cId\" Reference files."));
	    chdir "ref";
	    if ($#gRefFiles + 1 != unlink (@gRefFiles)) {
		push(@gBody,
		     p("Couldn't unlink all \"$cTopBase/$cId\" reference PDF, PNG and log files." .
		       "  Cannot continue.\n"));
		$gError++;
	    }
	    chdir "..";
	}
    }

    if (!$gError) {
	if ($#gStereoFiles != -1) {
	    push(@gBody,
		 p("Unlinking existing \"$cTopBase/$cId\" Stereo files."));
	    chdir "stereo";
	    if ($#gStereoFiles + 1 != unlink (@gStereoFiles)) {
		push(@gBody,
		     p("Couldn't unlink all \"$cTopBase/$cId\" stereo PNG files." .
		       "  Cannot continue.\n"));
		$gError++;
	    }
	    chdir "..";
	}
    }

    if (!$gError) {
	if ($#gDiffFiles != -1) {
	    push(@gBody,
		 p("Unlinking existing \"$cTopBase/$cId\" Diff files."));
	    chdir "diff";
	    if ($#gDiffFiles + 1 != unlink (@gDiffFiles)) {
		push(@gBody,
		     p("Couldn't unlink all \"$cTopBase/$cId\" diff PDF, PNG and log files." .
		       "  Cannot continue.\n"));
		$gError++;
	    }
	    chdir "..";
	}
    }

    if (!$gError) {
	push(@gBody,
	     p("Zeroing new \"$cTopBase/$cId\" Diff files"));
	foreach $lFile (@gPwdFiles) {
	    if (not open (DIFFILE, ">diff/$lFile")) {
		push(@gBody,
		     p("Couldn't zero \"$lFile\" diff file." .
		       "  Cannot continue.\n"));
		$gError++;
		last;
	    } else {
		close DIFFILE;
		chmod 0666, "diff/$lFile";
	    }
	}
    }

    if (!$gError) {
	push(@gBody,
	     p("Copying \"$cTopBase/$cId\" PDF, PNG and log files to Reference."));
	foreach $lFile (@gPwdFiles) {
	    if (not copy($lFile, "ref/$lFile")) {
		push(@gBody,
		     p("Couldn't copy \"$lFile\" PDF, PNG or log file." .
		       "  Cannot continue.\n"));
		$gError++;
		last;
	    } else {
		chmod 0666, "ref/$lFile";
	    }
	}
    }
}

if (!$gError) {
    push(@gBody,
	 p({-style=>"background-color: green; color: white"},
	   "Replacing \"$cTopBase/$cId\" reference files completed successfully."));
} else {
    push(@gBody,
	 p({-style=>"background-color: red; color: white"},
	   "Replacing \"$cTopBase/$cId\" reference files failed."));
}

############################################################
# Output the headers
#
# Output a 'refresh' header only if there were no errors
if (!$gError) {
    print header(-Refresh=>"$cRefreshDelay; URL=$cTestResultsBase/$cTopBase/$cId.html");
} else {
    print header;
}
print start_html("Updating \"" . param('path') . "/" . param('id') . "\"");

############################################################
# Output the saved body text
print @gBody;

print hr;

############################################################
# If no errors, advise that page will refresh
if (!$gError) {
    print p("Reloading \"$cTopBase/$cId\" results page in $cRefreshDelay seconds.");
} else {
    print p("Return to \"" .
	    a({-href=>"$cTestResultsBase/$cTopBase/$cId.html"},
	      "$cTopBase/$cId.html") . "\"");
}

print end_html;
