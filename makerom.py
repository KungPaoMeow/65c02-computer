code = bytearray([
    0xa9, 0xff,         # lda #$ff
    0x8d, 0x02, 0x60,   # sta $6002
    
    0xa9, 0x55,         # lda #$55
    0x8d, 0x00, 0x60,   # sta $6000
    
    0xa9, 0xaa,         # lda #$aa
    0x8d, 0x00, 0x60,   # sta $6000

    0x4c, 0x05, 0x80,   # jmp $8005
])

# For 6502, 0xEA is do nothing instruction. EEPROM is 256-kibibit
rom = code + bytearray([0xea] * (32768 - len(code)))

# Our EEPROM is addressable from 0x8000 to 0xFFFF
# Versatile Interface Adapter addressable from 0x6000
rom[0x7ffc] = 0x00
rom[0x7ffd] = 0x80

with open('rom.bin', 'wb') as out_file:
    out_file.write(rom)