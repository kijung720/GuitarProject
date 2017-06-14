# Because Everything is a Guitar
This is a final project for Stanford's CS107E: Computer Systems From the Ground Up.
Using Raspberry Pi and MinIMU-5 v9 accelerometer, I made an air guitar,
which the player strums the guitar by using an accelerometer as a guitar
peak, and presses set of buttons to generate certain chords.
Guitar can play 42 different strumming sounds; three different
chords (original, minor, 7) for each note from C~A, and each of these sounds
have different sounds for up strum and down strum.

## How To Play
0. Make the physical air guitar! (Ask me if you really want to make one)
1. Install the codes + mp3 files
2. Hold the peak with your thumb and pointer finger. 
3. ```
   $ make install && python play.py
   ```
4. Hold onto your peak (it should be flat) until you hear the ding-dong sound
5. Seven white buttons represent chords from C to A :
   ______________________
   |    D   F   A        |
   |                B    |
   |    C   E   G        |
   ----------------------
   Two red buttons represent minor and 7:
   ______________________
   |     m   7           |
   |                     |
   |                     |
   ----------------------
6. Press and hold the button and strum down or up.
7. To play m or 7, press and hold the desired chord button and m or 7.
8. Enjoy :)

## Implementation
### Reading the Accelerometer
LSM6DS33 gives acceleration in x, y, and z coordinates. Thus, it is closer to
reading the tilt values of each coordinates than getting the acceleration.
Therefore, to detect the strumming motion, I had to see the change in the tilt
values. After many trials, I realized that people tend to tilt the
accelerometer in respect to z coordinate when strumming. Z value, at 1000mg
when the accelerometer is held flat, goes down to zero or below zero when
people strum down. Thus, to see if the player is strumming down or up, I had
to check the accelerometer's z value going down or going up. To do this, while
constantly reading the acceleration (2000 reads per second), I kept track of the
average of 10 most recent values. I would then compare the current average value
with the last average value, and if the average value goes down for more than
four consecutive times, I trigged the sound, and vise versa for going up.
Only triggering the sound when the value goes down or up consecutively was very
important since this prevented false positive triggers.

###Button detection
Guitar knows what chord to play with buttons that trigger gpio pins.
In guitar.c, I detect which button is pressed and return the pressed button value.
Only one of the buttons from C~A can be pressed, and one of m or 7 can be pressed.
Player can generate m and 7 chords by pressing one of C~A and one of m and 7.

###Playing sound
I use serial port communication between Pi and computer to trigger a recorded sound.
When the button is pressed and the strumming is detected, I send three digit value
that contains information about pressed button(s) and strum motion.
I then read the value from python code, find the correct sound and play it through
VLC media player.

##Challenges
Biggest challenge was reading the accelerometer to get the right strum motion.
First, accelerometer was behaving different from what I expected. I was expecting
to see one number, the acceleration that I learned in physics and the acceleration
that I see in everyday life. So I expectd the accelerometer to print out 0 when not
moving and print out larger value as it moves faster. However, as described above,
accelerometer gave me tilt values for the three coordinates. (I still don't know why
this is called "accleration." Please let me know if anyone knows about this!). Thus,
detecting the motion with tilt value was challenging.
Generalizing the strumming motion and triggering the strumming was also difficult.
Since everyone strums differently, I had to figure out the general pattern of strumming.
Once I did that, I needed to determine when to trigger the sound. Since the accelerometer
was so accurate, I had to make sure that I don't make many false positive triggers. However,
at the same time I could not just read the acceleration with big delays since that might
miss the detected motion. I finally decided to constantly read the acceleration for accuracy,
but to take the average of ten values and constantly compare the previous average value and
current average value. Only when the average consecutively goes down or goes up, I would
trigger the sound.
Lastly, unexpected challenge came from soldering and making the guitar. I had to fit in
nine buttons to a box smaller than a hand. This required many precise soldering.

##Acknowledgement
My amazing TA Will Crichton help me write the python script for playing audio.
