OPENSNAP
==========

What's that?
------------
Opensnap brings the Aero Snap feature to Openbox.

This repo is no longer maintained
------------

Known bugs you just have to work around:

* No "unsnapping" feature (see end of this file for workaround)
* opensnap doesn't detect screen layout changes (just restart opensnap)

Does this work with other window managers?
------------------------------------------
The goal was to make it work with every EWMH compliant window manager.


Dependencies?
-------------
With the default configuration, you'll need wmctrl as a runtime dependency.

On most debian systems you should be able to install it by:

    sudo apt-get install wmctrl

If you want to build opensnap from source make sure you have these as well:

    sudo apt-get install build-essential libx11-dev libgtk-3-dev

Installing
----------
If you want to install opensnap from source first make sure you have git installed. (Or fetch a zip file: https://github.com/lawl/opensnap/archive/master.zip)

Fetch via git:

    git clone https://github.com/lawl/opensnap.git

Fetch via zip:

    wget https://github.com/lawl/opensnap/archive/master.zip
    unzip master.zip

Make sure you have all prerequisits:

    sudo apt-get install build-essential libx11-dev libgtk-3-dev wmctrl

And finally build and install it:

    cd opensnap*
    make
    sudo make install

And now start opensnap with

    opensnap

or

    opensnap --deamon

if you want it to deamonize.
    
Customizing the configuration
-----------------------------
By default opensnap stores its configuration files in /etc/opensnap if you've run `make install`.
If you want to customize these, you should copy the global configuration to your user directory.

    mkdir -p ~/.config/opensnap
    cp /etc/opensnap/* ~/.config/opensnap/

You can now edit the configuration files in `~/.config/opensnap/`. Make sure to restart opensnap for it to see the new configuration directory.

How can I use it?
-----------------
This should tell you all you need to know:

    opensnap --help

Copy the sample configs to ~/.config/opensnap/.


Unsnap workaround
-----------------

As of now opensnap does not support unsnapping (see #4).
You can find a workaround here: https://github.com/lawl/opensnap/issues/4#issuecomment-23666097

Do note however that this does not perfect unsnapping. I.e. your cursor possition and the window you are dragging might get displaced a bit on unsnapping. But it does work well enough for daily use.
