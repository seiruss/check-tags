# check-tags
This program will scan a file and verify all parentheses, brackets, and braces are open and closed properly.<br />
There are flags to disable scanning on lines in comments.

Usage: check_tags [OPTIONS] \<FILE\><br />
Miscellaneous:<br />
&nbsp;&nbsp;-h, --help&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Display this help<br />
&nbsp;&nbsp;-V, --version&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;version information<br />
&nbsp;&nbsp;-v, --verbose&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;verbose output<br /><br />
Scanning options:<br />
&nbsp;&nbsp;-p&nbsp;&nbsp;&nbsp;&nbsp;ignore tags after # on same line<br />
&nbsp;&nbsp;-s&nbsp;&nbsp;&nbsp;&nbsp;ignore tags after // on same line<br />
&nbsp;&nbsp;-m&nbsp;&nbsp;&nbsp;ignore tags between /* */ on multiple lines<br />
&nbsp;&nbsp;-u&nbsp;&nbsp;&nbsp;&nbsp;ignore tags between ' ' on multiple lines<br />
&nbsp;&nbsp;-q&nbsp;&nbsp;&nbsp;&nbsp;ignore tags between " " on multiple lines<br />
&nbsp;&nbsp;-a&nbsp;&nbsp;&nbsp;&nbsp;ignore tags between all comments<br />
