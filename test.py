array = [4,'A','B','A',3,'B','C','B',2,'C','D','C',1,'D','E','D']

hiscores = [None] * 6;
names = [None] * 20;

i = 0
while i <= 12:
	hiscores[i / 4 + 1] = array[i]
	names[i + 1] = array[i + 1]
	names[i + 2] = array[i + 2]
	names[i + 3] = array[i + 3]
	i+=4
	
print hiscores;
print names;

while True:
	score = int(raw_input("enter score"));
	name = "a" + raw_input("enter name");
	
	i = 1
	while score < hiscores[i]:
		i+=1
	
	j = 4
	while j >= 1:
		hiscores[j] = hiscores[j - 1]
		names[j * 4 + 1] = names[(j - 1) * 4 + 1]
		names[j * 4 + 2] = names[(j - 1) * 4 + 2]
		names[j * 4 + 3] = names[(j - 1) * 4 + 3]
		
		j-=1
		
	hiscores[i] = score;
	
	currentNameLocation = i - 1
	
	if currentNameLocation == 0:
		names[1] = name[1];
		names[2] = name[2];
		names[3] = name[3];
	elif currentNameLocation == 1:
		names[5] = name[1];
		names[6] = name[2];
		names[7] = name[3];
	elif currentNameLocation == 2:
		names[9] = name[1];
		names[10] = name[2];
		names[11] = name[3];
	elif currentNameLocation == 3:
		names[13] = name[1];
		names[14] = name[2];
		names[15] = name[3];
		
	print hiscores;
	print names;
