from math import floor, ceil
def sloni_line(w,x,T):
    sudy = T % 2 == 0
    if (sudy):
        pr = floor((w-x)/2)
        le = floor(x/2)
        pozice = min(T/2,pr) + min(T/2,le) + 1
    else:
        width_pravo = ceil((w-x)/2)
        width_levo = ceil(x/2)
        half_T = ceil(T/2)
        pozice = min(half_T,width_pravo) + min(half_T,width_levo)

    return pozice

def sloni(w,h,x,y,T):
    pozice = 0
    h -= 1
    w -= 1

    pozice += sloni_line(w,x,T)

    for i in range(1,y+1):
        if (T-i < 0): break
        pozice += sloni_line(w,x,T-i)

    for i in range(1,h-y+1):
        if (T-i < 0): break
        pozice += sloni_line(w,x,T-i)

    return pozice

print(sloni(5, 7, 0, 3, 3))