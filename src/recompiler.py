def rRom(filename:str):
    mem = []
    a = open(filename , "rb").read()
    for i in range(len(a)-1):
        mem.append((a[i] << 8 | a[i+1]))
    return mem

for i in rRom("../roms/test_opcode.ch8"):
    print(hex((i& 0xF000) >> 12))

arr = []

