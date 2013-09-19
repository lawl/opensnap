OPENSNAP
==========

What's that?
------------
Opensnap brings the Aero Snap feature to Openbox.

Report more bugs!
------------
![report bugs please](http://i.imgur.com/aF6eyZy.png)

If you didn't find any bugs, feel free to drop me a message at opensnap{ät]dumbinter[döt}net anyways. I'm happy for any feedback. But please report bugs on github if possible.


Does this work with other window managers?
------------------------------------------
The goal was to make it work with every EWMH compliant window manager.


Dependencies?
-------------
You'll need wmctrl.

On most debian systems you should be able to install it by:

    sudo apt-get install wmctrl

If you want to build it make sure you have these as well:

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
    mkdir -p ~/.config/opensnap
    cp sample_configs/* ~/.config/opensnap/

And now start opensnap by

    bin/opensnap --daemon
    

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
