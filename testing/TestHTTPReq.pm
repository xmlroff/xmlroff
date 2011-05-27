#
# create content handler class
#
package TestHTTPReq;

use HTTP::Date qw(time2str);
use HTTP::Response;
use HTTP::Daemon::Threaded::Content;
use base ('HTTP::Daemon::Threaded::Content');

use strict;
use warnings;

sub new {
    my $class = shift;
    return $class->SUPER::new(@_);  # use default constructor
}

sub getContent {
    my ($self, $fd, $request, $uri, $params, $session) = @_;

    return $fd->send_error(404)
	unless (($uri eq 'posted') || ($uri eq 'postxml'));

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
    my $res = HTTP::Response->new(200, 'OK',
				  [ 'Content-Type' => $ct,
				    'Content-Length' => length($html),
				    'Last-Modified' => time2str(time())
				  ]);
    $res->request($request);
    $res->content($html);
    return $fd->send_response($res);
}

sub getHeader {
    my ($self, $fd, $request, $uri, $params, $session) = @_;

    return $fd->send_error(404)
	unless (($uri eq 'posted') || ($uri eq 'postxml'));

    my $html = '<html><body>';
    my $ct = 'text/html';
    if ($uri eq 'posted') {
	$html .= "$_ is $$params{$_}<br>\n"
	    foreach (sort keys %$params);
	$html .= "</body></html>\n";
    }
    else {
	$ct = 'text/xml';
	$html = $params;        # its the content
    }
    my $res = HTTP::Response->new(200, 'OK',
				  [ 'Content-Type' => $ct,
				    'Content-Length' => length($html),
				    'Last-Modified' => time2str(time())
				  ]);
    $res->request($request);
    return $fd->send_response($res);
}

return 1;
