# icinga2_check_oom
Icinga2/Nagios check for Out of memory problems. ATM it check all dmesg output. If you want after check make it green again, you need to run dmesg -c.

### About this fork
The original version of this check assumes that non-root users can run `/bin/dmesg`, which is true on Ubuntu but not Debian (and likely other distros).  While you can give unprivileged users access to `/bin/dmesg` with `sudo sysctl -w kernel.dmesg_restrict=1` ([source](https://www.cyberciti.biz/faq/how-to-prevent-unprivileged-users-from-viewing-dmesg-command-output-on-linux/)), this has [security implications](https://www.halfdog.net/Security/2015/HavingFunWithDmesg/).  Instead, I've created a variant that uses a setuid wrapper, hard-coding the path to the original Nagios check to prohibit setuid abuse.

### Installing
* Place `check_oom.py` and `check_oom_wrapper` in `/usr/lib/nagios/plugins`.
 * If you have a different file path for your plugins, you will need to recompile `check_oom_wrapper.c` after modifying the `REAL_PATH` definition on line 3.  Use `gcc -o check_oom_wrapper check_oom_wrapper`.
* Set the setuid flag on the wrapper file: 
```shell
sudo chmod u+s /usr/lib/nagios/plugins/check_oom_wrapper.
```

As a future improvement, it would be nice to detect whether the script is running as root, and only call `setuid()` on the Python subprocess if necessary.


```bash
usage: check_oom.py [-h] [-m {warning,critical,default}] [-v]

Check for OOM killer events

optional arguments:
  -h, --help            show this help message and exit
  -m {warning,critical,default}, --mode {warning,critical,default}
                        Mode of results for this check: warning, critical,
                        default
  -s, --short           If this option is specified, check ignores dmesg OOM
                          problems older then 24 hours
  -v, --verbose         Show verbose output from demsg about OOM killer events

check_oom.py: v.1.1 by Dmytro Prokhorenkov
```
