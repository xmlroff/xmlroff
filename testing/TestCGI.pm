#
# create CGI based content handler class
#
# Copyright (c) 2011 Mentea
#
# Merger of 'update-results.pl' and 'HTTP::Daemon::Threaded' sample.
#
package TestCGI;

use File::Copy;
use CGI qw/:standard/;
use Cwd 'chdir';
use HTTP::Date qw(time2str);
use HTTP::Response;
use HTTP::Daemon::Threaded::CGIHandler;
use base ('HTTP::Daemon::Threaded::CGIHandler');

use vars qw($TEST_RESULTS $PROJECT_NAME $BASENAME $XSLTPROC);
require("config.pl");

use strict;
use warnings;

our $mtime = time2str(time());

sub new {
    my $class = shift;
    return $class->SUPER::new(@_);  # use default constructor
}

sub handleCGI {
    my ($self, $cgi, $session) = @_;
    my $uri = $ENV{REQUEST_URI};
    print $cgi->header(-status => "404 NOT FOUND", -nph => 1), "\n\n" and
	return 1
	unless (($uri eq '/update-results.pl') || ($uri eq 'postxml'));

    my $params = $cgi->Vars;

    my $html = '<html><body>';
    my $ct = 'text/html';
my @gBody = ();
    if ($uri eq '/update-results.pl') {
my $cWorkingDir = '.';
#my $cCwd = getcwd();
my $cResultsXML = "$cWorkingDir/$TEST_RESULTS";
my $cTopBase = $$params{'top-base'};
my $cId = $$params{'id'};
my $cIndividualXML = "$cWorkingDir/${cTopBase}/${cId}.xml";
my $cTestResultsBase = "/$PROJECT_NAME/$BASENAME";
my $cRefreshDelay = 1;

my $gError = 0;

my $gUseComment = $$params{'comment'};
$gUseComment =~ s/\`/\\`/g; #`
$gUseComment =~ s/"/\\"/g; #'

my $gXsltprocCommand =
    join ('',
	  "$XSLTPROC --novalid",
	  " --stringparam id ", $$params{'id'}, 
	  " --stringparam top-base ", $$params{'top-base'},
	  " --stringparam agreement ", $$params{'agreement'},
	  " --stringparam futuresupport \"",  $$params{'futuresupport'}, "\"",
	  " --stringparam specproblem ", $$params{'specproblem'},
	  " --stringparam testproblem ", $$params{'testproblem'},
	  " --stringparam comment \"", $gUseComment, "\"",
	  " -o ${cResultsXML}.out $cWorkingDir/update-result.xsl $cResultsXML"
	  );

my $IndividualXMLXsltprocCommand =
    join ('',
	  "$XSLTPROC --novalid",
	  " --stringparam id ", $$params{'id'}, 
	  " --stringparam top-base ", $$params{'top-base'},
	  " --stringparam agreement ", $$params{'agreement'},
	  " --stringparam futuresupport \"",  $$params{'futuresupport'}, "\"",
	  " --stringparam specproblem ", $$params{'specproblem'},
	  " --stringparam testproblem ", $$params{'testproblem'},
	  " --stringparam comment \"", $gUseComment, "\"",
	  " -o ${cIndividualXML}.out $cWorkingDir/update-results-xml.xsl ${cIndividualXML}"
	  );

############################################################
# Do the work and save the error and status messages in @gBody
#

push(@gBody,
     h1("Updating \"" . $$params{'path'} . "/" . $$params{'id'} . "\""));

push(@gBody,
     table({-border=>1},
	   # Has to be 'Tr' because 'tr' is a Perl function
            Tr({-align=>'CENTER',-valign=>'TOP'},
             [
               td(['Agreement:'     , $$params{'agreement'}]),
	       td(['Future support:', $$params{'futuresupport'} . "&#160;"]),
	       td(['Spec problem:'  , $$params{'specproblem'}]), 
	       td(['Test problem:'  , $$params{'testproblem'}]),
	       td(['Comment:'       , $$params{'comment'}])
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
    my $rc = 0xffff & system $gXsltprocCommand;
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

push(@gBody,
     h2("Updating individual results file \"$cIndividualXML\""));
push(@gBody,
     p("Running command:"));
push(@gBody,
     p($IndividualXMLXsltprocCommand));

if (!-e $cIndividualXML || !-r _) {
    push(@gBody,
	 p("\"$cIndividualXML\" does not exist or cannot be read." .
	   " Cannot continue\n"));
    $gError++;
}

if (!$gError && -e "${cIndividualXML}.out" && (!-f _ || !-w _)) {
    push(@gBody,
	 p("Cannot write output XML file: \"${cIndividualXML}.out\"." .
	   " Cannot continue.\n"));
    $gError++;
}

if (!$gError && -e "${cIndividualXML}.out") {
    if (unlink("${cIndividualXML}.out") != 1) {
	push(@gBody,
	     p("Cannot unlink existing output XML file: \"${cIndividualXML}.out\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    my $rc = 0xffff & system $IndividualXMLXsltprocCommand;
    if ($rc != 0) {
	$gError++;
	push(@gBody,
	     p("XSLT transformation of \"$cIndividualXML\" failed." .
	       " Cannot continue.\n"));
    } else {
	push(@gBody,
	     p("XSLT transformation completed."));
    }
}

if (!$gError) {
    if (! -e "${cIndividualXML}.out") {
	$gError++;
	push(@gBody,
	     p("\"${cIndividualXML}.out\" was not created." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (chmod(0666, "${cIndividualXML}.out") != 1) {
	$gError++;
	push(@gBody,
	     p("<tt>chmod</tt> of \"${cIndividualXML}.out\" failed." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (link("$cIndividualXML", "${cIndividualXML}.bak") != 1) {
	$gError++;
	push(@gBody,
	     p("Move of \"$cIndividualXML\" to \"${cIndividualXML}.bak\" failed." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (unlink("$cIndividualXML") != 1) {
	push(@gBody,
	     p("Cannot unlink results XML file: \"$cIndividualXML\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (link("${cIndividualXML}.out", "$cIndividualXML") != 1) {
	$gError++;
	push(@gBody,
	     p("Move of \"${cIndividualXML}.out\" to \"$cIndividualXML\" failed." .
	       " Cannot continue.\n"));
    }
}

if (!$gError) {
    if (unlink("${cIndividualXML}.out") != 1) {
	push(@gBody,
	     p("Cannot unlink output results XML file: \"${cIndividualXML}.out\"." .
	       " Cannot continue.\n"));
	$gError++;
    }
}

if (!$gError) {
    if (unlink("${cIndividualXML}.bak") != 1) {
	push(@gBody,
	     p("Cannot unlink backup results XML file: \"${cIndividualXML}.bak\"." .
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
	 h2("Replacing \"" .
	    $$params{'top-base'} .
	    "/" . $$params{'id'} .
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
    my @gPwdFiles = grep (/^$cId(\.\d{2})?\.(pdf|png|log)$/, readdir(PWD));
    my @gRefFiles = grep (/^$cId(\.\d{2})?\.(pdf|png|log)$/, readdir(REFDIR));
    my @gDiffFiles = grep (/^$cId(\.\d{2})?\.(pdf|png|log)$/, readdir(DIFFDIR));
    my @gStereoFiles = grep (/^$cId(\.\d{2})?\.png$/, readdir(STEREODIR));

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
	foreach my $lFile (@gPwdFiles) {
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
	foreach my $lFile (@gPwdFiles) {
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

	$html .= "$_ is $$params{$_}<br>\n"
	    foreach (sort keys %$params);
	$html .= "</body></html>\n";
############################################################
# Output the headers
#
# Output a 'refresh' header only if there were no errors
if (!$gError) {
    print $cgi->header( 
	-Content_type => $ct,
	-charset => 'UTF-8',
	-Last_Modified => $mtime,
	-Refresh => "$cRefreshDelay; URL=$cIndividualXML"
	),
	$html, @gBody,
	p("Reloading \"$cTopBase/$cId\" results page in $cRefreshDelay seconds.");
} else {
    print $cgi->header( 
	-Content_type => $ct,
	-charset => 'UTF-8',
	-Last_Modified => $mtime,
	),
	$html, @gBody,
	p("Return to \"" .
	  a({-href=>"$cIndividualXML"},
	    "$cIndividualXML") . "\"");
}
    chdir "..";
    }
    return 1;
}

return 1;
