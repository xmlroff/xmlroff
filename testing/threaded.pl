#! /usr/bin/perl
#
# Copyright (c) 2011 Mentea
#
# Based on 'HTTP::Daemon::Threaded' sample.
#
#       now fire up a server
#
package main;

use HTTP::Daemon::Threaded;
use HTTP::Daemon::Threaded::SessionCache;
use MyContentParams;
use MyEventLog;
use MyWebLog;
use TestCGI;

use strict;
use warnings;
#
# create a SessionCache object using default implementation
#
my $sessions = HTTP::Daemon::Threaded::SessionCache->new();
#
# create a ContentParams container
#
my $contparams = MyContentParams->new( "blah" );

my $evtlog = MyEventLog->new();
my $weblog = MyWebLog->new();

my $httpd = HTTP::Daemon::Threaded->new(
    Port                    => 8081,
    MaxClients              => 20,
    ContentParams   => $contparams,
    SessionCache    => $sessions,
    LogLevel                => 3,           # full info logging
    EventLogger             => $evtlog,
    WebLogger               => $weblog,
    DocRoot                 => './',        # root directory for default file handler
    Handlers                => [
	'^\/update-results.pl$', 'TestCGI',                # uses CGI
	'^\/postxml$', 'TestHTTPReq',   # uses HTTP::Request/Response directly
	'^.*\/scripty\.js$', '*',       # default file handler
	'^.*\/(\w|-)+\.html$', '*',         # default file handler
	'^.*\/(\w|-)+\.css$', '*',         # default file handler
	'^.*\/(\w|-)+\.fo$', '*',         # default file handler
	'^.*\/(\w|-)+\.x[ms]l$', '*',         # default file handler
	'^.*\/(\w|-|.)+?\.png$', '*',         # default file handler
    ],
    MediaTypes              => {
	'text/xml'      => [ 'xml', 'dtd', 'fo' ],
	'text/xsl'      => [ 'xsl' ],
	'image/png'     => [ 'png' ],
    }
    ) || die "Unable to create web server, exiting.";

while(1){};
    #
    # all done, shutdown
    #
    $httpd->shutdown();
