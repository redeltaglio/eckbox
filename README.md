# eckbox
A github mirror of http://eckbox.sourceforge.net/


Eckbox is software designed to aid in a specific type of security testing against a spying attack known as van Eck Phreaking or TEMPEST. It involves picking up radiation leaking from an electronic device, such as a monitor, and interpreting the signal to recreate the data contained in the device. This can be thought of as a sort of shoulder-surfing. Eckbox is the first and only open-source software designed that helps to test against this kind of attack. But it's still in early development, so feel free to contribute code, ideas, designs, advice, and nonthreatening e-mails :).

What Eckbox is for:
Eckbox is software that allows a user to remotely shoulder surf on a target computer's monitor (this is known as van Eck Phreaking).  It requires a certain amount of hardware that must be made by the user.  Instructions for building this hardware is located on eckbox's sourceforge project page at http://www.eckbox.sourceforge.net, although some day if I'm not lazy, it will be included in this document and the man pages too.

How to install it:
After untarring and unbzip2ing the archive, cd to the directory and run make, and make install.  Configure doesn't actually do anything.

How to use it:
First, see the eckbox project page at eckbox.sourceforge.net to build the hardware needed.

After that, you'll need to calibrate eckbox.  To do this, on a separate computer, run the bw program in the source directory (the directory you got when you ran tar -jxvf ./eckbox.tar.bz2).  This should display a screen of alternating black and white pixels on the monitor.  It helps if the monitor on the separate, target computer's resolution is the same as the resolution that you intend to be spying on.

Once you have bw running on the separate computer, place the radio from your hardware next to the separate computer's monitor, and run eckboxcalib (just typing it at the prompt will do).

Now you can just type "eckbox" at the prompt, and it will do the shoulder surfing for you.  If you experience any problems, examine your hardware, jiggle your radio, adn read the man pages.

How it will improve your life:
If you're a corporate spy, I'm certain you'd love to be able to book a hotel room next to a target CEO and read everything right off his laptop through the wall.

If you're a security freak, I'm sure you'll love the ability to develop hardware and software to counter this type of attack.
