This is a desktop graphical application for [nethogs](https://github.com/raboof/nethogs).    
This project is in *early* stage and will conflict an existing installation of nethogs (waiting for pull-request to be processed)   
Screenshot: http://imgur.com/6AhsPzH   

To install:
* remove nethogs if you have it installed
* `git clone git@github.com:mb-gh/nethogs.git`
* `git clone git@github.com:mb-gh/gnethogs.git`
* `cd nethogs && git checkout build-as-lib && make && sudo make -f MakeLib.mk install_dev`
* `cd ../gnethogs && ./configure && make && sudo make install`
* `sudo setcap cap_net_raw /usr/local/bin/gnethogs`
* Seach `nethogs` in your application menu!

To uninstall:
* `cd nethogs && sudo make uninstall`
* `cd ../gnethogs && sudo make uninstall`
