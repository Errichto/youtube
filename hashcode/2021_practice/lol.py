import matplotlib.pyplot as plt
import numpy as np
import os

plt.rcParams['figure.figsize'] = [50, 50]


PATH = ""
TESTS = ['r.in', 'l.in', 'c.in', 'o.in']

BLACK = [0, 0, 0]
WHITE = [1, 1, 1]
RED = [1, 0, 0]
GREEN = [0, 1, 0]
BLUE = [0, 0, 1]
GREY = [0.5, 0.5, 0.5]

def mix_colors(c1, c2):
    c1 = np.array(c1)
    c2 = np.array(c2)
    return np.mean((c1, c2), axis=0)

def draw_plansza(plansza, name="", backbone=[], routers=[]):
    def draw_point(x, y, image, color, big=False):
        xs = [0]
        ys = [0]
        if big:
            xs = [-1, 0, 1]
            ys = [-1, 0, 1]
        for xd in xs:
            for yd in ys:
                image[x+xd, y+yd] = color
        return
    
    sransza = np.zeros((H + 2, W + 2))
    for x in range(H):
        for y in range(W):
            sransza[x + 1][y + 1] = sransza[x + 1][y] + \
                                    sransza[x][y + 1] - \
                                    sransza[x][y] + \
                                    (plansza[x][y] == '#')
    
    image = np.zeros(H*W*3)
    image = image.reshape((H, W, 3))

    for x in range(H):
        for y in range(W):
            if plansza[x][y] == '#':
                draw_point(x, y, image, WHITE)
            elif plansza[x][y] == '.':
                draw_point(x, y, image, BLACK)
            else:
                draw_point(x, y, image, GREY)
    

    draw_point(B_r, B_c, image, RED, True)
    
    for x, y in backbone:
        draw_point(x, y, image, RED)
        
    
    greno = np.zeros(H*W)
    greno = greno.reshape((H, W, 1))
    
    for x, y in routers:
        draw_point(x, y, image, GREEN)
    
    def ile(sransza, x1, x2, y1, y2):
        return sransza[x2 + 1][y2 + 1] - sransza[x1][y2 + 1] - sransza[x2 + 1][y1] + sransza[x1][y1]
    
    for x, y in routers:
        for dx in range(-R, R + 1):
            for dy in range(-R, R + 1):
                if x + dx >= 0 and x + dx < H:
                    if y + dy >= 0 and y + dy < W:
                        a = x
                        b = x + dx
                        if a > b:
                            a, b = b, a
                        c = y
                        d = y + dy
                        if c > d:
                            c, d = d, c
                        if ile(sransza, a, b, c, d) == 0:
                            greno[x + dx, y + dy] = 1
    
    for x in range(H):
        for y in range(W):
            if greno[x, y] == 1:
                draw_point(x, y, image, mix_colors(image[x, y], GREEN))
    
    plt.imshow(image)

    plt.title(TEST)
    plt.axis('off')
    if name == "":
        name = TEST[:-3] + ".png"
    plt.savefig(PATH + name, bbox_inches='tight')
    return
    
for TEST in TESTS:
    OUTPUT = TEST[0] + ".out"
    plansza = []
    with open(PATH + TEST, "r") as f:
        H, W, R = [int(a) for a in f.readline().split(" ")]
        P_r, P_b, B = [int(a) for a in f.readline().split(" ")]
        B_r, B_c = [int(a) for a in f.readline().split(" ")]
        for x in range(H):
            plansza.append(f.readline()[:-1])

    with open(PATH + OUTPUT, "r") as f:
        N = int(f.readline())
        backbone = []
        routers = []
        for _ in range(N):
            x, y = [int(a) for a in f.readline().split(" ")]
            backbone.append((x, y))
        M = int(f.readline())
        for _ in range(M):
            x, y = [int(a) for a in f.readline().split(" ")]
            routers.append((x, y))
    draw_plansza(plansza,  TEST[0]+"_dupsko", backbone, routers)
