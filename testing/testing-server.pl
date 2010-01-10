#! /usr/bin/perl
#
# Copyright (c) 2008 Menteith Consulting Ltd
#
# Perl web server for XSL FO test results.
#
# This is part of the xmlroff XSL Formatter project.
#
# See COPYING for the status of this software.

#use strict;

############################################################
# Library modules
use Getopt::Long;
use XML::LibXML;
use XML::LibXSLT;
use HTTP::Daemon;
use HTTP::Headers;
use HTTP::Response;
use HTTP::Status qw(:constants :is status_message);

require("config.pl");

my $debug = 0;
my $port = 8080;
my $result = GetOptions ("debug"  => \$debug,
                         "port=i"   => \$port);

my $parser = XML::LibXML->new();
my $xslt = XML::LibXSLT->new();
my $stylesheet = $xslt->parse_stylesheet_file("testsuccess.xsl");
my $testresults = $parser->parse_file($TEST_RESULTS);

my $d = HTTP::Daemon->new(
    LocalPort => $port
    ) || die;
print "$TITLE at: <URL:", $d->url, "index.html>\n";

while (my $client = $d->accept) {
    while (my $request = $client->get_request) {
	my ($page) = $request->url->path;
	$page =~ s/^\///;
	if ($debug > 0) {
	    print "$page\n";
	    print $request->as_string;
	}
	if ($request->method eq 'GET') {
	    if ($page =~ m/^index.html/) {
		my $time = localtime();
		my $results = $stylesheet->transform($testresults,
						     date => "'$time'",
						     FORM => 1);
		my $response = HTTP::Response->new(RC_OK);
		$response->date(time);
		$response->content_type($stylesheet->media_type());
		$response->content_encoding($stylesheet->output_encoding());
		$response->content($stylesheet->output_as_bytes($results));
		$client->send_response($response);
		if ($debug > 0) {
		    print "Processed index.html\n";
		    print $response->headers->as_string;
		}
		$client->force_last_request;
	    } elsif (-e $page) {
		if ($page =~ m/\.html$/) {
		    print $` . "\n";
		}
		my $mtime = (stat(_))[9];
		if ($mtime > $request->if_modified_since) {
		    $client->send_file_response($page);
		    $client->send_crlf;
		} else {
		    $client->send_basic_header(RC_NOT_MODIFIED);
		    $client->force_last_request;
		}
	    } else {
		$client->send_error(HTTP_NOT_FOUND);
	    }
	} elsif ($request->method eq 'POST') {
	    if ($page =~ m/update-results.pl$/) {
	    } else {
		$client->send_error(HTTP_NOT_FOUND);
	    }
	} else {
	    $client->send_error(HTTP_METHOD_NOT_ALLOWED);
	}
    }
    $client->close;
    undef($client);
}
