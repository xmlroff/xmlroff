#
#       a container for content-specific parameters
#
package MyContentParams;

use HTTP::Daemon::Threaded::ContentParams;
use base qw(HTTP::Daemon::Threaded::ContentParams);

sub new {
    my $class = shift;
    return $class->SUPER::new(@_);  # use default constructor
}

return 1;
