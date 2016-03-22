This is a desktop graphical application for [nethogs](https://github.com/raboof/nethogs).    
Screenshot: http://imgur.com/6AhsPzH   
Project Status: [__Beta__](https://en.wikipedia.org/wiki/Software_release_life_cycle#Beta) (reviews and bug reports are welcome)

To build form source and install:
* remove nethogs if you have it installed
* install dependencies:
  * Debian/Ubuntu: `apt-get install build-essential libncurses5-dev libpcap-dev`
  * Yum-based distros: `yum install gcc-c++ libpcap-devel.x86_64 libpcap.x86_64 ncurses*`
* `cd ~`
* `git clone git@github.com:mb-gh/nethogs.git`
* `git clone git@github.com:mb-gh/gnethogs.git`
* `cd ~/nethogs && make && sudo make install_dev`
* `cd ~/gnethogs && ./configure && make && sudo make install`
* `sudo setcap cap_net_raw /usr/local/bin/gnethogs` (To be able to run it as non-root user)
* Seach `nethogs` in your application/activity menu!

To uninstall:
* `cd ~/nethogs && sudo make uninstall`
* `cd ~/gnethogs && sudo make uninstall`
