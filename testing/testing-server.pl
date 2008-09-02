#! /usr/bin/perl
#use strict;

use XML::LibXML;
use XML::LibXSLT;
use HTTP::Daemon;
use HTTP::Headers;
use HTTP::Response;
use HTTP::Status;

require("config.pl");

my $parser = XML::LibXML->new();
my $xslt = XML::LibXSLT->new();
my $stylesheet = $xslt->parse_stylesheet_file("testsuccess.xsl");
my $testresults = $parser->parse_file($TEST_RESULTS);

my $d = HTTP::Daemon->new(
    LocalPort => 8080
    ) || die;
print "Please contact me at: <URL:", $d->url, ">\n";

while (my $client = $d->accept) {
    while (my $request = $client->get_request) {
	my ($page) = $request->url->path;
	$page =~ s/^\///;
	print "$page\n";
	print $request->as_string;
	if ($page =~ m/index.html/) {
	    my $time = localtime();
	    my $results = $stylesheet->transform($testresults,
						 date => "'$time'");
	    my $response = HTTP::Response->new(RC_OK);
	    $response->date(time);
	    $response->content_type($stylesheet->media_type());
	    $response->content_encoding($stylesheet->output_encoding());
	    my $string = $stylesheet->output_as_bytes($results);
	    #$response->content_length($string);
	    $response->content($string);
	    $client->send_response($response);
	    print $response->headers->as_string;
	    $client->force_last_request;
	} elsif (-e $page) {
	    my $mtime = (stat(_))[9];
	    if ($mtime > $request->if_modified_since) {
		$client->send_file_response($page);
		$client->force_last_request unless ($page =~ /\.html$/);
	    } else {
		$client->send_status_line(RC_NOT_MODIFIED);
		$client->force_last_request;
	    }
	} else {
	    $client->send_error(RC_NOT_FOUND);
	}
    }
    $client->close;
    undef($client);
}
