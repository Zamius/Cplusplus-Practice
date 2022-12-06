from random import shuffle

with open("words_updated.txt", 'r') as f:
	content = [x.strip() for x in f.readlines()]

shuffle(content)

with open("words_updated.txt", "w") as f:
	f.write("\n".join(content))
