import vlc
import time
import serial

def playsound(path):
    vlc.MediaPlayer(path).play()

#Chord mp3 files
C = ['C.m4a','Cm.m4a', 'C7.m4a', 'CUp.m4a', 'CmUp.m4a', 'C7Up.m4a']
D = ['D.m4a','Dm.m4a', 'D7.m4a', 'DUp.m4a', 'DmUp.m4a', 'D7UP.m4a']
E = ['E.m4a','Em.m4a', 'E7.m4a', 'EUp.m4a', 'EmUp.m4a', 'E7UP.m4a']
F = ['F.m4a','Fm.m4a', 'F7.m4a', 'FUp.m4a', 'FmUp.m4a', 'F7Up.m4a']
G = ['G.m4a','Gm.m4a', 'G7.m4a', 'GUp.m4a', 'GmUp.m4a', 'G7Up.m4a']
A = ['A.m4a','Am.m4a', 'A7.m4a', 'AUp.m4a', 'AmUp.m4a', 'A7Up.m4a']
B = ['B.m4a','Bm.m4a', 'B7.m4a', 'BUp.m4a', 'BmUp.m4a', 'B7Up.m4a']

port = serial.Serial(port='/dev/tty.SLAB_USBtoUART', baudrate=115200, timeout=100)


#ding dong sound if calibration passes
u = port.read()
up = int(u)
if up == 8:
    playsound('dingdong.wav')


while True:
    c = port.read()
    chord = int(c)

    s = port.read();
    i = int(s)
    if i == 1:
        i = 0
    else:
        i = 3

    e = port.read();
    extra = int(e)
    i = i + extra

    if chord == 1:
        playsound(C[i])
    elif chord == 2:
        playsound(D[i])
    elif chord == 3:
        playsound(E[i])
    elif chord == 4:
        playsound(F[i])
    elif chord == 5:
        playsound(G[i])
    elif chord == 6:
        playsound(A[i])
    elif chord == 7:
        playsound(B[i])

