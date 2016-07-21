This is a desktop graphical application for [nethogs](https://github.com/raboof/nethogs).    
Project Status: [__Beta__](https://en.wikipedia.org/wiki/Software_release_life_cycle#Beta) (reviews and bug reports are welcome)

##Screenshot
![Screenshot](https://cloud.githubusercontent.com/assets/6733770/16925237/a1363dd0-4cf9-11e6-81aa-83a52e72c549.png)

##Installation
To build form source and install:
* remove nethogs if you have it installed
* install dependencies:
  * Debian/Ubuntu: `apt-get install build-essential libncurses5-dev libpcap-dev libgtkmm-3.0-dev`
  * Yum-based distros: `yum install gcc-c++ libpcap-devel.x86_64 libpcap.x86_64 ncurses* gtkmm30-docs`
* `cd ~`
* `git clone git@github.com:mb-gh/nethogs.git`
* `git clone git@github.com:mb-gh/gnethogs.git`
* `cd ~/nethogs && make && sudo make install_dev`
* `cd ~/gnethogs && autogen.sh && ./configure && make && sudo make install`
* `sudo setcap cap_net_raw /usr/local/bin/gnethogs` (To be able to run it as non-root user)
* Seach `nethogs` in your application/activity menu!

To uninstall:
* `cd ~/nethogs && sudo make uninstall`
* `cd ~/gnethogs && sudo make uninstall`

