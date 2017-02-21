This is a desktop graphical application for [nethogs](https://github.com/raboof/nethogs).    
Gnethogs uses libnethogs which is built from source by following the instructions below.

##Screenshot
![Screenshot](https://cloud.githubusercontent.com/assets/6733770/16925237/a1363dd0-4cf9-11e6-81aa-83a52e72c549.png)

##Installation
To build form source and install:
* install dependencies:
  * Debian/Ubuntu: `apt-get install build-essential libncurses5-dev libpcap-dev libgtkmm-3.0-dev autoconf autopoint intltool libxml2-utils`
  * Yum-based distros: `yum install gcc-c++ libpcap-devel.x86_64 libpcap.x86_64 ncurses* gtkmm30-docs autoconf autopoint intltool libxml2-utils`
* `cd ~`
* `git clone https://github.com/raboof/nethogs.git`
* `git clone https://github.com/mbfoss/gnethogs.git`
* `cd ~/nethogs && make libnethogs && sudo make install_dev`
* `cd ~/gnethogs && ./autogen.sh && ./configure && make && sudo make install`
* `sudo setcap cap_net_raw+ep /usr/local/bin/gnethogs` (To be able to run it as non-root user)
* Seach `nethogs` in your application/activity menu!

To uninstall:
* `cd ~/nethogs && sudo make uninstall`
* `cd ~/gnethogs && sudo make uninstall`

