#
#       a web request logger
#
package MyWebLog;

use HTTP::Daemon::Threaded::Logger;
use base qw(HTTP::Daemon::Threaded::Logger);

sub new {
    my $class = shift;
    return $class->SUPER::new(@_);  # use default constructor
}

return 1;
