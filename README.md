# check-tags
This program will scan a file and verify all parentheses, brackets, and braces are open and closed properly.<br />
There are flags to disable scanning on lines in comments.

Usage: check_tags [OPTIONS] \<FILE\><br />
Miscellaneous:<br />
&nbsp;&nbsp;-h, --help&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Display this help<br />
&nbsp;&nbsp;-V, --version&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;version information<br />
&nbsp;&nbsp;-v, --verbose&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;verbose output<br />
&nbsp;&nbsp;-q, --quiet&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;suppress normal output<br /><br />
Scanning options to ignore tags:<br />
&nbsp;&nbsp;-p&nbsp;&nbsp;&nbsp;&nbsp;after # on same line<br />
&nbsp;&nbsp;-s&nbsp;&nbsp;&nbsp;&nbsp;after // on same line<br />
&nbsp;&nbsp;-c&nbsp;&nbsp;&nbsp;&nbsp;between /* */ on multiple lines<br />
&nbsp;&nbsp;-i&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;between single quotes on multiple lines<br />
&nbsp;&nbsp;-d&nbsp;&nbsp;&nbsp;&nbsp;between double quotes on multiple lines<br />
&nbsp;&nbsp;-a&nbsp;&nbsp;&nbsp;&nbsp;ignore tags in all comments<br />
