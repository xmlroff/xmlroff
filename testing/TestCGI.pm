#
# create CGI based content handler class
#
package TestCGI;

use HTTP::Date qw(time2str);
use HTTP::Response;
use HTTP::Daemon::Threaded::CGIHandler;
use base ('HTTP::Daemon::Threaded::CGIHandler');

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
	unless (($uri eq 'posted') || ($uri eq 'postxml'));

    my $params = $cgi->Vars;

    my $html = '<html><body>';
    my $ct = 'text/html';
    if ($uri eq 'posted') {
	$html .= "$_ is $$params{$_}<br>\n"
	    foreach (sort keys %$params);
	$html .= "</body></html>\n";
    }
    else {
	$ct = 'text/xml';
	$html = $params;        # reflect the content
    }
    print $cgi->header( 
	-Content_type => $ct,
	-charset => 'UTF-8',
	-Last_Modified => $mtime,
	),
	$html;

    return 1;
}

return 1;
