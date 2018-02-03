.chipsets:
input a
input b
4071 or
output s
.links:
a:1 or:1
b:1 or:2
or:3 s:1

entry = (sec_chip, sec_link)+
sec_chip = ".chipsets", ':', (str, str)*
sec_link = ".links", ':', (str, ':', num, ' ', str, ':', num)*
