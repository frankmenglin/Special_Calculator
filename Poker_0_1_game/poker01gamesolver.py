import numpy as np
def solve01game(potsize,betsize,raisesize):
    #This function will solve [0,1] poker game with the following rule.
    #Each player is dealt a number in [0,1] (uniform probability distribution)
    #You input the starting pot size, bet size, and total raise size.
    #Each player can bet/raise at that fixed sizes, no 3-bet is allowed.
    #Out of position player (the one that act first) can check-raise.
    #In show down, higher number win.
    x=potsize #potsize before betting
    y=betsize #bet size
    z=raisesize #raise size(total), if bet size is 2, and is raised to 7 (5 to call), then z=7

    A=[[0,0,0,0,0,0,0,0,0,x+y,0,0],
    [0,0,0,0,0,0,x+y,-x-y,x+y+z,0,0,0],
    [0,0,0,0,0,0,0,x+2*y,-x-y-z,0,0,0],
    [0,0,0,0,0,0,y,-y,0,-x-y,x+2*y,0],
    [0,0,0,0,0,0,0,0,0,x+y+z,-x-y-z,y-z],
    [0,0,0,0,0,0,y,-y,y-z,z,y-z,z-y],
    [0,-x-y,0,y,0,-y,x,0,0,0,0,0],
    [0,-x-y,x+2*y,y,0,-y,0,-2*y,0,0,0,0],
    [0,x+y+z,-x-y-z,0,0,y-z,0,0,0,0,0,0],
    [x+y,0,0,-x-y,x+y+z,-z,0,0,0,0,0,0],
    [0,0,0,x+2*y,-x-y-z,-y+z,0,0,0,0,0,0],
    [0,0,0,0,y-z,y-z,0,0,0,0,0,2*z-2*y]]
    B=[y,z,y-z,0,y-z,0,-y,-y,y-z,0,0,0]
    a=np.array(A)
    b=np.array(B)
    s=np.linalg.solve(A,b)
    for i in range(len(s)):
        s[i]=round(s[i],6)
    print(" ")
    print("The out of position player use the following strategy")
    print("Check-Raise(Value) from "+str(s[5])+" to "+"1")
    print("Bet(Value)-Call from "+str(s[4])+" to "+str(s[5]))
    print("Bet(Value)-Fold from "+str(s[3])+" to "+str(s[4]))
    print("Check-Call from "+str(s[2])+" to "+str(s[3]))
    print("Check-Raise(Bluff) from "+str(s[1])+" to "+str(s[2]))
    print("Check-Fold from "+str(s[0])+" to "+str(s[1]))
    print("Bet(Bluff)-Fold from "+"0"+" to "+str(s[0]))
    print(" ")
    print("When the in position player facing a check,")
    print("Bet(Value)-Call from "+str(s[8])+" to "+"1")
    print("Bet(Value)-Fold from "+str(s[7])+" to "+str(s[8]))
    print("Check back from "+str(s[6])+" to "+str(s[7]))
    print("Bet(Bluff)-Fold from "+"0"+" to "+str(s[6]))
    print(" ")
    print("When the in position player facing a bet,")
    print("Raise(Value) from "+ str(s[11])+" to "+"1")
    print("Call from "+str(s[10])+" to "+str(s[11]))
    print("Raise(Bluff) from "+str(s[9])+" to "+str(s[10]))
    print("Fold from "+"0 to "+str(s[9]))

solve01game(2,1,5)