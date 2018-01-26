# check-tags
This program will scan a file and verify all parentheses, brackets, and braces are open and closed properly.<br />
There are flags to disable scanning on lines in comments.

## Help ##
    Usage: check_tags [OPTIONS] <FILE>
    Miscellaneous:
      -h, --help         Display this help
      -V, --version      version information
      -v, --verbose      verbose output
      -q, --quiet        suppress normal output

    Scanning options to ignore tags:
      -p    after # on same line
      -s    after // on same line
      -c    between /* */ on multiple lines
      -i    between single quotes on multiple lines
      -d    between double quotes on multiple lines
      -a    ignore tags in all comments

## Install ##
    git clone https://github.com/seiruss/check-tags
    cd check-tags
    make
