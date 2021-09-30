import sys
import fileinput

key = ''
phrase = ''
count = 0
# Recibe la entrada
for line in fileinput.input():
	if count == 0:
		key = line
		count += 1
		continue
	if count > 1:
		break
	phrase = line
phrase = phrase.replace('\n', '')
key = key.replace('\n', '')

key = [ord(char) for char in key]

# KSA
keylength = len(key)

S = [i for i in range(256)]

j = 0
for i in range(256):
	j = (j + S[i] + key[i % keylength]) % 256
	S[i], S[j] = S[j], S[i]  # swap
	
# PRGA 
i = 0
j = 0
K = [i for i in range(len(phrase))]
k = 0
while k < len(phrase):
	i = (i + 1) % 256
	j = (j + S[i]) % 256
	# swap
	S[i], S[j] = S[j], S[i]

	K[k] = S[(S[i] + S[j]) % 256]
	k += 1

# Generando salida utilizando XOR
output = [i for i in range(len(phrase))]
for i in range(len(phrase)):
	output[i] = ord(phrase[i]) ^ K[i]
	
for x in output:
	print("%02X" % x, end='')