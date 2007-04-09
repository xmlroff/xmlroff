#! /usr/bin/perl
#
# Copyright (c) 2001, 2002, 2004 Sun Microsystems
#
# $Id: regenerate-testsuccess.pl,v 1.3 2006/07/25 11:19:15 tonygraham Exp $
#
# Regenerate 'testsuccess.html'.
#
# See COPYING for the status of this software.

use CGI qw/:standard/;
require("config.pl");

$cWorkingDir = "/usr/local/src/xslfo/$BASENAME";
$cResultsXML = "$cWorkingDir/$TEST_RESULTS";
$cXsltproc = '/usr/bin/xsltproc';
$cTestResultsBase = "/$BASENAME";

$gError = 0;

print header;
print start_html("Regenerating testsuccess.html");
#print dump;
print h1("Regenerating testsuccess.html");

$gTestSuccessCommand = "cd $cWorkingDir; $cXsltproc --novalid -o testsuccess.html testsuccess.xsl testsuccess.xsl";

if (!$gError) {
    print h2("Updating results success files");
    print "Running command:", p;
    print $gTestSuccessCommand,p;
}

if (!$gError) {
    $rc = 0xffff & system $gTestSuccessCommand;
    if ($rc != 0) {
	$gError++;
	print "<p style=\"background-color: red\">XSLT transformation of success files failed." .
	    " Cannot continue.</p>\n";
    } else {
	print "<p style=\"background-color: green\">XSLT transformation completed.</p>\n";
    }
}

print hr;

print "Return to \"",a({-href=>"$cTestResultsBase/testsuccess.html"}, "testsuccess.html"), "\"";
print end_html;
